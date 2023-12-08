/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 13:49:12 by josorteg          #+#    #+#             */
/*   Updated: 2023/12/08 17:02:13 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"miniRT.h"

int	ray_color(t_scene *scene,t_pixel pos)
{
	t_vector	with;
	t_vector	higt;
	t_vector	init;
	t_ray		ray_vision;

	with = scene->camera.c_left;
	higt = scene->camera.c_up;
	init.x = scene->camera.c_ray.x + with.x + higt.x - 2 * pos.x * (with.x/scene->mlx.win_size.x) - 2 * pos.y *(higt.x/scene->mlx.win_size.y);
	init.y = scene->camera.c_ray.y + with.y + higt.y - 2 * pos.x * (with.y/scene->mlx.win_size.x) - 2 * pos.y *(higt.y/scene->mlx.win_size.y);
	init.z = scene->camera.c_ray.z + with.z + higt.z - 2 * pos.x * (with.z/scene->mlx.win_size.x) - 2 * pos.y *(higt.z/scene->mlx.win_size.y);

	//calculate the ray vector
	ray_vision.color.rgb = 0;
	ray_vision.n_colision_vector = vector_init(0,0,0);
	ray_vision.distance = 30000000;
	ray_vision.colision = 0;
	ray_vision.line = (l_create (scene->camera.c_point,init));
	ray_vision.type = 0;
	intersection_vision (scene, &ray_vision);

	set_color(scene, &ray_vision);

	return(ray_vision.color.rgb);
}
void intersection_vision (t_scene *scene, t_ray *ray)
{
	t_list	*sp_list;
	t_list	*p_list;
	t_list	*c_list;

	sp_list = scene->spheres;
	p_list = scene->planes;
	c_list = scene->cylinders;

	if (c_list)
	{
		while (c_list->content != NULL)
		{
			intersection_cylinder_test(ray,(t_cylinder*) c_list->content);
			c_list = c_list -> next;
		}
	}
	if (sp_list)
	{
		while (sp_list->content != NULL)
		{
			intersection_sphere (ray,(t_sphere*) sp_list->content);
			sp_list = sp_list -> next;
		}
	}
	if (p_list)
	{
		while (p_list->content != NULL)
		{
			intersection_plane (ray,(t_plane*) p_list->content);
			p_list = p_list -> next;
		}
	}
	return ;
}

bool	check_intersection (t_scene *scene, t_ray *ray, t_light *light)
{
	t_ray	ray_light;
	t_vector	light_pos;
	double	distance_lc;

	ray_light.color.rgb = 0;
	ray_light.n_colision_vector = vector_init(0,0,0);
	ray_light.distance = 30000000;
	ray_light.colision = 0;
	ray_light.line = (l_create (light->l_point,ray->colision_point));
	ray_light.type = 1;
	ray_light.c_orderref = ray->c_orderref;

	intersection_vision (scene, &ray_light);
	light_pos = ray->line.l_point;
	distance_lc = v_mod(v_substr(light->l_point,ray->colision_point));

	if ((distance_lc) <= ray_light.distance )
		return(0);
	return 1;
}
