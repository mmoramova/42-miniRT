/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wint.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 14:50:41 by josorteg          #+#    #+#             */
/*   Updated: 2023/12/02 12:42:29 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_wint(int n)
{
	int	res;

	res = 0;
	if (n == -2147483648)
	{
		res = write (1, "-2147483648", 11);
		if (res != 11)
			return (-1);
		return (res);
	}
	if (n < 0)
	{
		res += ft_wchar('-');
		if (res != 1)
			return (-1);
		n = -n;
	}
	return (res += ft_whe(n, "0123456789", 10));
}
