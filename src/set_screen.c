/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_screen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:48:20 by josorteg          #+#    #+#             */
/*   Updated: 2023/12/08 22:04:43 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"miniRT.h"

void	screen_set(t_scene *scene)
{
	t_vector	width_v;
	t_vector	hight_v;
	t_vector	north;
	double	fov;

	north = find_normal_vector(scene->camera.c_nvector,1);
	fov = 150;
	//calculate point of intersection between unitari vector and camera plane
	scene->camera.c_ray = v_norm(vector_init(scene->camera.c_point.x + scene->camera.c_nvector.x
		,scene->camera.c_point.y + scene->camera.c_nvector.y
		,scene->camera.c_point.z + scene->camera.c_nvector.z));
	printf("ray = (%f,%f,%f), module %f\n",scene->camera.c_ray.x,scene->camera.c_ray.y,scene->camera.c_ray.z,v_mod(scene->camera.c_ray));
	width_v = v_norm(v_mult(scene->camera.c_ray,north));
	printf("with = (%f,%f,%f)\n",width_v.x,width_v.y,width_v.z);
	hight_v = v_mult(width_v,scene->camera.c_ray);
	printf("higt = (%f,%f,%f)\n",hight_v.x,hight_v.y,hight_v.z);
	scene->camera.c_left = v_multd(2*tan(scene->camera.c_angle/2),width_v);
	scene->camera.c_up = v_multd((2*tan(scene->camera.c_angle/2)*scene->mlx.win_size.y)/scene->mlx.win_size.x,hight_v);
	printf("v_mod left = %f, v_mod up = %f\n",v_mod(scene->camera.c_left),v_mod(scene->camera.c_up));
	scene->camera.c_ray = v_multd(fov,scene->camera.c_ray);
	scene->camera.c_left = v_multd(fov,scene->camera.c_left);
	scene->camera.c_up = v_multd(fov,scene->camera.c_up);
}


