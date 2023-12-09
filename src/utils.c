/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 15:43:43 by mmoramov          #+#    #+#             */
/*   Updated: 2023/12/09 11:49:02 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	ft_check_arg(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (len < 4 || (ft_strnstr(&file[len - 3], ".rt", len) == 0))
		return (1);
	return (0);
}

t_line	l_create(t_vector pi, t_vector pf)
{
	t_line	ray;

	ray.l_point = pi;
	ray.l_vector = v_substr(pf, pi);
	return (ray);
}

t_vector	find_nvector(t_vector v1, double length)
{
	t_vector	result;

	(0 || (result.x = 0) || (result.y = 0) || (result.z = 0));
	if (v1.x != 0 && v1.y != 0 && v1.z != 0)
	{
		result.x = 1;
		result.y = 1;
		result.z = -(v1.x * result.x + v1.y * result.y) / v1.z;
	}
	else
	{
		if (v1.x == 0)
			result.x = 1;
		if (v1.y == 0)
			result.y = 1;
		if (v1.z == 0)
			result.z = 1;
	}
	result = v_multd(length, v_norm(result));
	return (result);
}

void ft_error(t_scene *scene, int exitnumber, char *txt)
{
	ft_putstr_fd("Error\n", 2);
	if (txt)
		ft_putstr_fd(txt, 2);
	ft_putstr_fd("\n", 2);
	if (scene)
		free_scene(scene);
	exit (exitnumber);
}
