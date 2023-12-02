/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 12:31:37 by josorteg          #+#    #+#             */
/*   Updated: 2023/12/02 12:40:38 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	int					i;
	unsigned char		*p;
	unsigned const char	*s;

	p = dst;
	i = 0;
	s = src;
	if (dst == src)
		return (dst);
	if (dst < src)
	{
		while (i < (int)len)
		{
			p[i] = s[i];
			i++;
		}
	}
	else
	{
		while (len-- > 0)
			p[len] = s[len];
	}
	return (dst);
}
