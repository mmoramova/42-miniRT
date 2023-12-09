/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_screen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:48:20 by josorteg          #+#    #+#             */
/*   Updated: 2023/12/09 14:08:29 by josorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"miniRT.h"

void	print_vector(t_vector vector,char	*str)
{
	printf("vector %s is (%f,%f,%f)\n",str,vector.x,vector.y,vector.z);
	return;
}

