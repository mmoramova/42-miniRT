/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_objects2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 17:10:13 by mmoramov          #+#    #+#             */
/*   Updated: 2023/12/08 17:02:27 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	set_cylinder(t_scene *scene, char **datarow, int *orderref)
{
	t_cylinder	*cylinder;

	if (datarow[5] == NULL || datarow[6] != NULL)
		ft_error(scene, 1, "incorrect number of inputs in camera");
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
	cylinder->c_point = v_substr(str2vector(datarow[1]), scene->camera.c_point_init);
	cylinder->c_direction = v_norm(str2vector(datarow[2]));
	cylinder->c_diameter = ft_atod(datarow[3]);
	cylinder->c_height = ft_atod(datarow[4]);
	cylinder->c_color = set_rgb(datarow[5]);
	cylinder->c_orderref = *orderref;
	*orderref += 1;
	cylinder->c_upper = v_sum(cylinder->c_point,v_multd(cylinder->c_height/2,cylinder->c_direction));
	cylinder->c_down = v_sum(cylinder->c_point,v_multd(-cylinder->c_height/2,cylinder->c_direction));
	set_planes_cylinder (&cylinder->upper_p,cylinder->c_upper,cylinder->c_direction);
	set_planes_cylinder (&cylinder->down_p,cylinder->c_down,v_multd(-1,cylinder->c_direction));
	ft_lstadd_front(&(scene->cylinders), ft_lstnew(cylinder));
}
void	set_planes_cylinder (t_plane *plane,t_vector point,t_vector axis)
{
	plane->p_point = point;
	plane->p_nvector = axis;
	plane->p_color = set_rgb("0,0,0");
	plane->p_surface.A = -plane->p_nvector.x;
	plane->p_surface.B = -plane->p_nvector.y;
	plane->p_surface.C = -plane->p_nvector.z;
	plane->p_surface.D = -(plane->p_surface.A*(plane->p_point.x) +
								plane->p_surface.B*(plane->p_point.y) +
								plane->p_surface.C*(plane->p_point.z));
}
