/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_objects2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 17:10:13 by mmoramov          #+#    #+#             */
/*   Updated: 2023/11/11 18:41:54 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	set_cylinder(t_scene *scene, char **datarow)
{
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *) malloc(sizeof(t_cylinder));
	if (!cylinder)
		ft_error(scene, 1, "Malloc error - cylinder");
	cylinder->point = str2vector(datarow[1]);
	cylinder->nvector = str2vector(datarow[2]);
	cylinder->diameter = ft_atod(datarow[3]);
	cylinder->height = ft_atod(datarow[4]);
	cylinder->color = str2rgb(datarow[5]);

	ft_lstadd_front(&(scene->cylinders), ft_lstnew(cylinder));
}
