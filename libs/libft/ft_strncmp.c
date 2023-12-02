/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 10:52:27 by josorteg          #+#    #+#             */
/*   Updated: 2023/12/02 12:40:38 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	ind;

	ind = 0;
	if (n == 0)
		return (0);
	while (((*(s1 + ind) && *(s2 + ind)) != '\0') && ind < (n - 1))
	{
		if (*(s1 + ind) != *(s2 + ind))
			return (((unsigned char *)s1)[ind] - ((unsigned char *)s2)[ind]);
		ind++;
	}
	return (((unsigned char *)s1)[ind] - ((unsigned char *)s2)[ind]);
}
