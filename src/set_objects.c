/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_objects.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 17:09:00 by mmoramov          #+#    #+#             */
/*   Updated: 2023/11/12 13:46:08 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* here are the functions which creates proper structure, fills data and add to t_scene */

void	set_amblight(t_scene *scene, char **datarow)
{
	scene->amblight.al_ratio = ft_atod(datarow[1]);
	scene->amblight.al_color = str2rgb(datarow[2]);
}

void	set_camera(t_scene *scene, char **datarow)
{
	scene->camera.c_point = str2vector(datarow[1]);
	scene->camera.c_nvector = str2vector(datarow[2]);
	scene->camera.c_angle = ft_atod(datarow[3]);
	//camera->c_surface = NULL;

}

void	set_light(t_scene *scene, char **datarow)
{
	t_light	*light;

	light = (t_light *) malloc(sizeof(t_light));
	if (!light)
		ft_error(scene, 1, "Malloc error - light");
	light->l_point = str2vector(datarow[1]);
	light->l_brightness = ft_atod(datarow[2]);
	//light->lightray = NULL;

	ft_lstadd_front(&(scene->lights), ft_lstnew(light));
}

void	set_sphere(t_scene *scene, char **datarow)
{
	t_sphere	*sphere;

	sphere = (t_sphere *) malloc(sizeof(t_sphere));
	if (!sphere)
		ft_error(scene, 1, "Malloc error - sphere");
	sphere->sp_point = str2vector(datarow[1]);
	sphere->sp_diameter = ft_atod(datarow[2]);
	sphere->sp_color = str2rgb(datarow[3]);
	//sphere->sp_radium = NULL;

	ft_lstadd_front(&(scene->spheres), ft_lstnew(sphere));
}

void	set_plane(t_scene *scene, char **datarow)
{
	t_plane	*plane;

	plane = (t_plane *) malloc(sizeof(t_plane));
	if (!plane)
		ft_error(scene, 1, "Malloc error - plane");
	plane->p_point = str2vector(datarow[1]);
	plane->p_nvector = str2vector(datarow[2]);
	plane->p_color = str2rgb(datarow[3]);
	//plane->p_surface = NULL;

	ft_lstadd_front(&(scene->planes), ft_lstnew(plane));
}
