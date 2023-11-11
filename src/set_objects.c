/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_objects.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 17:09:00 by mmoramov          #+#    #+#             */
/*   Updated: 2023/11/11 17:21:22 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* here are the functions which creates proper structure, fills data and add to t_scene */

void	set_amblight(t_scene *scene, char **datarow)
{
	t_amblight	*amblight;

	amblight = (t_amblight *) malloc(sizeof(t_amblight));
	if (!amblight)
		ft_error(scene, 1, "Malloc error - amblight");
	amblight->ratio = ft_atoi(datarow[1]); //todo ft_atod
	amblight->color = str2rgb(datarow[2]);

	ft_lstadd_front(&(scene->amblight), ft_lstnew(amblight));
}

void	set_camera(t_scene *scene, char **datarow)
{
	t_camera	*camera;

	camera = (t_camera *) malloc(sizeof(t_camera));
	if (!camera)
		ft_error(scene, 1, "Malloc error - camera");
	camera->point = str2vector(datarow[1]);
	camera->nvector = str2vector(datarow[2]);
	camera->angle = ft_atoi(datarow[3]);

	ft_lstadd_front(&(scene->camera), ft_lstnew(camera));
}

void	set_light(t_scene *scene, char **datarow)
{
	t_light	*light;

	light = (t_light *) malloc(sizeof(t_light));
	if (!light)
		ft_error(scene, 1, "Malloc error - light");
	light->point = str2vector(datarow[1]);
	light->brightness = ft_atoi(datarow[2]); //todo atod

	ft_lstadd_front(&(scene->light), ft_lstnew(light));
}

void	set_sphere(t_scene *scene, char **datarow)
{
	t_sphere	*sphere;

	sphere = (t_sphere *) malloc(sizeof(t_sphere));
	if (!sphere)
		ft_error(scene, 1, "Malloc error - sphere");
	sphere->point = str2vector(datarow[1]);
	sphere->diameter = ft_atoi(datarow[2]); //todo atod
	sphere->color = str2rgb(datarow[3]);

	ft_lstadd_front(&(scene->spheres), ft_lstnew(sphere));
}

void	set_plane(t_scene *scene, char **datarow)
{
	t_plane	*plane;

	plane = (t_plane *) malloc(sizeof(t_plane));
	if (!plane)
		ft_error(scene, 1, "Malloc error - plane");
	plane->point = str2vector(datarow[1]);
	plane->nvector = str2vector(datarow[2]);
	plane->color = str2rgb(datarow[3]);

	ft_lstadd_front(&(scene->planes), ft_lstnew(plane));
}
