/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 15:41:55 by mmoramov          #+#    #+#             */
/*   Updated: 2023/12/09 18:30:42 by josorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	scene_create(t_scene *scene, char *file)
{
	int		fd;
	char	*line;
	char	**datarow;

	scene->lights = ft_lstnew(NULL);
	scene->spheres = ft_lstnew(NULL);
	scene->planes = ft_lstnew(NULL);
	scene->cylinders = ft_lstnew(NULL);
	scene->amblight.al_count = 0;
	scene->camera.c_count = 0;
	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		datarow = ft_split_noprintable(line, '\t');
		free(line);
		scene_fill(scene, datarow);
		free_datarow(datarow);
		line = get_next_line(fd);
	}
	close(fd);
}

void	scene_fill(t_scene *scene, char **datarow)
{
	if ((datarow[0][0]) == '\n')
		return ;
	if (ft_strncmp(datarow[0], "A", 1) == 0 && ft_strlen(datarow[0]) == 1)
		set_amblight(scene, datarow);
	else if (ft_strncmp(datarow[0], "C", 1) == 0 && ft_strlen(datarow[0]) == 1)
		set_camera(scene, datarow);
	else if (ft_strncmp(datarow[0], "l", 1) == 0 && ft_strlen(datarow[0]) == 1)
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

void	print_vector(t_vector vector, char *str)
{
	printf("vector %s is (%f, %f, %f)\n", str, vector.x, vector.y, vector.z);
	return ;
}

void	free_datarow(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}
