/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 14:03:12 by mmoramov          #+#    #+#             */
/*   Updated: 2023/12/02 13:15:46 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*changes RGB to int*/
int	set_trgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

/* creates rgb from str for example: 10,0,255 */
t_rgb	set_rgb(char *row)
{
	char		**colors;
	t_rgb		rgb;

	colors = ft_split(row, ',');
	rgb.r = ft_atoi(colors[0]);
	rgb.g = ft_atoi(colors[1]);
	rgb.b = ft_atoi(colors[2]);
	rgb.rgb = set_trgb(rgb.r, rgb.g, rgb.b);

	return(rgb);
}

t_rgb rgb_mult(t_rgb c1, t_rgb c2)
{
	t_rgb	rgb;

	rgb.r = ((c1.r/255.0) * (c2.r/255.0)) * 255;
	rgb.g = ((c1.g/255.0) * (c2.g/255.0)) * 255;
	rgb.b = ((c1.b/255.0) * (c2.b/255.0)) * 255;
	rgb.rgb = set_trgb(rgb.r, rgb.g, rgb.b);

	return(rgb);
}
t_rgb rgb_multd(t_rgb c1, double r)
{
	t_rgb	rgb;

	rgb.r = c1.r * r;
	rgb.g = c1.g * r;
	rgb.b = c1.b * r;
	rgb.rgb = set_trgb(rgb.r, rgb.g, rgb.b);

	return(rgb);
}

t_rgb rgb_sum(t_rgb c1, t_rgb c2)
{
	t_rgb	rgb;

	rgb.r = c1.r + c2.r;
	rgb.g = c1.g + c2.g;
	rgb.b = c1.b + c2.b;
	rgb.rgb = set_trgb(rgb.r, rgb.g, rgb.b);

	return(rgb);
}

t_rgb	rgb_normalize(t_rgb rgb)
{
	double	max_color;

	max_color = 0;
	if (rgb.r > 255 || rgb.g > 255 || rgb.b > 255 )
	{
		max_color = fmax(fmax(rgb.r,rgb.g),rgb.b);
		rgb.r = (255 * rgb.r) / max_color;
		rgb.g = (255 * rgb.g) / max_color;
		rgb.b = (255 * rgb.b) / max_color;
		rgb.rgb = set_trgb(rgb.r, rgb.g, rgb.b);
	}
	return(rgb);
}
