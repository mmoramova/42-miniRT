/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputCheck.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:00:26 by mmoramov          #+#    #+#             */
/*   Updated: 2023/12/02 13:01:50 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int inputcheck_isRatio(char *data)
{
	double	ratio;
	int		i;
	int		count_dots;

	i = 0;
	count_dots = 0;
	//just numbers or dot
	while (data[i] && data[i] != '\n')
	{
		if (!ft_isdigit(data[i]) && data[i] != '.')
			return 0;
		if (data[i] == '.')
			count_dots += 1;
		i++;
	}
	//max 1 dot
	if (count_dots > 1)
		return (0);
	ratio = ft_atod(data);
	// between 0 and 1, not checking < 0 because it cant contain minus
	if (ratio > 1)
		return (0);
	return (1);
}

int inputcheck_isAngle(char *data)
{
	double	ratio;
	int		i;

	i = 0;
	//just numbers
	while (data[i] && data[i] != '\n')
	{
		if (!ft_isdigit(data[i]))
			return 0;
		i++;
	}
	ratio = ft_atod(data);
	// between 0 and 180, not checking < 0 because it cant contain minus
	if (ratio > 180)
		return (0);
	return (1);
}

int inputcheck_isColor(char *data)
{
	t_rgb	color;
	int		i;
	int		count_commas;

	i = 0;
	count_commas = 0;
	//just numbers and commas
	while (data[i] && data[i] != '\n')
	{
		if (!ft_isdigit(data[i]) && data[i] != ',')
			return 0;
		if (data[i] == ',')
			count_commas += 1;
		i++;
	}
	//exactly 2 commas
	if (count_commas != 2)
		return (0);
	color = set_rgb(data);
	// between 0 and 255 inclusive, not checking < 0 because it cant contain minus
	if (color.r > 255 || color.g > 255 || color.b > 255)
		return (0);
	return (1);
}

int inputcheck_isPointOrVector(char *data)
{
	int		i;
	int		count_commas;
	int		count_dots;

	i = 0;
	count_dots = 0;
	count_commas = 0;
	//just numbers, dots, minus and commas. Only one dot between commas
	while (data[i] && data[i] != '\n')
	{
		if (!ft_isdigit(data[i]) && data[i] != '.' && data[i] != ',' && data[i] != '-')
			return 0;
		if (data[i] == '-' && !(i == 0 || data[i-1] == ','))
			return 0;
		if (data[i] == ',')
		{
			if (count_dots > 1)
				return (0);
			count_dots = 0;
			count_commas += 1;
		}
		i++;
	}
	//exactly 2 commas and max one dot after last comma
	if (count_commas != 2 || count_dots > 1)
		return (0);
	return (1);
}

int inputcheck_isDoublePositive(char *data)
{
	int		i;
	int		count_dots;

	i = 0;
	count_dots = 0;
	//just numbers or dot
	while (data[i] && data[i] != '\n')
	{
		if (!ft_isdigit(data[i]) && data[i] != '.')
			return 0;
		if (data[i] == '.')
			count_dots += 1;
		i++;
	}
	//max 1 dot
	if (count_dots > 1)
		return (0);
	return (1);
}
