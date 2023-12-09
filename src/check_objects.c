/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 21:45:59 by mmoramov          #+#    #+#             */
/*   Updated: 2023/12/09 16:28:46 by josorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	check_amblight(t_scene *scene, char **datarow)
{
	if (datarow[2] == NULL || datarow[3] != NULL)
		ft_error(scene, 1, "incorrect number of inputs in amblight");
	if (scene->amblight.al_count == 1)
		ft_error(scene, 1, "multiple amblight rows");
	if (check_ratio(datarow[1]) == 0)
		ft_error(scene, 1, "incorrect amblight ratio");
	if (check_color(datarow[2]) == 0)
		ft_error(scene, 1, "incorrect amblight color");
}

void	check_camera(t_scene *scene, char **datarow)
{
	if (datarow[3] == NULL || datarow[4] != NULL)
		ft_error(scene, 1, "incorrect number of inputs in camera");
	if (scene->camera.c_count == 1)
		ft_error(scene, 1, "multiple camera rows");
	if (check_vector(datarow[1]) == 0)
		ft_error(scene, 1, "incorrect camera point");
	if (check_nvector(datarow[2]) == 0)
		ft_error(scene, 1, "incorrect camera vector");
	if (check_angle(datarow[3]) == 0)
		ft_error(scene, 1, "incorrect camera angle");
}

void	check_light(t_scene *scene, char **datarow)
{
	if (datarow[3] == NULL || datarow[4] != NULL)
		ft_error(scene, 1, "incorrect number of inputs in light");
	if (check_vector(datarow[1]) == 0)
		ft_error(scene, 1, "incorrect light point");
	if (check_ratio(datarow[2]) == 0)
		ft_error(scene, 1, "incorrect light brightness");
	if (check_color(datarow[3]) == 0)
		ft_error(scene, 1, "incorrect light color");
}

void	check_sphere(t_scene *scene, char **datarow)
{
	if (datarow[3] == NULL || datarow[4] != NULL)
		ft_error(scene, 1, "incorrect number of inputs in sphere");
	if (check_vector(datarow[1]) == 0)
		ft_error(scene, 1, "incorrect sphere point");
	if (check_nbrpositive(datarow[2]) == 0)
		ft_error(scene, 1, "incorrect sphere diameter");
	if (check_color(datarow[3]) == 0)
		ft_error(scene, 1, "incorrect sphere color");
}

void	check_plane(t_scene *scene, char **datarow)
{
	if (datarow[3] == NULL || datarow[4] != NULL)
		ft_error(scene, 1, "incorrect number of inputs in plane");
	if (check_vector(datarow[1]) == 0)
		ft_error(scene, 1, "incorrect plane point");
	if (check_nvector(datarow[2]) == 0)
		ft_error(scene, 1, "incorrect plane vector");
	if (check_color(datarow[3]) == 0)
		ft_error(scene, 1, "incorrect plane color");
}
