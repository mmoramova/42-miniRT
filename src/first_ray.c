/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 13:49:12 by josorteg          #+#    #+#             */
/*   Updated: 2023/11/15 12:07:47 by josorteg         ###   ########.fr       */
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
	init.x = scene->camera.c_inter.x + with.x + higt.x - 2 *pos.x * (with.x/scene->mlx.win_size.x) - 2 * pos.y *(higt.x/scene->mlx.win_size.y);
	init.y = scene->camera.c_inter.y + with.y + higt.y - 2 * pos.x * (with.y/scene->mlx.win_size.x) - 2 * pos.y *(higt.y/scene->mlx.win_size.y);
	init.z = scene->camera.c_inter.z + with.z + higt.z - 2 * pos.x * (with.z/scene->mlx.win_size.x) - 2 *pos.y *(higt.z/scene->mlx.win_size.y);
	//calculate the ray vector
	ray_vision.color.rgb = 0;
	ray_vision.distance = 30000;
	ray_vision.colision = 0;
	ray_vision.line = two_points_line (scene->camera.c_point,init);
	//color = intersection_sphere (ray_vision.line,(t_sphere*) scene->spheres->content);
	intersection_vision (scene, &ray_vision);
	if (ray_vision.color.rgb == 0)
		ray_vision.color.rgb = scene->amblight.al_color.rgb * scene->amblight.al_ratio;
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
			//intersection_plane (ray,(t_plane*) p_list->content);
			p_list = p_list -> next;
		}
	}
	if (c_list)
	{
		while (c_list->content != NULL)
		{
			intersection_cylinder (ray,(t_cylinder*) c_list->content);
			c_list = c_list -> next;
		}
	}
	return ;
}
