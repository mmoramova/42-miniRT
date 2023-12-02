/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 10:49:59 by josorteg          #+#    #+#             */
/*   Updated: 2023/12/02 12:40:38 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*r;
	unsigned int	i;
	unsigned int	mem;

	i = 0;
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (ft_strlen(s)-start > len)
		mem = len + 1;
	else
		mem = (ft_strlen(s) - start) + 1;
	r = (char *)malloc (mem * sizeof(char));
	if (!r)
		return (NULL);
	while (i < mem -1)
	{
		r[i] = s[start + i];
		i++;
	}
	r[i] = '\0';
	return (r);
}
