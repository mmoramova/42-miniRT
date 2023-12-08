/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_screen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:48:20 by josorteg          #+#    #+#             */
/*   Updated: 2023/12/08 16:58:51 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"miniRT.h"


void	init_screen(t_scene *scene)
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
	//D_plane (&scene->camera);
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
void D_plane (t_camera *camera)
{
	camera->c_surface.A = camera->c_ray.x;
	camera->c_surface.B = camera->c_ray.y;
	camera->c_surface.C = camera->c_ray.z;
	camera->c_surface.D = -(camera->c_surface.A*(camera->c_point.x) +
								camera->c_surface.B*( camera->c_point.y) +
								camera->c_surface.C*(camera->c_point.z));
	//printf("camera plane  %fx + %fy + %fz + %f = 0\n",camera->c_surface.A,camera->c_surface.B,camera->c_surface.C,camera->c_surface.D);

}

t_vector	find_normal_vector (t_vector v1, double lengh)
{
	t_vector result;

	(0 || (result.x = 0) || (result.y = 0) || (result.z = 0));
	if (v1.x != 0 && v1.y != 0 && v1.z != 0)
	{
		result.x = 1;
		result.y = 1;
		result.z = -(v1.x * result.x + v1.y * result.y)/v1.z;
	}
	else
	{
		if (v1.x == 0)
			result.x = 1;
		if (v1.y == 0)
			result.y = 1;
		if (v1.z == 0)
			result.z = 1;
	}
	result = v_norm (result);
	result.x= result.x * lengh;
	result.y= result.y * lengh;
	result.z= result.z * lengh;
	//printf("vector (%f,%f,%f), con v_mod %f",result.x,result.y,result.z,sqrt(pow(result.x,2) + pow(result.y,2) + pow(result.z,2)));
	return (result);
}
