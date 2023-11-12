/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 09:06:11 by josorteg          #+#    #+#             */
/*   Updated: 2023/11/12 15:32:12 by josorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"miniRT.h"

// static double	scale(int32_t win_pos, int32_t win_size,
// 	double pos, double size)
// {
// 	return (((double)win_pos / (double)win_size) * size + pos);
// }

int	key_hook(int keycode, t_scene *scene)
{
	if (keycode == ESC_KEY)
		scene_exit(scene);
		// if (keycode == UP_KEY)
		// 	scene->pict.pos.y -= (scene->pict.size.y / 10);
		// if (keycode == DOWN_KEY)
		// 	scene->pict.pos.y += (scene->pict.size.y / 10);
		// if (keycode == RIGHT_KEY)
		// 	scene->pict.pos.x += (scene->pict.size.x / 10);
		// if (keycode == LEFT_KEY)
		// 	scene->pict.pos.x -= (scene->pict.size.x / 10);
		// if (keycode == PUP_KEY)
		// 	scene->pict.iter_num++;
		// if (keycode == PDOWN_KEY)
		// 	scene->pict.iter_num -= (scene->pict.iter_num >= 1);
	draw_win(scene);
	return (0);
}

int	scene_exit(t_scene *scene)
{
	if (scene->mlx.mlx && scene->mlx.window)
		mlx_destroy_window(scene->mlx.mlx, scene->mlx.window);
	if (scene->mlx.mlx && scene->mlx.image)
		mlx_destroy_image(scene->mlx.mlx, scene->mlx.image);
	exit(0);
}

// int	mouse_hook(int x, int y, t_scene *scene)
// {
// 	if (scene->pict.movable && !scene->pict.mov_lock)
// 	{
// 		scene->mouse_pos.x = scale(x, scene->mlx.win_size.x,
// 				scene->pict.pos.x, scene->pict.size.x);
// 		scene->mouse_pos.y = scale(y, scene->mlx.win_size.y,
// 				scene->pict.pos.y, scene->pict.size.y);
// 		draw_win(scene);
// 	}
// 	return (0);
// }

// int	scroll_hook(int button, int x, int y, t_scene *scene)
// {
// 	if (button == SCROLLUP_KEY)
// 	{
// 		zoom_out(scene, (t_vec2){x, y});
// 	}
// 	else if (button == SCROLLDOWN_KEY)
// 	{
// 		zoom_in(scene, (t_vec2){x, y});
// 	}
// 	else
// 	{
// 		if (!scene->pict.movable)
// 		{
// 			scene->pict.pos.x = scale(x, scene->mlx.win_size.x,
// 					scene->pict.pos.x, scene->pict.size.x)
// 				- scene->pict.size.x / 2;
// 			scene->pict.pos.y = scale(y, scene->mlx.win_size.y,
// 					scene->pict.pos.y, scene->pict.size.y)
// 				- scene->pict.size.y / 2;
// 		}
// 		else
// 			scene->pict.mov_lock = !scene->pict.mov_lock;
// 	}
// 	draw_win(scene);
// 	return (0);
// }
