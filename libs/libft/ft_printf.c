/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 10:36:17 by josorteg          #+#    #+#             */
/*   Updated: 2023/12/02 12:42:29 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		res;
	int		inc;

	res = 0;
	va_start(args, str);
	if (!str)
		return (-1);
	while (*str != '\0')
	{
		inc = res;
		if (*str != '%')
			res += write(1, str, 1);
		else
			res += ft_decide(*(++str), args);
		str++;
		if (res < inc)
			return (-1);
	}
	va_end(args);
	return (res);
}
