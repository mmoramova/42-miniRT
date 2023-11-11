/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibx.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:17:22 by josorteg          #+#    #+#             */
/*   Updated: 2023/11/11 13:02:15 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft.h"
# include "mlx.h"
# include <math.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdint.h>

typedef struct s_vec2
{
	int		x;
	int		y;
}				t_vec2;

typedef struct s_vecd2
{
	double		x;
	double		y;
}				t_vecd2;

typedef struct s_unr
{
	double		r;
	double		i;
}				t_unr;

typedef struct s_pixel
{
	int		x;
	int		y;
	int		color;
}				t_pixel;

struct	s_pict;
struct	s_painter;

typedef struct s_mlx
{
	void		*image;
	char		*buff;
	int			buf_wid;
	void		*window;
	void		*mlx;
	t_vec2		win_size;
	int			bpp;
	int			endian;
}				t_mlx;

typedef struct s_pict
{
	const char	*name;
	t_vecd2		size;
	t_vecd2		pos;
	int32_t		iter_num;
	bool		movable;
	bool		mov_lock;
}				t_pict;

typedef struct s_painter
{
	t_mlx		mlx;
	t_pict		pict;
	t_vecd2		mouse_pos;
}				t_painter;

int			check_frac(char *frac);
void		ft_mensaje(void);

void		init_Mandelbrot(t_painter *painter);
void		init_Julia(t_painter *painter);
void		init_ship(t_painter *painter);
void		init_fract(const char *frac, t_painter *painter);
void		init(t_painter *painter);

int			display_mlx_win(t_painter *painter);

int			key_hook(int keycode, t_painter *painter);
int			mouse_hook(int x, int y, t_painter *painter);
int			scroll_hook(int button, int x, int y, t_painter *painter);
int			painter_exit(t_painter *fractol);

void		zoom_in(t_painter *painter, t_vec2 pos);
void		zoom_out(t_painter *painter, t_vec2 pos);

void		draw_win(t_painter *painter);
void		draw_px(t_painter *painter, t_vec2 pos, int32_t *table);
void		put_pixel(t_mlx *mlx, int x, int y, int color);
int32_t		fade(int32_t step, int32_t max_iter, int32_t *table);

int32_t		draw_julia(t_painter *painter, t_vec2 pos);
int32_t		draw_mandelbrot(t_painter *painter, t_vec2 pos);
int32_t		draw_ship(t_painter *painter, t_vec2 pos);

#endif
