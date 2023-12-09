/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:27:38 by josorteg          #+#    #+#             */
/*   Updated: 2023/12/09 13:18:41 by josorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	intersection_vision(t_scene *scene, t_ray *r)
{
	t_list	*sp_list;
	t_list	*p_list;
	t_list	*c_list;

	sp_list = scene->spheres;
	p_list = scene->planes;
	c_list = scene->cylinders;
	while (c_list && c_list->content != NULL)
	{
		intersection_cylinder(r, (t_cylinder *) c_list->content);
		c_list = c_list -> next;
	}
	while (sp_list && sp_list->content != NULL)
	{
		intersection_sphere(r, (t_sphere *) sp_list->content);
		sp_list = sp_list -> next;
	}
	while (p_list && p_list->content != NULL)
	{
		intersection_plane(r, (t_plane *) p_list->content);
		p_list = p_list -> next;
	}
	return ;
}

void	intersection_sphere(t_ray *r, t_sphere *obj)
{
	t_vector	punto_centro;
	t_vector	rad;
	double		c[6];
	t_line		l;

	l = r->line;
	punto_centro = v_substr(l.l_point, obj->sp_point);
	c[0] = v_inner(l.l_vector, l.l_vector);
	c[1] = 2 * (v_inner(l.l_vector, punto_centro));
	c[2] = v_inner(punto_centro, punto_centro) - pow(obj->sp_diameter / 2, 2);
	c[3] = pow(c[1], 2) - 4 * c[0] * c[2];
	c[4] = (-c[1] + sqrt(fabs(c[3]))) / (2 * c[0]);
	c[5] = (-c[1] - sqrt(fabs(c[3]))) / (2 * c[0]);
	if (c[5] < c[4] && c[5] >= 0)
		c[4] = (-c[1] - sqrt(fabs(c[3]))) / (2 * c[0]);
	if (c[4] < 0 || c[3] < 0)
		return ;
	rad = v_substr(v_sum(v_multd(c[4], v_norm(l.l_vector)), l.l_point), obj->sp_point);
	if (v_inner(rad, l.l_vector) >= 0)
		rad = v_multd(-1, rad);
	if (r->colision == 0 || (r->distance > v_mod(v_multd(c[4], l.l_vector)) && v_inner(rad, l.l_vector) <= 0))
		ray_update(r, obj->sp_color, c[4], rad, obj->sp_orderref);
}

void	intersection_plane(t_ray *r, t_plane *obj)
{
	double		t;
	t_vector	o_norm;
	t_vector	solution;

	o_norm.x = obj->p_surface.a;
	o_norm.y = obj->p_surface.b;
	o_norm.z = obj->p_surface.c;
	if (v_inner(o_norm, r->line.l_vector) == 0)
		return ;
	t = -(obj->p_surface.d + v_inner(o_norm, r->line.l_point)) / v_inner(o_norm, r->line.l_vector);
	solution = v_multd(t, r->line.l_vector);
	if (v_inner(r->line.l_vector, solution) < 0)
		return ;
	if (v_inner(o_norm, r->line.l_vector) >= 0)
		o_norm = v_multd(-1, o_norm);
	if (r->colision == 0 || (r->distance >= t))
		ray_update(r, obj->p_color, t, o_norm, obj->p_orderref);
}

void	intersection_cylinder_plane(t_ray *r, t_cylinder *obj, t_vector point, t_plane plane)
{
	double		t;
	t_vector	o_norm;
	t_vector	solution;
	double		condition;

	o_norm.x = plane.p_surface.a;
	o_norm.y = plane.p_surface.b;
	o_norm.z = plane.p_surface.c;
	point = v_substr(point, r->line.l_point);
	if (v_inner(o_norm, r->line.l_vector) == 0)
		return ;
	t = -(plane.p_surface.d + v_inner(o_norm, r->line.l_point)) / v_inner(o_norm, r->line.l_vector);
	solution = v_multd(t, r->line.l_vector);
	if (t < 0)
		return ;
	if (v_inner(o_norm, r->line.l_vector) >= 0)
		o_norm = v_multd(-1, o_norm);
	condition = v_inner(v_substr(solution, point), v_substr(solution, point));
	if ((r->colision == 0 || r->distance >= t) && (condition <= pow(obj->c_diameter / 2, 2)))
		ray_update(r, obj->c_color, t, o_norm, obj->c_orderref);
}

void	intersection_cylinder(t_ray *r, t_cylinder *obj)
{
	t_vector	s_norm;
	t_vector	cb;
	t_vector	solution;
	double		c[6];

	cb = v_substr(obj->c_down, r->line.l_point);
	intersection_cylinder_plane(r, obj, obj->c_down, obj->down_p);
	intersection_cylinder_plane(r, obj, obj->c_upper, obj->upper_p);
	c[0] = 1 - pow(v_inner(r->line.l_vector, obj->c_vh), 2);
	c[1] = 2 * (v_inner(r->line.l_vector, v_multd(-1, cb)) - v_inner(r->line.l_vector, obj->c_vh) * v_inner(v_multd(-1, cb), obj->c_vh));
	c[2] = v_inner(v_multd(-1, cb), v_multd(-1, cb)) - pow(v_inner(v_multd(-1, cb), obj->c_vh), 2) - pow(obj->c_diameter / 2, 2);
	c[3] = pow(c[1], 2) - 4 * c[0] * c[2];
	c[4] = (-c[1] + sqrt(fabs(c[3]))) / (2 * c[0]);
	c[5] = (-c[1] - sqrt(fabs(c[3]))) / (2 * c[0]);
	if (c[5] < c[4] && c[5] >= 0)
		c[4] = (-c[1] - sqrt(fabs(c[3]))) / (2 * c[0]);
	if (c[4] < 0 || c[3] < 0)
		return ;
	solution = v_multd (c[4], r->line.l_vector);
	s_norm = v_substr(solution, v_sum(cb, v_multd(v_inner(v_substr(solution, cb), obj->c_vh), obj->c_vh)));
	if ((r->colision == 0 || r->distance >= c[4]) /* && v_inner(s_norm,r_norm)<= 0*/ && (v_inner(v_substr(solution, cb), obj->c_vh) < obj->c_height && v_inner(v_substr(solution, cb), obj->c_vh) >= 0))
		ray_update(r, obj->c_color, c[4], s_norm, obj->c_orderref);
}
