/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_screen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:48:20 by josorteg          #+#    #+#             */
/*   Updated: 2023/12/06 16:39:16 by josorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"miniRT.h"


void	init_screen(t_scene *scene)
{
	// double		dhigt;
	// double		dwith;
	t_vector	with_v;
	t_vector	higt_v;
	t_vector	north;
	double	fov;

	north = find_normal_vector(scene->camera.c_nvector,1);
	fov = 10;
	//calculate point of intersection between unitari vector and camera plane
	scene->camera.c_ray = normalize_vector(vector_init(scene->camera.c_point.x + scene->camera.c_nvector.x
		,scene->camera.c_point.y + scene->camera.c_nvector.y
		,scene->camera.c_point.z + scene->camera.c_nvector.z));
	//D_plane (&scene->camera);
	printf("ray = (%f,%f,%f), module %f\n",scene->camera.c_ray.x,scene->camera.c_ray.y,scene->camera.c_ray.z,modulo(scene->camera.c_ray));
	with_v = normalize_vector(producto_vectorial(scene->camera.c_ray,north));
	printf("with = (%f,%f,%f)\n",with_v.x,with_v.y,with_v.z);
	higt_v = producto_vectorial(with_v,scene->camera.c_ray);
	printf("higt = (%f,%f,%f)\n",higt_v.x,higt_v.y,higt_v.z);
	scene->camera.c_left = escalarxvector(2*tan(scene->camera.c_angle/2),with_v);
	scene->camera.c_up = escalarxvector((2*tan(scene->camera.c_angle/2)*scene->mlx.win_size.y)/scene->mlx.win_size.x,higt_v);
	printf("modulo left = %f, modulo up = %f\n",modulo(scene->camera.c_left),modulo(scene->camera.c_up));
	scene->camera.c_ray = escalarxvector(fov,scene->camera.c_ray);
	scene->camera.c_left = escalarxvector(fov,scene->camera.c_left);
	scene->camera.c_up = escalarxvector(fov,scene->camera.c_up);
	printf("modulo left = %f, modulo up = %f\n",modulo(scene->camera.c_left),modulo(scene->camera.c_up));






	// camera_intersection (&scene->camera);
	// with = camera_first_vector (&scene->camera);
	// higt = producto_vectorial (scene->camera.c_nvector, with);
	// higt = normalize_vector (higt);
	// //h_angle = (scene->camera.c_angle*scene->mlx.win_size.y/scene->mlx.win_size.x);
	// //printf("vertical angle = %f horizontal angle %f\n", h_angle, scene->camera.c_angle);

	// dwith = 8*tan((scene->camera.c_angle*M_PI)/(360));
	// dhigt = dwith * ((double) scene->mlx.win_size.y/scene->mlx.win_size.x);
	// printf ("ancho = %f , alto %f ancho p = %d alto %d\n",dwith,dhigt,scene->mlx.win_size.x,scene->mlx.win_size.y);
	// scene->camera.c_left.x = dwith * with.x;
	// scene->camera.c_left.y = dwith * with.y;
	// scene->camera.c_left.z = dwith * with.z;
	// //printf("with vector en distancia(%f,%f,%f), con modulo %f\n",with.x,with.y,with.z,modulo(with));
	// scene->camera.c_up.x = dhigt * higt.x;
	// scene->camera.c_up.y = dhigt * higt.y;
	// scene->camera.c_up.z = dhigt * higt.z;
	// //printf("punto de inicio(%f,%f,%f)\n",scene->camera.c_up.x,scene->camera.c_up.y,scene->camera.c_up.z);
	// //exit(0);
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

void camera_intersection (t_camera *camera)
{
	//double	param;


	camera->c_inter.x = (camera->c_nvector.x +camera->c_point.x);
	camera->c_inter.y = (camera->c_nvector.y +camera->c_point.y);
	camera->c_inter.z = (camera->c_nvector.z +camera->c_point.z);
	//printf("intersection  x = %f + y = %f + z= %f \n",camera->c_inter.x,camera->c_inter.y,camera->c_inter.z);
	//printf ("distance between camera and surface plane = %f\n",d);

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
	result = normalize_vector (result);
	result.x= result.x * lengh;
	result.y= result.y * lengh;
	result.z= result.z * lengh;
	//printf("vector (%f,%f,%f), con modulo %f",result.x,result.y,result.z,sqrt(pow(result.x,2) + pow(result.y,2) + pow(result.z,2)));
	return (result);
}
