/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 09:07:33 by josorteg          #+#    #+#             */
/*   Updated: 2023/11/14 12:59:24 by josorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "miniRT.h"

void	draw_px(t_scene *scene, t_pixel pos)
{
	int	color;

	color = 0;
	color = ray_color(scene,pos);
	//printf("pixel x,y= (%d,%d)  color = %d\n",pos.x, pos.y,color);
	// iter_num = 0;
	// if (!ft_strncmp("mandelbrot", scene->pict.name, 10))
	// 	iter_num = draw_mandelbrot(scene, pos);
	// if (!ft_strncmp("Julia", scene->pict.name, 5))
	// 	iter_num = draw_julia(scene, pos);
	// if (!ft_strncmp("ship", scene->pict.name, 4))
	// 	iter_num = draw_ship(scene, pos);
	// color = fade(iter_num, scene->pict.iter_num, table);
	//FUNCION MATEMATICA QUE DETECTA EL COLOR POR RAY TRACING!!
	put_pixel(&scene->mlx, pos.x, pos.y, color);
}

void	draw_win(t_scene *scene)
{
	t_pixel	tmp;
	int		i;

	(0 || (i = 0) || (tmp.y = 0));
	mlx_clear_window(scene->mlx.mlx, scene->mlx.window);
	while (tmp.y < scene->mlx.win_size.y)
	{
		tmp.x = 0;
		while (tmp.x < scene->mlx.win_size.x)
		{
			draw_px(scene, tmp);
			tmp.x++;
		}
		tmp.y++;
	}
	mlx_put_image_to_window(scene->mlx.mlx, scene->mlx.window,
		scene->mlx.image, 0, 0);
}

void	put_pixel(t_mlx *mlx, int x, int y, int color)
{
	int		*img;

	img = (int *) mlx->buff;
	if (x >= 0 && x < mlx->win_size.x && y >= 0 && y < mlx->win_size.y)
		img[x + mlx->win_size.x * y] = color;
}


