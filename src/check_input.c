/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:00:26 by mmoramov          #+#    #+#             */
/*   Updated: 2023/12/09 16:27:04 by josorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	check_ratio(char *data)
{
	double	ratio;

	if (!check_nbrpositive(data))
		return (0);
	ratio = ft_atod(data);
	if (ratio > 1)
		return (0);
	return (1);
}

int	check_angle(char *data)
{
	double	ratio;
	int		i;

	i = 0;
	while (data[i] && data[i] != '\n')
	{
		if (!ft_isdigit(data[i]))
			return (0);
		i++;
	}
	ratio = ft_atod(data);
	if (ratio > 180)
		return (0);
	return (1);
}

int	check_color(char *data)
{
	t_rgb	color;
	int		i;
	int		count_commas;

	i = 0;
	count_commas = 0;
	while (data[i] && data[i] != '\n')
	{
		if (!ft_isdigit(data[i]) && data[i] != ',')
			return (0);
		if (data[i] == ',')
			count_commas += 1;
		i++;
	}
	if (data[i - 1] == ',' || count_commas != 2)
		return (0);
	color = set_rgb(data);
	if (color.r > 255 || color.g > 255 || color.b > 255)
		return (0);
	return (1);
}

int	check_vector(char *data)
{
	int		i;
	int		count_commas;
	int		count_dots;

	i = 0;
	count_dots = 0;
	count_commas = 0;
	while (data[i] && data[i] != '\n')
	{
		if ((!ft_isdigit(data[i]) && !ft_strchr(".,-", data[i]))
			|| (data[i] == '-' && !(i == 0 || data[i - 1] == ',')))
			return (0);
		if (data[i] == '.')
			count_dots += 1;
		if (data[i++] == ',')
		{
			if (count_dots > 1)
				return (0);
			count_dots = 0;
			count_commas += 1;
		}
	}
	if (ft_strchr(".,-", data[i - 1]) || count_commas != 2 || count_dots > 1)
		return (0);
	return (1);
}

int	check_nvector(char *data)
{
	t_vector	nvector;

	if (!check_vector(data))
		return (0);
	nvector = set_vector(data);
	if (nvector.x > 1 || nvector.x < -1
		|| nvector.y > 1 || nvector.y < -1
		|| nvector.z > 1 || nvector.z < -1)
		return (0);
	return (1);
}
