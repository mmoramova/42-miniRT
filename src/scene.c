/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 15:41:55 by mmoramov          #+#    #+#             */
/*   Updated: 2023/11/13 17:13:45 by josorteg         ###   ########.fr       */
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
		printf("\n%s\n", line);
		datarow = ft_split(line, '\t');
		free(line);

		printf("|Type is %s|\n", datarow[0]);
		printf("|First column data %s|\n", datarow[1]);

		scene_fill_line(scene, datarow);

		//free(datarow); //TODO
		line = get_next_line(fd);
	}

	// getting and printing any information example :
	int cameraprint;
	cameraprint = scene->camera.c_point.x;
	//printf("printing info from camera point y%d", cameraprint);

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
	if (ft_strncmp(datarow[0], "A", 1) == 0) //todo and len
		set_amblight(scene, datarow);
	else if (ft_strncmp(datarow[0], "C", 1) == 0)
		set_camera(scene, datarow);
	else if (ft_strncmp(datarow[0], "L", 1) == 0)
		set_light(scene, datarow);
	else if (ft_strncmp(datarow[0], "sp", 2) == 0)
		set_sphere(scene, datarow);
	else if (ft_strncmp(datarow[0], "pl", 2) == 0)
		set_plane(scene, datarow);
	else if (ft_strncmp(datarow[0], "cy", 2) == 0)
		set_cylinder(scene, datarow);
	else
		ft_error(scene, 1, "incorrect .rt file");
}
