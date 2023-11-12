/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 17:50:16 by mmoramov          #+#    #+#             */
/*   Updated: 2023/11/12 13:45:07 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	free_scene(t_scene *scene)
{
	if (scene)
	{
		ft_lstclear(&(scene->lights), free_light);
		ft_lstclear(&(scene->spheres), free_sphere);
		ft_lstclear(&(scene->planes), free_plane);
		ft_lstclear(&(scene->cylinders), free_cylinder);
	}

}

void	free_light(void *light)
{
	if (light)
		free(light);
}

void	free_sphere(void *sphere)
{
	if (sphere)
		free(sphere);
}

void	free_plane(void *plane)
{
	if (plane)
		free(plane);
}

void	free_cylinder(void *cylinder)
{
	if (cylinder)
		free(cylinder);
}





