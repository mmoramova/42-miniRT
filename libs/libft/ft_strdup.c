/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 09:45:06 by josorteg          #+#    #+#             */
/*   Updated: 2023/12/02 12:40:38 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char			*s2;
	unsigned int	ind;

	ind = 0;
	s2 = malloc (ft_strlen(s1) * sizeof(char) + 1);
	if (!s2)
		return (NULL);
	while (s1[ind] != '\0')
	{
		s2[ind] = s1[ind];
		ind++;
	}
	s2[ind] = '\0';
	return (s2);
}
