/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_whe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 10:46:46 by josorteg          #+#    #+#             */
/*   Updated: 2023/12/02 12:42:29 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_whe(unsigned long n, char *basec, int base)
{
	int	res;

	res = 0;
	if (n > (unsigned int)base - 1)
	{
		res += ft_whe(n / base, basec, base);
		if (res == -1)
			return (-1);
		ft_whe(n % base, basec, base);
		res++;
	}
	else
	{
		res += write(1, &basec[n], 1);
		if (res != 1)
			return (-1);
	}
	return (res);
}
