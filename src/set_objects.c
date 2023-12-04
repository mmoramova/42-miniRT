/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_objects.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 17:09:00 by mmoramov          #+#    #+#             */
/*   Updated: 2023/12/04 17:54:20 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* here are the functions which creates proper structure, fills data and add to t_scene */
void	set_amblight(t_scene *scene, char **datarow)
{
	if (datarow[2] == NULL || datarow[3] != NULL)
		ft_error(scene, 1, "incorrect number of inputs in amblight");
	if (scene->amblight.al_count == 1)
		ft_error(scene, 1, "multiple amblight rows");
	if (inputcheck_isRatio(datarow[1]) == 0)
		ft_error(scene, 1, "incorrect amblight ratio");
	if (inputcheck_isColor(datarow[2]) == 0)
		ft_error(scene, 1, "incorrect amblight color");

	scene->amblight.al_ratio = ft_atod(datarow[1]);
	scene->amblight.al_color = set_rgb(datarow[2]);
	scene->amblight.al_count = 1;
}

void	set_camera(t_scene *scene, char **datarow)
{
	if (datarow[3] == NULL || datarow[4] != NULL)
		ft_error(scene, 1, "incorrect number of inputs in camera");
	if (scene->camera.c_count == 1)
		ft_error(scene, 1, "multiple camera rows");
	if (inputcheck_isPointOrVector(datarow[1]) == 0)
		ft_error(scene, 1, "incorrect camera point");
	if (inputcheck_isPointOrVector(datarow[2]) == 0)
		ft_error(scene, 1, "incorrect camera vector");
	if (inputcheck_isAngle(datarow[3]) == 0)
		ft_error(scene, 1, "incorrect camera angle");

	scene->camera.c_point_init = str2vector(datarow[1]);
	scene->camera.c_point = vector_init(0,0,0);
	scene->camera.c_nvector = normalize_vector(str2vector(datarow[2]));
	scene->camera.c_angle = ft_atod(datarow[3])* 2 * M_PI / 360;
	scene->camera.c_count = 1;
	//camera->c_surface = NULL;

}

void	set_light(t_scene *scene, char **datarow)
{
	t_light	*light;

	if (datarow[3] == NULL || datarow[4] != NULL)
		ft_error(scene, 1, "incorrect number of inputs in light");
	if (inputcheck_isPointOrVector(datarow[1]) == 0)
		ft_error(scene, 1, "incorrect light point");
	if (inputcheck_isRatio(datarow[2]) == 0)
		ft_error(scene, 1, "incorrect light brightness");
	if (inputcheck_isColor(datarow[3]) == 0)
		ft_error(scene, 1, "incorrect light color");

	light = (t_light *) malloc(sizeof(t_light));
	if (!light)
		ft_error(scene, 1, "Malloc error - light");
	light->l_point = vectorminus(str2vector(datarow[1]),scene->camera.c_point_init);
	light->l_brightness = ft_atod(datarow[2]);
	light->color = set_rgb(datarow[3]);
	//light->lightray = NULL;

	ft_lstadd_front(&(scene->lights), ft_lstnew(light));
}

void	set_sphere(t_scene *scene, char **datarow, int *orderref)
{
	t_sphere	*sphere;

	if (datarow[3] == NULL || datarow[4] != NULL)
		ft_error(scene, 1, "incorrect number of inputs in sphere");
	if (inputcheck_isPointOrVector(datarow[1]) == 0)
		ft_error(scene, 1, "incorrect sphere point");
	if (inputcheck_isDoublePositive(datarow[2]) == 0)
		ft_error(scene, 1, "incorrect sphere diameter");
	if (inputcheck_isColor(datarow[3]) == 0)
		ft_error(scene, 1, "incorrect sphere color");
		sphere = (t_sphere *) malloc(sizeof(t_sphere));
	if (!sphere)
		ft_error(scene, 1, "Malloc error - sphere");
	sphere->sp_point = vectorminus(str2vector(datarow[1]),scene->camera.c_point_init);
	sphere->sp_diameter = ft_atod(datarow[2]);
	sphere->sp_color = set_rgb(datarow[3]);
	sphere->sp_orderref = *orderref;
	*orderref += 1;
	//sphere->sp_radium = NULL;
	printf("Order number of sphere is %d\n",sphere->sp_orderref);
	ft_lstadd_front(&(scene->spheres), ft_lstnew(sphere));
}

void	set_plane(t_scene *scene, char **datarow, int *orderref)
{
	t_plane	*plane;

	if (datarow[3] == NULL || datarow[4] != NULL)
		ft_error(scene, 1, "incorrect number of inputs in plane");
	if (inputcheck_isPointOrVector(datarow[1]) == 0)
		ft_error(scene, 1, "incorrect plane point");
	if (inputcheck_isPointOrVector(datarow[2]) == 0)
		ft_error(scene, 1, "incorrect plane vector");
	if (inputcheck_isColor(datarow[3]) == 0)
		ft_error(scene, 1, "incorrect plane color");

	plane = (t_plane *) malloc(sizeof(t_plane));
	if (!plane)
		ft_error(scene, 1, "Malloc error - plane");
	write(1,"a",1);
	plane->p_point = vectorminus(str2vector(datarow[1]),scene->camera.c_point_init);;
	plane->p_nvector = str2vector(datarow[2]);
	plane->p_color = set_rgb(datarow[3]);
	plane->p_orderref = *orderref;
	*orderref += 1;
	plane->p_surface.A = -plane->p_nvector.x;
	plane->p_surface.B = -plane->p_nvector.y;
	plane->p_surface.C = -plane->p_nvector.z;
	plane->p_surface.D = -(plane->p_surface.A*(plane->p_point.x) +
								plane->p_surface.B*(plane->p_point.y) +
								plane->p_surface.C*(plane->p_point.z));


	ft_lstadd_front(&(scene->planes), ft_lstnew(plane));
}
