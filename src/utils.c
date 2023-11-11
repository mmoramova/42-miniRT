/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 15:43:43 by mmoramov          #+#    #+#             */
/*   Updated: 2023/11/11 17:28:38 by mmoramov         ###   ########.fr       */
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
