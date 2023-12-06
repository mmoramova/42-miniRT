/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 17:34:09 by mmoramov          #+#    #+#             */
/*   Updated: 2023/12/06 17:15:11 by josorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atod(const char *str)
{
	double	sign;
	double	num;
	double	part;

	sign = 1.0;
	while ((9 <= *str && 13 >= *str) || *str == 32)
		str++;
	if (*str == '-')
		sign = -1.0;
	if (*str == '-' || *str == '+')
		str++;
	num = 0.0;
	while (*str >= '0' && *str <= '9')
		num = num * 10 + ((*str++) - '0');
	if (*str == '.' || *str == ',')
	{
		while (*(++str) >= '0' && *str <= '9')
			part = 0.0;
		while (*(--str) >= '0' && *str <= '9')
			part = (part + ((*str) - '0')) / 10.0;
		num += part;
	}
	return (num * sign);
}
