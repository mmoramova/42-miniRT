/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_screen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:48:20 by josorteg          #+#    #+#             */
/*   Updated: 2023/11/14 17:06:01 by josorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"miniRT.h"


void	init_screen(t_scene *scene)
{
	double		dhigt;
	double		dwith;
	t_vector	with;
	t_vector	higt;

	D_plane (&scene->camera);
	//calculate point of intersection between unitari vector and camera plane
	camera_intersection (&scene->camera);
	with = camera_first_vector (&scene->camera);
	higt = producto_vectorial (scene->camera.c_nvector, with);
	higt = normalize_vector (higt);
	with = normalize_vector (with);
	//h_angle = (scene->camera.c_angle*scene->mlx.win_size.y/scene->mlx.win_size.x);
	//printf("vertical angle = %f horizontal angle %f\n", h_angle, scene->camera.c_angle);

	dwith = distance (scene->camera.c_point, scene->camera.c_inter)*tan((scene->camera.c_angle*M_PI)/(360));
	dhigt = dwith * ((double) scene->mlx.win_size.y/scene->mlx.win_size.x);
	printf ("ancho = %f , alto %f ancho p = %d alto %d\n",dwith,dhigt,scene->mlx.win_size.x,scene->mlx.win_size.y);
	scene->camera.c_left.x = dwith * with.x;
	scene->camera.c_left.y = dwith * with.y;
	scene->camera.c_left.z = dwith * with.z;
	//printf("with vector en distancia(%f,%f,%f), con modulo %f\n",with.x,with.y,with.z,modulo(with));
	scene->camera.c_up.x = dhigt * higt.x;
	scene->camera.c_up.y = dhigt * higt.y;
	scene->camera.c_up.z = dhigt * higt.z;
	//printf("punto de inicio(%f,%f,%f)\n",scene->camera.c_up.x,scene->camera.c_up.y,scene->camera.c_up.z);
	//exit(0);
}
void D_plane (t_camera *camera)
{
	camera->c_surface.A = camera->c_nvector.x;
	camera->c_surface.B = camera->c_nvector.y;
	camera->c_surface.C = camera->c_nvector.z;
	camera->c_surface.D = -(camera->c_surface.A*(camera->c_surface.A +camera->c_point.x) +
								camera->c_surface.B*(camera->c_surface.B + camera->c_point.y) +
								camera->c_surface.C*(camera->c_surface.C + camera->c_point.z));
	//printf("camera plane  %fx + %fy + %fz + %f = 0\n",camera->c_surface.A,camera->c_surface.B,camera->c_surface.C,camera->c_surface.D);

}

void camera_intersection (t_camera *camera)
{
	//double	param;
	double		d;

	camera->c_inter.x = (camera->c_surface.A +camera->c_point.x);
	camera->c_inter.y = (camera->c_surface.B +camera->c_point.y);
	camera->c_inter.z = (camera->c_surface.C +camera->c_point.z);
	//printf("intersection  x = %f + y = %f + z= %f \n",camera->c_inter.x,camera->c_inter.y,camera->c_inter.z);
	d = distance (camera->c_point,camera->c_inter);
	//printf ("distance between camera and surface plane = %f\n",d);

}

t_vector	camera_first_vector (t_camera *camera)
{
	double		lengh;
	t_vector	first_unitary;

	lengh = distance (camera->c_point, camera->c_inter)*tan((camera->c_angle/2*2*M_PI)/(360));
	//printf ("module first vector= %f\n",lengh);
	first_unitary = find_normal_vector (camera->c_nvector, lengh);
	return (first_unitary);
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