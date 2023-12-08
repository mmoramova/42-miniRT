/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 15:38:38 by mmoramov          #+#    #+#             */
/*   Updated: 2023/12/08 17:05:33 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void ft_error(t_scene *scene, int exitnumber, char *txt)
{
	ft_putstr_fd("Error\n", 2);
	if (txt)
		ft_putstr_fd(txt, 2);
	ft_putstr_fd("\n", 2);
	if (scene)
		free_scene(scene);
	exit (exitnumber);
}
