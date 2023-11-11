/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 14:03:12 by mmoramov          #+#    #+#             */
/*   Updated: 2023/11/11 17:16:42 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*changes RGB to int*/
int	ft_create_trgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

/* creates rgb from str for example: 10,0,255 */
t_rgb str2rgb(char *row)
{
	char		**data;

	data = ft_split(row, ',');
	return(set_rgb(data[0], data[1], data[2]));
}

/* creates t_rgb from chars */
t_rgb set_rgb(char *x, char *y, char *z)
{
	t_rgb	rgb;

	rgb.r = ft_atoi(x);
	rgb.g = ft_atoi(y);
	rgb.b = ft_atoi(z);
	rgb.rgb = ft_create_trgb(rgb.r, rgb.g, rgb.b);

	return(rgb);
}
