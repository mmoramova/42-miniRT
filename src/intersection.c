/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:27:38 by josorteg          #+#    #+#             */
/*   Updated: 2023/11/26 15:36:11 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include"miniRT.h"

void		intersection_sphere(t_ray *ray, t_sphere *object)
{
	t_vector u_ray;
	t_vector punto_centro;
	t_vector punto_recta;
	t_vector radio;
	double coef[3];
	double	d1;
	double	d2;
	double	t1;
	double	t2;
	double	d;
	double	t;
	double	discriminante;

	u_ray = normalize_vector(vector_init (ray->line.Ux,ray->line.Uy,ray->line.Uz));
	punto_recta = vector_init (ray->line.x0,ray->line.y0,ray->line.z0);
	punto_centro.x = ray->line.x0 - object->sp_point.x;
	punto_centro.y = ray->line.y0 - object->sp_point.y;
	punto_centro.z = ray->line.z0 - object->sp_point.z;

	coef[0] = producto_escalar(u_ray,u_ray);
	coef[1] = 2 * (producto_escalar(u_ray,punto_centro));
	coef[2] = producto_escalar(punto_centro,punto_centro) - pow(object->sp_diameter/2,2);
	discriminante = pow(coef[1],2) - 4 * coef[0] *coef[2];
	if (discriminante < 0)
		return;
	//else if ( discriminante == 0)
	//	d = - coef[1]/(2 * coef[0]);
	else
	{
		d1 = modulo(escalarxvector(((-coef[1]+ sqrt(discriminante))/ 2 * coef[0]),u_ray));
		t1 = (-coef[1]+ sqrt(discriminante))/ 2 * coef[0];
		d2 = modulo(escalarxvector(((-coef[1]-sqrt(discriminante))/ 2 * coef[0]),u_ray));
		t2 = (-coef[1] -sqrt(discriminante))/ 2 * coef[0];

	}
	if (t1 < 0 && t2 < 0)
	{
		//printf(" t1 = %f t2 = %f d1 = %f d2 = %f\n",t1,t2,d1,d2);

		return;
	}
	else if ( t1 >= 0)
		d = d1;
	if (t2 > 0 && (d2 < d1|| t1 < 0))
		d = d2;
	//printf(" t1 = %f t2 = %f d1 = %f d2 = %f\n",t1,t2,d1,d2);
	//printf("coef[%f,%f,%f]\n",coef[0],coef[1],coef[2]);
	radio = vectorminus(vectoradd(escalarxvector(d,normalize_vector(u_ray)) ,punto_recta),object->sp_point); //vectoradd(escalarxvector(d,u_norm), punto_recta);
	if (ray->colision == 0 || (ray->distance > modulo(escalarxvector(d,u_ray)) && producto_escalar(radio,u_ray) <= 0))
		ray_update(ray, object->sp_color, modulo(escalarxvector(d,normalize_vector(u_ray))), radio);//bad unorm
}

void	intersection_plane(t_ray *ray, t_plane *object)
{
	//todo

	double	d;
	double	t;

	t_vector	punto_recta;
	t_vector	u_norm;
	t_vector	o_norm;


	punto_recta.x =ray->line.x0;
	punto_recta.y =ray->line.y0;
	punto_recta.z =ray->line.z0;

	u_norm.x = ray->line.Ux;
	u_norm.y = ray->line.Uy;
	u_norm.z = ray->line.Uz;

	o_norm.x = object->p_surface.A;
	o_norm.y = object->p_surface.B;
	o_norm.z = object->p_surface.C;
	if (producto_escalar(o_norm,u_norm) >= 0)
		return;

	//printf("vector plano x vector recta %f modulo plano %f y modilo recta %f\n",ray->nvector.x,ray->nvector.y,ray->nvector.z);
	t = - (object->p_surface.D + producto_escalar(o_norm,punto_recta))/producto_escalar(o_norm,u_norm);

	// distvect = vectoradd(punto_recta,escalarxvector(t,u_norm));
	// distvect = vectorminus
	d = modulo(escalarxvector(t,u_norm));

	//printf("t de solucion %f distance %f and ray colision distance %f \n",t ,d,ray->distance);

	if (ray->colision == 0 || (ray->distance >= d && producto_escalar(o_norm,u_norm) <= 0))
	{
		//printf("t de solucion %f distance %f and ray colision distance %f \n",t ,d,ray->distance);
		ray_update(ray, object->p_color, d,o_norm);
		//printf("ray = (%f,%f,%f) and distance %f angle in degrees %f\n",o_norm.x,o_norm.y,o_norm.z,d, acos(2*M_PI*producto_escalar(u_norm,o_norm)/(360*modulo(u_norm)*modulo(o_norm))));

	}
}

void ray_update(t_ray *ray, t_rgb object_color, double d,t_vector normal_colision)
{
		ray->colision = 1;
		ray->colision_point.x = ray->line.x0 + d*ray->line.Ux;
		ray->colision_point.y = ray->line.y0 + d*ray->line.Uy;
		ray->colision_point.z = ray->line.z0 + d*ray->line.Uz;
		ray->color = object_color;
		ray->n_colision_vector = normal_colision;
		ray->distance = d;

}
void	intersection_cylinder (t_ray *ray,t_cylinder *object)
{
	//double	discriminante;
	t_vector u_norm;
	//t_vector c_norm;
	t_vector punto_centro;
	t_vector punto_recta;
	//double	d;

	u_norm.x = ray->line.Ux;
	u_norm.y = ray->line.Uy;
	u_norm.z = ray->line.Uz;
	punto_recta.x =ray->line.x0;
	punto_recta.y =ray->line.y0;
	punto_recta.z =ray->line.z0;
	u_norm = normalize_vector (u_norm);
	//c_norm = normalize_vector (object->c_direction);
	punto_centro.x = ray->line.x0 - object->c_point.x;
	punto_centro.y = ray->line.y0 - object->c_point.y;
	punto_centro.z = ray->line.z0 - object->c_point.z;
	// 1 intersect with the infinite cylinder
	intersection_cylinder1(ray, object); //HECHO!!!!
	// 2 check if the intersection is between the planes
	intersection_cylinder_planes(ray,object);
	// 3 intersect with each plane
	// 4 determine if the intersections are inside the caps
	// 5 choose the minimal



	//printf ("1 = %f\n2 = %f\n3 - %f\n ",c_norm.x,c_norm.y,c_norm.z);
	// discriminante = pow(producto_escalar(c_norm,punto_centro),2) - pow(producto_escalar (u_norm,c_norm),2)*(pow(modulo(punto_centro),2) - pow(object->c_diameter/2,2));
	// //printf("discriminante = %f\n",discriminante);
	// if (discriminante < 0)
	// {
	// 	//no colision, no point, no normal
	// 	//ray->colision = 0;
	// 	return ;
	// }
	// else if ( discriminante == 0)
	// 	d = -producto_escalar(punto_centro,c_norm);
	// else
	// {
	// 	d = -producto_escalar(punto_centro,c_norm) + sqrt(discriminante);
	// 	if (-producto_escalar(c_norm,punto_centro) - sqrt(discriminante) < d)
	// 		d = -producto_escalar(punto_centro,c_norm) - sqrt(discriminante);
	// }



}
void	intersection_cylinder1 (t_ray *ray,t_cylinder *object)
{
	double	discriminante;
	t_vector u_norm;
	t_vector c_norm;
	t_vector punto_centro;
	t_vector punto_centro2;
	t_vector punto_recta;
	t_vector s_norm;
	t_vector r_norm;
	double	d;
	double coef[3];
	double uperc;
	t_vector	ccylinder;

	u_norm.x = ray->line.Ux;
	u_norm.y = ray->line.Uy;
	u_norm.z = ray->line.Uz;
	punto_recta.x =ray->line.x0;
	punto_recta.y =ray->line.y0;
	punto_recta.z =ray->line.z0;
	//u_norm = normalize_vector (u_norm);

	//c_norm = escalarxvector (object->c_height,c_norm);
	punto_centro.x = ray->line.x0 - object->c_point.x - object->c_direction.x * object->c_height/2;
	punto_centro.y = ray->line.y0 - object->c_point.y - object->c_direction.y * object->c_height/2;
	punto_centro.z = ray->line.z0 - object->c_point.z - object->c_direction.z * object->c_height/2;
	punto_centro2.x = ray->line.x0 - object->c_point.x + object->c_direction.x * object->c_height/2;
	punto_centro2.y = ray->line.y0 - object->c_point.y + object->c_direction.y * object->c_height/2;
	punto_centro2.z = ray->line.z0 - object->c_point.z + object->c_direction.z * object->c_height/2;
	c_norm = vectorminus(punto_centro2,punto_centro);
	uperc = producto_escalar(u_norm,c_norm);

	coef[0] = producto_escalar(vectorminus(u_norm,escalarxvector(uperc,c_norm)),vectorminus(u_norm,escalarxvector(uperc,c_norm)));
	coef[1] = 2 * (producto_escalar(vectorminus(u_norm,escalarxvector(uperc,c_norm)),vectorminus(punto_centro,escalarxvector(producto_escalar(punto_centro,c_norm),c_norm))));
	coef[2] = producto_escalar(vectorminus(punto_centro,escalarxvector(producto_escalar(punto_centro,c_norm),c_norm)),vectorminus(punto_centro,escalarxvector(producto_escalar(punto_centro,c_norm),c_norm))) - pow(object->c_diameter/2,2);

	discriminante = pow(coef[1],2) - 4 * coef[0] * coef [2];

	if (discriminante < 0)//(producto_escalar(c_norm,vectorminus(object->c_point,punto_centro)) > 0 && producto_escalar(c_norm,vectorminus(object->c_point,punto_centro2)) > 0))
		return;
	else if (discriminante == 0)
		d = - coef[1] / (2 * coef[0]);
	else
	{
		d = - coef[1] / (2 * coef[0]) + sqrt(discriminante);
		if ( - coef[1] / (2 * coef[0]) - sqrt(discriminante) < d)
			d =  - coef[1] / (2 * coef[0]) - sqrt(discriminante);
	}
	s_norm.x = ray->line.Ux;
	s_norm.y = ray->line.Uy;
	s_norm.z = ray->line.Uz;
	r_norm = vectorminus(punto_centro2,punto_centro);
	ccylinder = vectoradd(punto_recta,escalarxvector(d,s_norm));
	//printf("solucion (%f,%f,%f) and product %f\n",r_norm.x,r_norm.y,r_norm.z,producto_escalar(r_norm,vectorminus(punto_centro,ccylinder)));
	if ((producto_escalar(r_norm,vectorminus(punto_centro,ccylinder))) > 0 || producto_escalar(r_norm,vectorminus(punto_centro2,ccylinder)) < 0)
		return;
	if (ray->colision == 0 || ray->distance > d)
	{
		//printf("discriminante = %f dist = %f, cil = %f\n",discriminante,ray->distance ,d);
		ray_update(ray, object->c_color, d, s_norm);//bad s_norm
	}

}
void	intersection_cylinder_planes(t_ray *ray,t_cylinder *object)
{
	t_vector u_norm;
	//t_vector c_norm;
	t_vector punto_centro;
	t_vector punto_centro2;
	t_vector punto_recta;

	u_norm.x = ray->line.Ux;
	u_norm.y = ray->line.Uy;
	u_norm.z = ray->line.Uz;
	punto_recta.x =ray->line.x0;
	punto_recta.y =ray->line.y0;
	punto_recta.z =ray->line.z0;

	//c_norm = escalarxvector (object->c_height,c_norm);
	punto_centro.x = ray->line.x0 - object->c_point.x - object->c_direction.x * object->c_height/2;
	punto_centro.y = ray->line.y0 - object->c_point.y - object->c_direction.y * object->c_height/2;
	punto_centro.z = ray->line.z0 - object->c_point.z - object->c_direction.z * object->c_height/2;
	punto_centro2.x = ray->line.x0 - object->c_point.x + object->c_direction.x * object->c_height/2;
	punto_centro2.y = ray->line.y0 - object->c_point.y + object->c_direction.y * object->c_height/2;
	punto_centro2.z = ray->line.z0 - object->c_point.z + object->c_direction.z * object->c_height/2;
	//c_norm = vectorminus(punto_centro2,punto_centro);
}
