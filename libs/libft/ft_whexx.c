/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_whexx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 15:04:12 by josorteg          #+#    #+#             */
/*   Updated: 2023/12/02 12:43:28 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_whexx(unsigned int n)
{
	int	res;

	res = 0;
	res += ft_whe(n, "0123456789ABCDEF", 16);
	if (res == -1)
		return (-1);
	return (res);
}
