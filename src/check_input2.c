/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 16:26:55 by josorteg          #+#    #+#             */
/*   Updated: 2023/12/09 16:27:13 by josorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	check_nbrpositive(char *data)
{
	int		i;
	int		count_dots;

	i = 0;
	count_dots = 0;
	while (data[i] && data[i] != '\n')
	{
		if (!ft_isdigit(data[i]) && data[i] != '.')
			return (0);
		if (data[i] == '.')
			count_dots += 1;
		i++;
	}
	if (data[i - 1] == '.' || count_dots > 1)
		return (0);
	return (1);
}
