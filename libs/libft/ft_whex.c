/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_whex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 14:58:05 by josorteg          #+#    #+#             */
/*   Updated: 2023/12/02 12:42:29 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_whex(unsigned int n)
{
	int	res;

	res = 0;
	res += ft_whe(n, "0123456789abcdef", 16);
	if (res == -1)
		return (-1);
	return (res);
}
