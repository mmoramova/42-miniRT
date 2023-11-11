/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_fractol.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:03:45 by josorteg          #+#    #+#             */
/*   Updated: 2023/11/11 13:03:08 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx.h"

void	ft_mensaje(void)
{
	ft_printf("Error-->Usage: \n");
}

void	init(t_painter *painter)
{
	painter->mlx.win_size.x = 1900;
	painter->mlx.win_size.y = 1080;
}
/*
static void	add_mlx_hook(t_painter *painter)
{
	mlx_hook(painter->mlx.window, KEYPRESS, 0, key_hook, painter);
	mlx_hook(painter->mlx.window, MOTIONNOTIFY, 0, mouse_hook, painter);
	mlx_hook(painter->mlx.window, BUTTONPRESS, 0, scroll_hook, painter);
	mlx_hook(painter->mlx.window, DESTROYNOTIFY, 0, painter_exit, painter);
}*/

int	display_mlx_win(t_painter *painter)
{
	painter->mlx.mlx = mlx_init();
	if (painter->mlx.mlx != NULL)
	{
		painter->mlx.window
			= mlx_new_window(painter->mlx.mlx, painter->mlx.win_size.x,
				painter->mlx.win_size.y, "miniRT");
		if (painter->mlx.window != NULL)
		{
			painter->mlx.image = mlx_new_image(painter->mlx.mlx,
					painter->mlx.win_size.x, painter->mlx.win_size.y);
			if (painter->mlx.image != NULL)
			{
				painter->mlx.buff = mlx_get_data_addr(painter->mlx.image,
						&painter->mlx.bpp, &painter->mlx.buf_wid,
						&painter->mlx.endian);
				mlx_put_image_to_window(painter->mlx.mlx, painter->mlx.window,
					painter->mlx.image, 0, 0);
				add_mlx_hook(painter);
				draw_win(painter);
				mlx_loop(painter->mlx.mlx);
				return (0);
			}
		}
	}
	return (1);
}
