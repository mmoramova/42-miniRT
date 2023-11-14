/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 13:49:12 by josorteg          #+#    #+#             */
/*   Updated: 2023/11/14 17:35:52 by josorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"miniRT.h"

int	ray_color(t_scene *scene,t_pixel pos)
{
	t_vector	with;
	t_vector	higt;
	t_vector	init;
	t_ray		ray_vision;
	int		color;

	with = scene->camera.c_left;
	higt = scene->camera.c_up;
	init.x = scene->camera.c_inter.x + with.x + higt.x - 2 *pos.x * (with.x/scene->mlx.win_size.x) - 2 * pos.y *(higt.x/scene->mlx.win_size.y);
	init.y = scene->camera.c_inter.y + with.y + higt.y - 2 * pos.x * (with.y/scene->mlx.win_size.x) - 2 * pos.y *(higt.y/scene->mlx.win_size.y);
	init.z = scene->camera.c_inter.z + with.z + higt.z - 2 * pos.x * (with.z/scene->mlx.win_size.x) - 2 *pos.y *(higt.z/scene->mlx.win_size.y);
	//calculate the ray vector
	ray_vision.color.rgb = 0;
	color = 0;
	ray_vision.line = two_points_line (scene->camera.c_point,init);
	intersection_sfere (ray_vision.line,(t_sphere*) scene->spheres->content);
	if (ray_vision.color.rgb == 0)
		color = scene->amblight.al_color.rgb * scene->amblight.al_ratio;
	return(color);
}

void intersection_vision (t_scene *scene, t_ray *ray)
{

	
}
