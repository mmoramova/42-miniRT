/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 17:19:49 by josorteg          #+#    #+#             */
/*   Updated: 2023/12/09 10:53:55 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"miniRT.h"

double	distance (t_vector point1,t_vector point2)
{
	return (sqrt (pow((point1.x - point2.x),2)+pow((point1.y - point2.y),2)+pow((point1.z - point2.z),2)));
}

double	v_inner (t_vector vector1, t_vector vector2)
{
	double	res;

	res = vector1.x * vector2.x + vector1.y * vector2.y + vector1.z * vector2.z;
	if ( fabs(res) < 0.0001)
		return (0);
	return (vector1.x * vector2.x + vector1.y * vector2.y + vector1.z * vector2.z);
}

t_vector v_mult (t_vector vector1, t_vector vector2)
{
	t_vector	result;

	result.x = vector1.y * vector2.z - vector1.z * vector2.y;
	result.y = -(vector1.x * vector2.z - vector1.z * vector2.x);
	result.z = vector1.x * vector2.y - vector1.y * vector2.x;
	return(result);
}

t_vector v_norm(t_vector v1)
{
	double	module;

	module = sqrt(pow(v1.x,2) + pow(v1.y,2) + pow(v1.z,2)); //use the v _mod
	v1.x = v1.x / module;
	v1.y = v1.y / module;
	v1.z = v1.z / module;
	return (v1);
}

double	v_mod(t_vector v1)
{
	double	result;
	result = sqrt(pow(v1.x, 2) + pow(v1.y, 2) + pow(v1.z, 2));
	return(result);
}


t_vector v_multd(double esc, t_vector vec)
{
	t_vector	res;

	res.x = esc * vec.x;
	res.y = esc * vec.y;
	res.z = esc * vec.z;
	return (res);
}
t_vector v_substr(t_vector v1, t_vector v2)
{
	t_vector res;

	res.x = v1.x - v2.x;
	res.y = v1.y - v2.y;
	res.z = v1.z - v2.z;

	return (res);
}
t_vector v_sum(t_vector v1, t_vector v2)
{
	t_vector res;

	res.x = v1.x + v2.x;
	res.y = v1.y + v2.y;
	res.z = v1.z + v2.z;

	return (res);

}

t_vector	find_normal_vector(t_vector v1, double lengh) //find_nvector
{
	t_vector result;

	(0 || (result.x = 0) || (result.y = 0) || (result.z = 0));
	if (v1.x != 0 && v1.y != 0 && v1.z != 0)
	{
		result.x = 1;
		result.y = 1;
		result.z = -(v1.x * result.x + v1.y * result.y)/v1.z;
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
	result = v_norm (result);
	result.x= result.x * lengh;
	result.y= result.y * lengh;
	result.z= result.z * lengh;
	return (result);
}
