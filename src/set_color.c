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

#include"miniRT.h"

void	set_color(t_scene *scene, t_ray *ray)
{
	t_list	*l_list;
	t_rgb	final_color;

	final_color = set_rgb("0,0,0");
	final_color = rgb_sum(final_color, set_ambient_color(ray, &scene->amblight));
	l_list = scene->lights;
	while (l_list && l_list->content != NULL)
	{
		if (check_intersection(scene, ray, (t_light*) l_list->content) == 0)
		{
			final_color = rgb_sum(final_color, set_diffuse_color (ray, (t_light*) l_list->content));
			final_color = rgb_sum(final_color, set_specular_color (scene, ray, (t_light*) l_list->content));
		}
		l_list = l_list -> next;
	}
	ray->color = rgb_normalize(final_color);
}

t_rgb	set_ambient_color (t_ray *ray, t_amblight *amblight)
{
	t_rgb	ambient_color;
	t_rgb	o_color = ray->color;
	double	al_ratio = amblight->al_ratio;
	t_rgb	al_color = amblight->al_color;

	if (ray->color.rgb == 0)
		ambient_color = set_rgb("0,0,0");
	else
		ambient_color = rgb_mult(o_color, rgb_multd(al_color,al_ratio));
	return (ambient_color);
}

t_rgb	set_diffuse_color (t_ray *ray, t_light *light)
{
	t_vector	l_point = light->l_point;
	t_vector	o_point = ray->colision_point;
	double		l_brightness = light->l_brightness;

	t_rgb		diffuse_color;
	t_rgb		l_color = light->color;

	t_vector	o_nvector = normalize_vector(ray->n_colision_vector);
	t_vector	l_nvector = normalize_vector(vectorminus(l_point, o_point));

	if (ray->color.rgb == 0)
		diffuse_color = set_rgb("0,0,0");
	else
		diffuse_color = rgb_mult(ray->color, rgb_multd(rgb_multd(l_color,l_brightness),fmax(0, producto_escalar(l_nvector,o_nvector))));
	return(diffuse_color);
}

t_rgb	set_specular_color (t_scene *scene, t_ray *ray, t_light *light)
{
	t_vector	c_point = scene->camera.c_point;
	t_vector	l_point = light->l_point;
	t_vector	o_point = ray->colision_point;
	t_rgb		specular_color;
	t_rgb		s_color = light->color;
	double		specular_factor;
	t_rgb		o_color = ray->color;

	t_vector	o_nvector = normalize_vector(ray->n_colision_vector);
	t_vector	l_nvector = normalize_vector(vectorminus(o_point, l_point));

	t_vector	reflection_vector = vectorminus(l_nvector, escalarxvector(2 * producto_escalar(l_nvector, o_nvector), o_nvector));
	t_vector	view_vector = normalize_vector(vectorminus(c_point, o_point));
	specular_factor = pow(fmax(0, producto_escalar(reflection_vector,view_vector)),32);

	if (ray->color.rgb == 0)
		specular_color = set_rgb("0,0,0");
	else
		specular_color = rgb_mult(o_color,rgb_multd(s_color,specular_factor));
	return(specular_color);
}
