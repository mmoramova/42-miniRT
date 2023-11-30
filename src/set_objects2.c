/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_objects2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 17:10:13 by mmoramov          #+#    #+#             */
/*   Updated: 2023/11/30 15:47:57 by josorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	set_cylinder(t_scene *scene, char **datarow)
{
	t_cylinder	*cylinder;

	if (inputcheck_isPointOrVector(datarow[1]) == 0)
		ft_error(scene, 1, "incorrect cylinder point");
	if (inputcheck_isPointOrVector(datarow[2]) == 0)
		ft_error(scene, 1, "incorrect cylinder vector");
	if (inputcheck_isDoublePositive(datarow[3]) == 0)
		ft_error(scene, 1, "incorrect cylinder diameter");
	if (inputcheck_isDoublePositive(datarow[4]) == 0)
		ft_error(scene, 1, "incorrect cylinder height");
	if (inputcheck_isColor(datarow[5]) == 0)
		ft_error(scene, 1, "incorrect cylinder color");

	cylinder = (t_cylinder *) malloc(sizeof(t_cylinder));
	if (!cylinder)
		ft_error(scene, 1, "Malloc error - cylinder");
	cylinder->c_point = vectorminus(str2vector(datarow[1]),scene->camera.c_point_init);
	cylinder->c_direction = normalize_vector(str2vector(datarow[2]));
	cylinder->c_diameter = ft_atod(datarow[3]);
	cylinder->c_height = ft_atod(datarow[4]);
	cylinder->c_color = str2rgb(datarow[5]);
	cylinder->c_upper = vectoradd(cylinder->c_point,escalarxvector(cylinder->c_height/2,cylinder->c_direction));
	cylinder->c_down = vectoradd(cylinder->c_point,escalarxvector(-cylinder->c_height/2,cylinder->c_direction));
	printf("cylinder center (%f,%f,%f), vector (%f,%f,%f), upper (%f,%f,%f), down (%f,%f,%f)\n"
		,cylinder->c_point.x,cylinder->c_point.y,cylinder->c_point.z
		,cylinder->c_direction.x,cylinder->c_direction.y,cylinder->c_direction.z
		,cylinder->c_upper.x,cylinder->c_upper.y,cylinder->c_upper.z
		,cylinder->c_down.x,cylinder->c_down.y,cylinder->c_down.z);
	//cylinder->c_nvector = NULL;

	ft_lstadd_front(&(scene->cylinders), ft_lstnew(cylinder));
}
