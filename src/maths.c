/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 17:19:49 by josorteg          #+#    #+#             */
/*   Updated: 2023/11/12 17:35:32 by josorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"miniRT.h"

double	distance (t_vector point1,t_vector point2)
{
	printf("distance = %f\n",sqrt (pow((point1.x - point2.x),2)+pow((point1.y - point2.y),2)+pow((point1.z - point2.z),2)));
	return (sqrt (pow((point1.x - point2.x),2)+pow((point1.y - point2.y),2)+pow((point1.z - point2.z),2)));
}
