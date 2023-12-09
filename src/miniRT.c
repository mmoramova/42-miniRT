/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 13:05:28 by mmoramov          #+#    #+#             */
/*   Updated: 2023/12/09 17:45:47 by josorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main(int argc, char **argv)
{
	t_scene	scene;

	if (argc != 2 || ft_check_arg(argv[1]))
	{
		ft_putstr_fd("Error\nPlease add one .rt type argument\n", 2);
		exit (1);
	}
	window_create(&scene);
	scene_create(&scene, argv[1]);
	display_mlx_win(&scene);
	return (0);
}
