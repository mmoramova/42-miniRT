/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 15:43:43 by mmoramov          #+#    #+#             */
/*   Updated: 2023/12/09 10:51:17 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* check if file ends by .rt */
int	ft_check_arg(char *file)
{
	int len;

	len = ft_strlen(file);
	if (len < 4 || (ft_strnstr(&file[len - 3], ".rt", len) == 0))
		return (1);
	return (0);
}

t_line	l_create (t_vector pi, t_vector pf)
{
	t_line	ray;

	ray.l_point = pi;
	ray.l_vector = v_substr(pf, pi);
	return (ray);
}



