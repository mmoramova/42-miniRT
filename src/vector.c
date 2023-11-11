/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 17:12:06 by mmoramov          #+#    #+#             */
/*   Updated: 2023/11/11 17:16:35 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* creates t_vector from numbers - i didnt use this but maybe we will need it */
t_vector vector_init(double x, double y, double z)
{
	t_vector	vector;

	vector.x = x;
	vector.y = y;
	vector.z = z;

	return(vector);
}
/* creater t_vector from str for example 0,0,1.0 */
t_vector str2vector(char *row)
{
	char		**data;

	data = ft_split(row, ',');
	return(set_vector(data[0], data[1], data[2]));
}

/* creater t_vector from chars */
t_vector set_vector(char *x, char *y, char *z)
{
	t_vector	vector;

	vector.x = ft_atoi(x);
	vector.y = ft_atoi(y);
	vector.z = ft_atoi(z);

	//todo ft_atod
	/*vector.x = ft_atod(x);
	vector.y = ft_atod(y);
	vector.z = ft_atod(z);
	*/
	return(vector);
}


