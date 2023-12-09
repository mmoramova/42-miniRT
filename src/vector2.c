/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 17:19:49 by josorteg          #+#    #+#             */
/*   Updated: 2023/12/09 11:36:45 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	v_mod(t_vector v1)
{
	double	result;

	result = sqrt(pow(v1.x, 2) + pow(v1.y, 2) + pow(v1.z, 2));
	return (result);
}

double	distance(t_vector point1, t_vector point2)
{
	double	result;

	result = v_mod(v_substr(point1, point2));
	return (result);
}

double	v_inner(t_vector vector1, t_vector vector2)
{
	double	res;

	res = vector1.x * vector2.x + vector1.y * vector2.y + vector1.z * vector2.z;
	if (fabs(res) < 0.0001)
		return (0);
	return (res);
}

t_vector	v_mult(t_vector vector1, t_vector vector2)
{
	t_vector	result;

	result.x = vector1.y * vector2.z - vector1.z * vector2.y;
	result.y = -(vector1.x * vector2.z - vector1.z * vector2.x);
	result.z = vector1.x * vector2.y - vector1.y * vector2.x;
	return (result);
}

t_vector	v_norm(t_vector v1)
{
	double	mod;

	mod = v_mod(v1);
	v1.x = v1.x / mod;
	v1.y = v1.y / mod;
	v1.z = v1.z / mod;
	return (v1);
}
