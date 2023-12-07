/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:27:38 by josorteg          #+#    #+#             */
/*   Updated: 2023/12/07 19:03:25 by josorteg         ###   ########.fr       */
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
	//double	t;
	double	discriminante;

	u_ray = normalize_vector(ray->line.l_vector);
	punto_recta = ray->line.l_point;
	punto_centro = vectorminus(ray->line.l_point, object->sp_point);

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

	//printf("coef[%f,%f,%f]\n",coef[0],coef[1],coef[2]);
	//printf("punto recta (%f,%f,%f)\n",punto_centro.x,punto_centro.y,punto_centro.z);
	radio = vectorminus(vectoradd(escalarxvector(d,normalize_vector(u_ray)) ,punto_recta),object->sp_point); //vectoradd(escalarxvector(d,u_norm), punto_recta);
	if (ray->colision == 0 || (ray->distance > modulo(escalarxvector(d,u_ray))/* && producto_escalar(radio,u_ray) <= 0)*/))
	{
		ray_update(ray, object->sp_color, d, radio, object->sp_orderref);//bad unorm

	}
}

void	intersection_plane(t_ray *ray, t_plane *object)
{
	double	t;
	t_vector	u_norm;
	t_vector	o_norm;
	t_vector	solution;

	u_norm = ray->line.l_vector;
	u_norm = normalize_vector(u_norm);
	o_norm.x = object->p_surface.A;
	o_norm.y = object->p_surface.B;
	o_norm.z = object->p_surface.C;
	if (producto_escalar(o_norm,u_norm) == 0 )
	 	return;
	t = - (object->p_surface.D + producto_escalar(o_norm,ray->line.l_point))/producto_escalar(o_norm,u_norm);
	solution = escalarxvector(t,u_norm);
	if (producto_escalar(u_norm,solution) < 0)
		return;
	if (producto_escalar(o_norm,u_norm) > 0 )
		o_norm = escalarxvector(-1,o_norm);
	if (ray->colision == 0 || (ray->distance >= t))
		ray_update(ray, object->p_color, t,o_norm, object->p_orderref);
}


void ray_update(t_ray *ray, t_rgb object_color, double d,t_vector normal_colision, int orderref)
{
		t_vector	nray;

		// if (ray->type == 1 && orderref == ray->c_orderref)
		// 	return;
		ray->colision = 1;
		nray = normalize_vector(ray->line.l_vector);
		ray->colision_point = vectoradd(ray->line.l_point,escalarxvector(d,nray));
		ray->color = object_color;
		ray->n_colision_vector = normal_colision;
		ray->distance = d;
		if (ray->type == 0)
			ray->c_orderref = orderref;
}


void	intersection_cylinder_planes(t_ray *ray,t_cylinder *object,t_vector point,t_plane plane)
{
	double	t;
	t_vector	u_norm;
	t_vector	o_norm;
	t_vector	solution;
	double		condition;

	u_norm = ray->line.l_vector;
	u_norm = normalize_vector(u_norm);
	o_norm.x = plane.p_surface.A;
	o_norm.y = plane.p_surface.B;
	o_norm.z = plane.p_surface.C;
	point = vectorminus(point,ray->line.l_point);
	if (producto_escalar(o_norm,u_norm) == 0 )
	 	return;
	t = - (plane.p_surface.D + producto_escalar(o_norm,ray->line.l_point))/producto_escalar(o_norm,u_norm);
	solution = escalarxvector(t,u_norm);
	if (t<0)
		return;
	if (producto_escalar(o_norm,u_norm) > 0 )
		o_norm = escalarxvector(-1,o_norm);
	condition = producto_escalar(vectorminus(solution,point),vectorminus(solution,point));
	if ((ray->colision == 0 ||ray->distance >= t) && (condition <= pow(object->c_diameter/2,2)))
		ray_update(ray, object->c_color, t,o_norm, object->c_orderref);
}
//test
//test
//test
//test
//test
void	intersection_cylinder_test (t_ray *ray,t_cylinder *object)
{
	t_vector 	r_norm;
	t_vector	v_norm;
	t_vector	s_norm;
	t_vector 	centro_base;
	//t_vector 	centro_higt;
	t_vector	VoCb;
	t_vector	solution;
	double coef[3];
	double		discriminante;
	double		d;

	r_norm = normalize_vector(ray->line.l_vector);
	v_norm = normalize_vector(vectorminus(object->c_upper,object->c_down));
	centro_base = vectorminus(object->c_down, ray->line.l_point);
	//centro_higt = vector_init(object->c_upper.x,object->c_upper.y,object->c_upper.z);
	VoCb = vectorminus(ray->line.l_point, object->c_down);
	intersection_cylinder_planes (ray,object,object->c_down,object->down_p);
	intersection_cylinder_planes (ray,object,object->c_upper,object->upper_p);
	coef[0] = 1 - pow (producto_escalar(r_norm,v_norm),2);
	coef[1] = 2*(producto_escalar(r_norm,VoCb) - producto_escalar(r_norm,v_norm)*producto_escalar(VoCb,v_norm));
	coef[2] = producto_escalar(VoCb,VoCb) - pow(producto_escalar(VoCb,v_norm),2) - pow(object->c_diameter/2,2);
	discriminante = pow(coef[1],2) - 4 * coef[0] * coef [2];

	if (discriminante >= 0)
	{
		d = (- coef[1] + sqrtl(discriminante)) / (2 * coef[0]);
		if ((- coef[1] - sqrtl(discriminante)) / (2 * coef[0]) < d && (- coef[1] - sqrtl(discriminante)) / (2 * coef[0])>=0)
			d =  (- coef[1] - sqrtl(discriminante))/ (2 * coef[0]);

	}
		else
	{
		return;
	}
	if (d < 0)
		return;
	solution = escalarxvector (d,r_norm);


	s_norm = vectorminus(solution,vectoradd(centro_base,escalarxvector(producto_escalar(vectorminus(solution,centro_base),v_norm),v_norm)));
	if ((ray->colision == 0 ||ray->distance > d) /* && producto_escalar(s_norm,r_norm)<= 0*/ && (producto_escalar(vectorminus(solution,centro_base),v_norm) < object->c_height && producto_escalar(vectorminus(solution,centro_base),v_norm) > 0))
			ray_update(ray, object->c_color, d, s_norm, object->c_orderref);//bad s_norm

}


