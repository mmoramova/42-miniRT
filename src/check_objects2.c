/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_objects2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 21:54:46 by mmoramov          #+#    #+#             */
/*   Updated: 2023/12/09 16:28:54 by josorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	check_cylinder(t_scene *scene, char **datarow)
{
	if (datarow[5] == NULL || datarow[6] != NULL)
		ft_error(scene, 1, "incorrect number of inputs in camera");
	if (check_vector(datarow[1]) == 0)
		ft_error(scene, 1, "incorrect cylinder point");
	if (check_nvector(datarow[2]) == 0)
		ft_error(scene, 1, "incorrect cylinder vector");
	if (check_nbrpositive(datarow[3]) == 0)
		ft_error(scene, 1, "incorrect cylinder diameter");
	if (check_nbrpositive(datarow[4]) == 0)
		ft_error(scene, 1, "incorrect cylinder height");
	if (check_color(datarow[5]) == 0)
		ft_error(scene, 1, "incorrect cylinder color");
}
