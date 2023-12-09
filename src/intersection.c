/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:27:38 by josorteg          #+#    #+#             */
/*   Updated: 2023/12/09 11:01:49 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include"miniRT.h"

void	intersection_vision(t_scene *scene, t_ray *ray)
{
	t_list	*sp_list;
	t_list	*p_list;
	t_list	*c_list;

	sp_list = scene->spheres;
	p_list = scene->planes;
	c_list = scene->cylinders;
	while (c_list && c_list->content != NULL)
	{
		intersection_cylinder(ray, (t_cylinder *) c_list->content);
		c_list = c_list -> next;
	}
	while (sp_list && sp_list->content != NULL)
	{
		intersection_sphere(ray, (t_sphere *) sp_list->content);
		sp_list = sp_list -> next;
	}
	while (p_list && p_list->content != NULL)
	{
		intersection_plane(ray, (t_plane *) p_list->content);
		p_list = p_list -> next;
	}
	return ;
}

void	intersection_sphere(t_ray *ray, t_sphere *object)
{
	t_vector u_ray;
	t_vector punto_centro;
	t_vector radio;
	double coef[3];
	double	d1;
	double	d2;
	double	t1;
	double	t2;
	double	d;
	double	discriminante;

	u_ray = v_norm(ray->line.l_vector);
	punto_centro = v_substr(ray->line.l_point, object->sp_point);
	coef[0] = v_inner(u_ray,u_ray);
	coef[1] = 2 * (v_inner(u_ray,punto_centro));
	coef[2] = v_inner(punto_centro,punto_centro) - pow(object->sp_diameter/2,2);
	discriminante = pow(coef[1],2) - 4 * coef[0] *coef[2];
	if (discriminante < 0)
		return;
	d1 = v_mod(v_multd(((-coef[1]+ sqrt(discriminante))/ 2 * coef[0]),u_ray));
	t1 = (-coef[1]+ sqrt(discriminante))/ 2 * coef[0];
	d2 = v_mod(v_multd(((-coef[1]-sqrt(discriminante))/ 2 * coef[0]),u_ray));
	t2 = (-coef[1] -sqrt(discriminante))/ 2 * coef[0];
	if (t1 < 0 && t2 < 0)
		return;
	else if ( t1 >= 0)
		d = d1;
	if (t2 > 0 && (d2 < d1|| t1 < 0))
		d = d2;
	radio = v_substr(v_sum(v_multd(d,v_norm(u_ray)) ,ray->line.l_point),object->sp_point); //v_sum(v_multd(d,u_norm), punto_recta);
	if (ray->colision == 0 || (ray->distance > v_mod(v_multd(d,u_ray))/* && v_inner(radio,u_ray) <= 0)*/))
		ray_update(ray, object->sp_color, d, radio, object->sp_orderref);//bad unorm
}

void	intersection_plane(t_ray *ray, t_plane *object)
{
	double	t;
	t_vector	u_norm;
	t_vector	o_norm;
	t_vector	solution;

	u_norm = ray->line.l_vector;
	u_norm = v_norm(u_norm);
	o_norm.x = object->p_surface.A;
	o_norm.y = object->p_surface.B;
	o_norm.z = object->p_surface.C;
	if (v_inner(o_norm,u_norm) == 0 )
	 	return;
	t = - (object->p_surface.D + v_inner(o_norm,ray->line.l_point))/v_inner(o_norm,u_norm);
	solution = v_multd(t,u_norm);
	if (v_inner(u_norm,solution) < 0)
		return;
	if (v_inner(o_norm,u_norm) >= 0 )
		o_norm = v_multd(-1,o_norm);
	if (ray->colision == 0 || (ray->distance >= t))
		ray_update(ray, object->p_color, t,o_norm, object->p_orderref);
}


void	intersection_cylinder_plane(t_ray *ray,t_cylinder *object,t_vector point,t_plane plane)
{
	double	t;
	t_vector	u_norm;
	t_vector	o_norm;
	t_vector	solution;
	double		condition;

	u_norm = ray->line.l_vector;
	u_norm = v_norm(u_norm);
	o_norm.x = plane.p_surface.A;
	o_norm.y = plane.p_surface.B;
	o_norm.z = plane.p_surface.C;
	point = v_substr(point,ray->line.l_point);
	if (v_inner(o_norm,u_norm) == 0 )
	 	return;
	t = - (plane.p_surface.D + v_inner(o_norm,ray->line.l_point))/v_inner(o_norm,u_norm);
	solution = v_multd(t,u_norm);
	if (t < 0)
		return;
	if (v_inner(o_norm,u_norm) >= 0 )
		o_norm = v_multd(-1,o_norm);
	condition = v_inner(v_substr(solution,point),v_substr(solution,point));
	if ((ray->colision == 0 ||ray->distance >= t) && (condition <= pow(object->c_diameter/2,2)))
		ray_update(ray, object->c_color, t,o_norm, object->c_orderref);
}

void	intersection_cylinder(t_ray *ray,t_cylinder *object)
{
	t_vector 	r_norm;
	t_vector	v_nvec;
	t_vector	s_norm;
	t_vector 	centro_base;
	t_vector	VoCb;
	t_vector	solution;
	double coef[3];
	double		discriminante;
	double		d;

	r_norm = v_norm(ray->line.l_vector);
	v_nvec = v_norm(v_substr(object->c_upper,object->c_down));
	centro_base = v_substr(object->c_down, ray->line.l_point);
	VoCb = v_substr(ray->line.l_point, object->c_down);
	intersection_cylinder_plane (ray,object,object->c_down,object->down_p);
	intersection_cylinder_plane (ray,object,object->c_upper,object->upper_p);
	coef[0] = 1 - pow (v_inner(r_norm,v_nvec),2);
	coef[1] = 2*(v_inner(r_norm,VoCb) - v_inner(r_norm,v_nvec)*v_inner(VoCb,v_nvec));
	coef[2] = v_inner(VoCb,VoCb) - pow(v_inner(VoCb,v_nvec),2) - pow(object->c_diameter/2,2);
	discriminante = pow(coef[1],2) - 4 * coef[0] * coef [2];
	if (discriminante < 0)
		return;
	d = (- coef[1] + sqrtl(discriminante)) / (2 * coef[0]);
	if ((- coef[1] - sqrtl(discriminante)) / (2 * coef[0]) < d && (- coef[1] - sqrtl(discriminante)) / (2 * coef[0])>=0)
		d =  (- coef[1] - sqrtl(discriminante))/ (2 * coef[0]);
	if (d < 0)
		return;
	solution = v_multd (d,r_norm);
	s_norm = v_substr(solution,v_sum(centro_base,v_multd(v_inner(v_substr(solution,centro_base),v_nvec),v_nvec)));
	if ((ray->colision == 0 ||ray->distance >= d) /* && v_inner(s_norm,r_norm)<= 0*/ && (v_inner(v_substr(solution,centro_base),v_nvec) < object->c_height && v_inner(v_substr(solution,centro_base),v_nvec) >= 0))
			ray_update(ray, object->c_color, d, s_norm, object->c_orderref);
}




