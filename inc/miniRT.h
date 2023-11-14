/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 12:59:11 by mmoramov          #+#    #+#             */
/*   Updated: 2023/11/14 19:48:16 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include"libft.h"
# include"keyscode.h"
# include"mlx.h"
# include <math.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <fcntl.h>

/* UTILS */
typedef struct s_pixel
{
	int		x;
	int		y;
}				t_pixel;

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}				t_vector;

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
	int	rgb;
}				t_rgb;

typedef struct s_line
{
	double	x0;
	double	y0;
	double	z0;
	double	Ux;
	double	Uy;
	double	Uz;

}		t_line;

typedef struct s_ray
{
	t_line		line;
	bool		colision;
	t_vector	colision_point;
	double		distance;
	t_rgb		color;
	t_vector	nvector;
}	t_ray;

typedef struct s_surface
{
	double		A;
	double		B;
	double		C;
	double		D;
	t_vector	nvector;

}	t_surface;

/* BASICS */
typedef struct s_amblight
{
	double			al_ratio;
	t_rgb			al_color;

}					t_amblight;

typedef struct s_camera
{
	t_vector	c_point;
	t_vector	c_inter; //point of intersection with unitary vector
	t_vector	c_nvector;
	t_vector	c_up;
	t_vector	c_left;
	double		c_angle;
	t_surface	c_surface;
}				t_camera;

typedef struct s_light
{
	t_vector	l_point;
	double		l_brightness;
	t_line		lightray;
	//t_rgb		color; for bonus

}				t_light;

/* OBJECTS */
typedef struct s_sphere
{
	t_vector	sp_point;
	double		sp_diameter;
	t_rgb		sp_color;
	t_vector	sp_radium;
}				t_sphere;

typedef struct s_plane
{
	t_vector	p_point;
	t_vector	p_nvector;
	t_rgb		p_color;
	t_surface	p_surface;
}				t_plane;

typedef struct s_cylinder
{
	t_vector	c_point;
	t_vector	c_direction;
	double		c_diameter;
	double		c_height;
	t_rgb		c_color;
	t_vector	c_nvector;
}				t_cylinder;

/* SCENE */

typedef struct s_mlx
{
	void		*image;
	char		*buff;
	int			buf_wid;
	void		*window;
	void		*mlx;
	t_pixel		win_size;	//aprox
	int			bpp;
	int			endian;
}				t_mlx;

typedef struct s_scene
{
	t_line		visionray;
	t_amblight	amblight;
	t_camera	camera;
	t_list		*lights;
	t_list		*spheres;
	t_list		*planes;
	t_list		*cylinders;
	t_mlx		mlx;
}				t_scene;

//miniRT.c

//scene.c
void scene_init(t_scene *scene);
void scene_create(t_scene *scene, char *file);
void scene_fill_line(t_scene *scene, char **datarow);

//utils.c
int	ft_check_arg(char *file);

//set_objects 1,2;
void	set_amblight(t_scene *scene, char **datarow);
void	set_camera(t_scene *scene, char **datarow);
void	set_light(t_scene *scene, char **datarow);
void	set_sphere(t_scene *scene, char **datarow);
void	set_plane(t_scene *scene, char **datarow);
void	set_cylinder(t_scene *scene, char **datarow);

//rgb.c
int	ft_create_trgb(int r, int g, int b);
t_rgb str2rgb(char *row);
t_rgb set_rgb(char *x, char *y, char *z);

//vector.c
t_vector vector_init(double x, double y, double z);
t_vector str2vector(char *row);
t_vector set_vector(char *x, char *y, char *z);

//error.c
void ft_error(t_scene *scene, int exitnumber, char *txt);

//free.c
void free_scene(t_scene *scene);
void free_light(void *light);
void free_sphere(void *sphere);
void free_plane(void *plane);
void free_cylinder(void *cylinder);

//minilib
void	init(t_scene *scene);
int		display_mlx_win(t_scene *scene);
void	draw_px(t_scene *scene, t_pixel pos);
void	draw_win(t_scene *scene);
void	put_pixel(t_mlx *mlx, int x, int y, int color);
//hook
int		key_hook(int keycode, t_scene *scene); //exit
int		scene_exit(t_scene *scene);

//Calculus
int		ray_color(t_scene *scene, t_pixel pos);\
void	ray_update(t_ray *ray, t_rgb object_color, double d);
void 	D_plane (t_camera *camera);
void 	camera_intersection (t_camera *camera);
t_vector	camera_first_vector (t_camera *camera);
void 	intersection_vision (t_scene *scene, t_ray *ray);
void	intersection_sphere(t_ray *ray, t_sphere *object);
void	intersection_plane(t_ray *ray, t_plane *object);
void	init_screen(t_scene *scene);

//General calculus
double		distance (t_vector point1,t_vector point2);
double		producto_escalar (t_vector vector1, t_vector vector2);
t_vector 	producto_vectorial (t_vector vector1, t_vector vector2);
t_vector	find_normal_vector (t_vector v1, double lengh);
t_vector 	normalize_vector(t_vector v1);
double		modulo(t_vector v1);
t_line		two_points_line (t_vector pi, t_vector pf);

#endif
