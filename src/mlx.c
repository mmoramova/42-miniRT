/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_old.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:03:45 by josorteg          #+#    #+#             */
/*   Updated: 2023/11/12 15:23:12 by josorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "minilibx.h"
#include "miniRT.h"

void	ft_mensaje(void)
{
	ft_printf("Error-->Usage: \n");
}

void	init(t_scene *scene)
{
	scene->mlx.win_size.x = 1900;
	scene->mlx.win_size.y = 1080;
}

static void	add_mlx_hook(t_scene *scene)
{
	/*mlx_hook(scene->mlx.window, KEYPRESS, 0, key_hook, scene);
	mlx_hook(scene->mlx.window, MOTIONNOTIFY, 0, mouse_hook, scene);
	mlx_hook(scene->mlx.window, BUTTONPRESS, 0, scroll_hook, scene);*/
	mlx_hook(scene->mlx.window, DESTROYNOTIFY, 0, scene_exit, scene);
}

int	display_mlx_win(t_scene *scene)
{
	scene->mlx.mlx = mlx_init();
	if (scene->mlx.mlx != NULL)
	{
		scene->mlx.window
			= mlx_new_window(scene->mlx.mlx, scene->mlx.win_size.x,
				scene->mlx.win_size.y, "miniRT");
		if (scene->mlx.window != NULL)
		{
			scene->mlx.image = mlx_new_image(scene->mlx.mlx,
					scene->mlx.win_size.x, scene->mlx.win_size.y);
			if (scene->mlx.image != NULL)
			{
				scene->mlx.buff = mlx_get_data_addr(scene->mlx.image,
						&scene->mlx.bpp, &scene->mlx.buf_wid,
						&scene->mlx.endian);
				mlx_put_image_to_window(scene->mlx.mlx, scene->mlx.window,
					scene->mlx.image, 0, 0);
				add_mlx_hook(scene);
				draw_win(scene);
				mlx_loop(scene->mlx.mlx);
				return (0);
			}
		}
	}
	return (1);
}