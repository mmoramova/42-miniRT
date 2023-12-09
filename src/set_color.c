/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 13:16:43 by mmoramov          #+#    #+#             */
/*   Updated: 2023/12/02 14:07:49 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	set_color(t_scene *scene, t_ray *ray)
{
	t_list	*l_list;
	t_rgb	final_color;

	final_color = set_rgb("0,0,0");
	final_color = rgb_sum(final_color,
			ambient_color(ray, &scene->amblight));
	l_list = scene->lights;
	while (l_list && l_list->content != NULL)
	{
		if (ray_light(scene, ray, (t_light *) l_list->content) == 0)
		{
			final_color = rgb_sum(final_color,
					diffuse_color (ray, (t_light *) l_list->content));
			final_color = rgb_sum(final_color,
					specular_color (scene, ray, (t_light *) l_list->content));
		}
		l_list = l_list -> next;
	}
	ray->color = rgb_norm(final_color);
}

t_rgb	ambient_color(t_ray *r, t_amblight *a)
{
	t_rgb	ambient_color;

	if (r->color.rgb == 0)
		ambient_color = set_rgb("0,0,0");
	else
		ambient_color = rgb_mult(r->color, rgb_multd(a->al_color, a->al_ratio));
	return (ambient_color);
}

t_rgb	diffuse_color(t_ray *r, t_light *l)
{
	t_rgb		diffuse_color;
	t_vector	o_nvec;
	t_vector	l_nvec;

	o_nvec = v_norm(r->n_colision_vector);
	l_nvec = v_norm(v_substr(l->l_point, r->colision_point));
	if (r->color.rgb == 0)
		diffuse_color = set_rgb("0,0,0");
	else
		diffuse_color = rgb_mult(r->color, rgb_multd(rgb_multd(l->color,
						l->l_brightness), fmax(0, v_inner(l_nvec, o_nvec))));
	return (diffuse_color);
}

t_rgb	specular_color(t_scene *scene, t_ray *r, t_light *l)
{
	t_rgb		specular_color;
	double		spec_factor;
	t_vector	l_nvec;
	t_vector	refl_vec;
	t_vector	view_vec;

	l_nvec = v_norm(v_substr(r->colision_point, l->l_point));
	refl_vec = v_substr(l_nvec, v_multd(2 * v_inner(l_nvec,
				v_norm(r->n_colision_vector)), v_norm(r->n_colision_vector)));
	view_vec = v_norm(v_substr(scene->camera.c_point, r->colision_point));
	spec_factor = pow(fmax(0, v_inner(refl_vec, view_vec)), 32);
	if (r->color.rgb == 0)
		specular_color = set_rgb("0,0,0");
	else
		specular_color = rgb_mult(r->color, rgb_multd(l->color, spec_factor));
	return (specular_color);
}
