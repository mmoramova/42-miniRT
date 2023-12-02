/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 10:57:59 by josorteg          #+#    #+#             */
/*   Updated: 2023/12/02 12:40:38 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	unsigned int	ldst;
	unsigned int	i;

	ldst = ft_strlen(dst);
	i = 0;
	if (dstsize <= ldst)
		return (dstsize + ft_strlen(src));
	while (src[i] && (ldst + 1 < dstsize))
	{
		dst[ldst] = src[i];
		i++;
		ldst++;
	}
	dst[ldst] = '\0';
	return (ft_strlen(dst) + ft_strlen(&src[i]));
}
