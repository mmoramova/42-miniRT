/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_old.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 09:07:33 by josorteg          #+#    #+#             */
/*   Updated: 2023/11/11 13:03:56 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx.h"

void	draw_px(t_painter *painter, t_vec2 pos, int32_t *table)
{
	int32_t	iter_num;
	int32_t	color;

	// color = 0;
	// iter_num = 0;
	// if (!ft_strncmp("mandelbrot", painter->pict.name, 10))
	// 	iter_num = draw_mandelbrot(painter, pos);
	// if (!ft_strncmp("Julia", painter->pict.name, 5))
	// 	iter_num = draw_julia(painter, pos);
	// if (!ft_strncmp("ship", painter->pict.name, 4))
	// 	iter_num = draw_ship(painter, pos);
	// color = fade(iter_num, painter->pict.iter_num, table);
	//FUNCION MATEMATICA QUE DETECTA EL COLOR POR RAY TRACING!!
	put_pixel(&painter->mlx, pos.x, pos.y, color);
}

void	draw_win(t_painter *painter)
{
	t_vec2	tmp;
	int32_t	*table;
	int		i;

	(0 || (i = 0) || (tmp.y = 0));
	mlx_clear_window(painter->mlx.mlx, painter->mlx.window);
	while (tmp.y < painter->mlx.win_size.y)
	{
		tmp.x = 0;
		while (tmp.x < painter->mlx.win_size.x)
		{
			draw_px(painter, tmp, table);
			tmp.x++;
		}
		tmp.y++;
	}
	mlx_put_image_to_window(painter->mlx.mlx, painter->mlx.window,
		painter->mlx.image, 0, 0);
	free(table);
}

void	put_pixel(t_mlx *mlx, int x, int y, int color)
{
	int		*img;

	img = (int *) mlx->buff;
	if (x >= 0 && x < mlx->win_size.x && y >= 0 && y < mlx->win_size.y)
		img[x + mlx->win_size.x * y] = color;
}


