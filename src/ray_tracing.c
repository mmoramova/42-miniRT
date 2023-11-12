/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 13:49:12 by josorteg          #+#    #+#             */
/*   Updated: 2023/11/12 17:35:44 by josorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"miniRT.h"

int	ray_tracing(t_scene *scene/*,t_pixel pos*/)
{

	//calculate the plane and vertex of the plane
	D_plane (&scene->camera);
	//calculate point of intersection between unitari vector and camera plane
	camera_intersection (&scene->camera);

	//calculate points in the plane
	//calculate the ray vector
	//calculate colision
	return(0);
}
void D_plane (t_camera *camera)
{
	camera->c_surface.A = camera->c_nvector.x;
	camera->c_surface.B = camera->c_nvector.y;
	camera->c_surface.C = camera->c_nvector.z;
	camera->c_surface.D = -(camera->c_surface.A*(camera->c_surface.A +camera->c_point.x) +
								camera->c_surface.B*(camera->c_surface.B + camera->c_point.y) +
								camera->c_surface.C*(camera->c_surface.C + camera->c_point.z));
	printf("camera plane  %fx + %fy + %fz + %f = 0\n",camera->c_surface.A,camera->c_surface.B,camera->c_surface.C,camera->c_surface.D);

}

void camera_intersection (t_camera *camera)
{
	//double	param;
	t_vector	inter;
	double		d;

	inter.x = (camera->c_surface.A +camera->c_point.x);
	inter.y = (camera->c_surface.B +camera->c_point.y);
	inter.z = (camera->c_surface.C +camera->c_point.z);
	printf("intersection  x = %f + y = %f + z= %f \n",inter.x,inter.y,inter.z);
	d = distance (camera->c_point,inter);
	printf ("distance between camera and surface plane = %f\n",d);
	exit(0);
}


