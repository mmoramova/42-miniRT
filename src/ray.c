/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 13:49:12 by josorteg          #+#    #+#             */
/*   Updated: 2023/12/09 13:26:22 by josorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ray_init(t_ray *ray, bool type, t_vector v1, t_vector v2)
{
	ray->color.rgb = 0;
	ray->n_colision_vector = vector_init(0, 0, 0);
	ray->distance = 30000000;
	ray->colision = 0;
	ray->line = (l_create (v1, v2));
	ray->line.l_vec = v_norm(ray->line.l_vec);
	ray->type = type;
}

int	ray_camera(t_scene *scene, t_pixel pos)
{
	t_vector	width;
	t_vector	hight;
	t_vector	init_point;
	t_ray		ray_camera;

	width = scene->camera.c_left;
	hight = scene->camera.c_up;
	init_point.x = scene->camera.c_ray.x + width.x + hight.x
		- 2 * pos.x * (width.x / scene->mlx.win_size.x)
		- 2 * pos.y * (hight.x / scene->mlx.win_size.y);
	init_point.y = scene->camera.c_ray.y + width.y + hight.y
		- 2 * pos.x * (width.y / scene->mlx.win_size.x)
		- 2 * pos.y * (hight.y / scene->mlx.win_size.y);
	init_point.z = scene->camera.c_ray.z + width.z + hight.z
		- 2 * pos.x * (width.z / scene->mlx.win_size.x)
		- 2 * pos.y * (hight.z / scene->mlx.win_size.y);
	ray_init(&ray_camera, 0, scene->camera.c_point, init_point);
	intersection_vision (scene, &ray_camera);
	set_color(scene, &ray_camera);
	return (ray_camera.color.rgb);
}

bool	ray_light(t_scene *scene, t_ray *ray, t_light *light)
{
	t_ray	ray_light;
	double	distance_lc;

	ray_init(&ray_light, 1, light->l_point, ray->colision_point);
	ray_light.c_orderref = ray->c_orderref;
	intersection_vision(scene, &ray_light);
	distance_lc = v_mod(v_substr(light->l_point, ray->colision_point));
	if ((distance_lc * 0.99) <= ray_light.distance)
		return (0);
	return (1);
}

void	ray_update(t_ray *ray, t_rgb object_color, double d, t_vector normal_colision, int orderref)
{
	t_vector	nray;

	//if (ray->type == 1 && orderref == ray->c_orderref)
	//	return ;
	ray->colision = 1;
	nray = v_norm(ray->line.l_vec);
	ray->colision_point = v_sum(ray->line.l_point, v_multd(d,nray));
	ray->color = object_color;
	ray->n_colision_vector = normal_colision;
	ray->distance = d;
	//delete!!
	orderref = 5;
//	if (ray->type == 0)
	//	ray->c_orderref = orderref;
}
