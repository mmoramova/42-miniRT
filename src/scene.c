/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 15:41:55 by mmoramov          #+#    #+#             */
/*   Updated: 2023/11/29 17:38:29 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* creates a scene and fills data from .rt file */
void scene_create(t_scene *scene, char *file)
{
	int		fd;
	char	*line;
	char	**datarow;

	scene_init(scene);
	fd = open(file, O_RDONLY);

	line = get_next_line(fd);
	while (line)
	{
		datarow = ft_split(line, '\t'); //Jose i will ask you about this when we will meet
		free(line);
		scene_fill_line(scene, datarow);

		//free(datarow); //TODO
		line = get_next_line(fd);
	}
}

/* creates empty t_scene for init */
void scene_init(t_scene *scene)
{
	//scene->amblight = ft_lstnew(NULL);
	//scene->camera = ft_lstnew(NULL);
	scene->lights = ft_lstnew(NULL);
	scene->spheres = ft_lstnew(NULL);
	scene->planes = ft_lstnew(NULL);
	scene->cylinders = ft_lstnew(NULL);
}

/* fill each line depending on the first letters */
void scene_fill_line(t_scene *scene, char **datarow)
{
	if ((datarow[0][0]) == '\n')
		return;
	if (ft_strncmp(datarow[0], "A", 1) == 0 && ft_strlen(datarow[0]) == 1)
		set_amblight(scene, datarow);
	else if (ft_strncmp(datarow[0], "C", 1) == 0 && ft_strlen(datarow[0]) == 1)
		set_camera(scene, datarow);
	else if (ft_strncmp(datarow[0], "L", 1) == 0 && ft_strlen(datarow[0]) == 1)  //i will ask you when we meet
		set_light(scene, datarow);
	else if (ft_strncmp(datarow[0], "sp", 2) == 0 && ft_strlen(datarow[0]) == 2)
		set_sphere(scene, datarow);
	else if (ft_strncmp(datarow[0], "pl", 2) == 0 && ft_strlen(datarow[0]) == 2)
		set_plane(scene, datarow);
	else if (ft_strncmp(datarow[0], "cy", 2) == 0 && ft_strlen(datarow[0]) == 2)
		set_cylinder(scene, datarow);
	else
		ft_error(scene, 1, "incorrect .rt file");
}
