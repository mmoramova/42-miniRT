/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 17:12:06 by mmoramov          #+#    #+#             */
/*   Updated: 2023/12/09 17:42:15 by josorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vector	vector_init(double x, double y, double z)
{
	t_vector	vector;

	vector.x = x;
	vector.y = y;
	vector.z = z;
	return (vector);
}

t_vector	set_vector(char *row)
{
	char		**data;
	t_vector	vector;

	data = ft_split(row, ',');
	vector.x = ft_atod(data[0]);
	vector.y = ft_atod(data[1]);
	vector.z = ft_atod(data[2]);
	free_datarow(data);
	return (vector);
}

t_vector	v_multd(double esc, t_vector vec)
{
	t_vector	res;

	res.x = esc * vec.x;
	res.y = esc * vec.y;
	res.z = esc * vec.z;
	return (res);
}

t_vector	v_substr(t_vector v1, t_vector v2)
{
	t_vector	res;

	res.x = v1.x - v2.x;
	res.y = v1.y - v2.y;
	res.z = v1.z - v2.z;
	return (res);
}

t_vector	v_sum(t_vector v1, t_vector v2)
{
	t_vector	res;

	res.x = v1.x + v2.x;
	res.y = v1.y + v2.y;
	res.z = v1.z + v2.z;
	return (res);
}
