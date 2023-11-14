/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 13:05:28 by mmoramov          #+#    #+#             */
/*   Updated: 2023/11/14 13:07:48 by josorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* make && ./miniRT test.rt */
int	main(int argc, char **argv)
{
	t_scene	scene;

	if (argc != 2 || ft_check_arg(argv[1]))
		ft_error(&scene, 1, "Please add one .rt type argument");

	scene_create(&scene, argv[1]);

	init(&scene);
	init_screen(&scene);
	display_mlx_win(&scene);
	free_scene(&scene);

	return (0);
}
