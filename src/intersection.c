/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:27:38 by josorteg          #+#    #+#             */
/*   Updated: 2023/12/09 18:28:46 by josorteg         ###   ########.fr       */
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

void	intersection_sphere(t_ray *r, t_sphere *o)
{
	t_vector	punto_centro;
	t_vector	rad;
	double		c[6];
	t_line		l;

	l = r->line;
	punto_centro = v_substr(l.l_point, o->sp_point);
	c[0] = v_inner(l.l_vec, l.l_vec);
	c[1] = 2 * (v_inner(l.l_vec, punto_centro));
	c[2] = v_inner(punto_centro, punto_centro) - pow(o->sp_diameter / 2, 2);
	eq_two_grade(c);
	if (c[4] < 0 || c[3] < 0)
		return ;
	rad = v_substr(v_sum(v_multd(c[4], v_norm(l.l_vec)),
				l.l_point), o->sp_point);
	if (v_inner(rad, l.l_vec) >= 0)
		rad = v_multd(-1, rad);
	if (r->colision == 0 || (r->distance > v_mod(v_multd(c[4], l.l_vec))
			&& v_inner(rad, l.l_vec) <= 0))
		ray_update(r, o->sp_color, c[4], rad);
}

void	intersection_plane(t_ray *r, t_plane *o)
{
	double		t;
	t_vector	o_norm;
	t_vector	solution;

	o_norm.x = o->p_surface.a;
	o_norm.y = o->p_surface.b;
	o_norm.z = o->p_surface.c;
	if (v_inner(o_norm, r->line.l_vec) == 0)
		return ;
	t = -(o->p_surface.d + v_inner(o_norm, r->line.l_point))
		/ v_inner(o_norm, r->line.l_vec);
	solution = v_multd(t, r->line.l_vec);
	if (v_inner(r->line.l_vec, solution) < 0)
		return ;
	if (v_inner(o_norm, r->line.l_vec) >= 0)
		o_norm = v_multd(-1, o_norm);
	if (r->colision == 0 || (r->distance >= t))
		ray_update(r, o->p_color, t, o_norm);
}

void	plane_cyl(t_ray *r, t_cylinder *o, t_vector point, t_plane plane)
{
	double		t;
	t_vector	o_norm;
	t_vector	solution;
	double		condition;

	o_norm.x = plane.p_surface.a;
	o_norm.y = plane.p_surface.b;
	o_norm.z = plane.p_surface.c;
	point = v_substr(point, r->line.l_point);
	if (v_inner(o_norm, r->line.l_vec) == 0)
		return ;
	t = -(plane.p_surface.d + v_inner(o_norm, r->line.l_point))
		/ v_inner(o_norm, r->line.l_vec);
	solution = v_multd(t, r->line.l_vec);
	if (t < 0)
		return ;
	if (v_inner(o_norm, r->line.l_vec) >= 0)
		o_norm = v_multd(-1, o_norm);
	condition = v_inner(v_substr(solution, point), v_substr(solution, point));
	if ((r->colision == 0 || r->distance >= t) && (condition
			<= pow(o->c_diameter / 2, 2)))
		ray_update(r, o->c_color, t, o_norm);
}

void	intersection_cylinder(t_ray *r, t_cylinder *o)
{
	t_vector	s_norm;
	t_vector	cb;
	t_vector	solution;
	double		c[6];

	cb = v_substr(o->c_down, r->line.l_point);
	plane_cyl(r, o, o->c_down, o->down_p);
	plane_cyl(r, o, o->c_upper, o->upper_p);
	c[0] = 1 - pow(v_inner(r->line.l_vec, o->c_vh), 2);
	c[1] = 2 * (v_inner(r->line.l_vec, v_multd(-1, cb)) - v_inner(r->line.l_vec,
				o->c_vh) * v_inner(v_multd(-1, cb), o->c_vh));
	c[2] = v_inner(v_multd(-1, cb), v_multd(-1, cb)) - pow(v_inner(v_multd(-1,
					cb), o->c_vh), 2) - pow(o->c_diameter / 2, 2);
	eq_two_grade(c);
	if (c[4] < 0 || c[3] < 0)
		return ;
	solution = v_multd (c[4], r->line.l_vec);
	s_norm = v_substr(solution, v_sum(cb,
				v_multd(v_inner(v_substr(solution, cb), o->c_vh), o->c_vh)));
	if (v_inner(s_norm, r->line.l_vec) >= 0)
		s_norm = v_multd(-1, s_norm);
	if ((r->colision == 0 || r->distance >= c[4])
		&& (v_inner(v_substr(solution, cb), o->c_vh) < o->c_height
			&& v_inner(v_substr(solution, cb), o->c_vh) >= 0))
		ray_update(r, o->c_color, c[4], s_norm);
}
