/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 17:19:49 by josorteg          #+#    #+#             */
/*   Updated: 2023/11/15 18:19:22 by josorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"miniRT.h"

double	distance (t_vector point1,t_vector point2)
{
	//printf("distance = %f\n",sqrt (pow((point1.x - point2.x),2)+pow((point1.y - point2.y),2)+pow((point1.z - point2.z),2)));
	return (sqrt (pow((point1.x - point2.x),2)+pow((point1.y - point2.y),2)+pow((point1.z - point2.z),2)));
}

double	producto_escalar (t_vector vector1, t_vector vector2)
{
	return (vector1.x * vector2.x + vector1.y * vector2.y + vector1.z * vector2.z);
}

t_vector producto_vectorial (t_vector vector1, t_vector vector2)
{
	t_vector	result;

	result.x = vector1.y * vector2.z - vector1.z * vector2.y;
	result.y = -(vector1.x * vector2.z - vector1.z * vector2.x);
	result.z = vector1.x * vector2.y - vector1.y * vector2.x;
	return(result);
}

t_vector normalize_vector(t_vector v1)
{
	double	module;

	module = sqrt(pow(v1.x,2) + pow(v1.y,2) + pow(v1.z,2));
	v1.x = v1.x/module;
	v1.y = v1.y/module;
	v1.z = v1.z/module;
	//printf("vector (%f,%f,%f), con modulo %f\n",v1.x,v1.y,v1.z,modulo(v1));
	return (v1);
}

double	modulo(t_vector v1)
{
	double	result;
	result = sqrt(pow(v1.x,2) + pow(v1.y,2) + pow(v1.z,2));
	return(result);
}

t_line	two_points_line (t_vector pi, t_vector pf)
{
	t_line	ray;

	ray.Ux = pf.x - pi.x;
	ray.Uy = pf.y - pi.y;
	ray.Uz = pf.z - pi.z;
	ray.x0 = pi.x;
	ray.y0 = pi.y;
	ray.z0 = pi.z;
	return (ray);
}

t_vector escalarxvector(double esc, t_vector vec)
{
	t_vector	res;

	res.x = esc * vec.x;
	res.y = esc * vec.y;
	res.z = esc * vec.z;
	return (res);
}
t_vector vectorminus(t_vector v1, t_vector v2)
{
	t_vector res;

	res.x = v1.x - v2.x;
	res.y = v1.y - v2.y;
	res.z = v1.z - v2.z;

	return (res);
}
t_vector vectoradd(t_vector v1, t_vector v2)
{
	t_vector res;

	res.x = v1.x + v2.x;
	res.y = v1.y + v2.y;
	res.z = v1.z + v2.z;

	return (res);

}




