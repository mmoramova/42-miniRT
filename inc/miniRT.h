/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 12:59:11 by mmoramov          #+#    #+#             */
/*   Updated: 2023/12/09 17:45:00 by josorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include "keyscode.h"
# include "mlx.h"
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
	t_vector	l_point;
	t_vector	l_vec;
}		t_line;

typedef struct s_ray
{
	t_line		line;
	bool		colision;
	t_vector	colision_point;
	double		distance;
	t_rgb		color;
	t_vector	n_colision_vector;
	bool		type; //0 ray, 1 light
	int			c_orderref;
	int			l_orderref;
}	t_ray;

typedef struct s_surface
{
	double		a;
	double		b;
	double		c;
	double		d;
	t_vector	nvector;
}	t_surface;

/* BASICS */
typedef struct s_amblight
{
	double			al_ratio;
	t_rgb			al_color;
	int				al_count;
}					t_amblight;

typedef struct s_camera
{
	t_vector	c_point;
	t_vector	c_point_init;
	t_vector	c_inter;
	t_vector	c_nvector;
	t_vector	c_up;
	t_vector	c_left;
	double		c_angle;
	t_surface	c_surface;
	t_vector	c_ray;
	int			c_count;
}				t_camera;

typedef struct s_light
{
	t_vector	l_point;
	double		l_brightness;
	t_line		l_ray;
	t_rgb		color;

}				t_light;

/* OBJECTS */
typedef struct s_sphere
{
	t_vector	sp_point;
	double		sp_diameter;
	t_rgb		sp_color;
	t_vector	sp_radium;
	int			sp_orderref;
}				t_sphere;

typedef struct s_plane
{
	t_vector	p_point;
	t_vector	p_nvector;
	t_rgb		p_color;
	t_surface	p_surface;
	int			p_orderref;
}				t_plane;

typedef struct s_cylinder
{
	t_vector	c_point;
	t_vector	c_direction;
	double		c_diameter;
	double		c_height;
	t_rgb		c_color;
	t_vector	c_nvector;
	t_vector	c_vh;
	t_vector	c_upper;
	t_vector	c_down;
	t_plane		upper_p;
	t_plane		down_p;
	int			c_orderref;
}				t_cylinder;

/* SCENE */
typedef struct s_mlx
{
	void		*image;
	char		*buff;
	int			buf_wid;
	void		*window;
	void		*mlx;
	t_pixel		win_size;
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

///scene.c
void		scene_create(t_scene *scene, char *file);
void		scene_fill(t_scene *scene, char **datarow, int *orderref);
void		free_datarow(char **s);

///utils.c
int			ft_check_arg(char *file);
t_vector	find_nvector(t_vector v1, double length);
void		eq_two_grade(double *c);
t_line		l_create(t_vector pi, t_vector pf);
void		ft_error(t_scene *scene, int exitnumber, char *txt);

///set_objects.c 1,2;
void		set_amblight(t_scene *scene, char **datarow);
void		set_camera(t_scene *scene, char **datarow);
void		set_light(t_scene *scene, char **datarow);
void		set_sphere(t_scene *scene, char **datarow, int *orderref);
void		set_plane(t_scene *scene, char **datarow, int *orderref);
void		set_cylinder(t_scene *scene, char **datarow, int *orderref);
void		set_planes_cylinder(t_plane *plane, t_vector point, t_vector axis);

///check_objects.c 1,2;
void		check_amblight(t_scene *scene, char **datarow);
void		check_camera(t_scene *scene, char **datarow);
void		check_light(t_scene *scene, char **datarow);
void		check_sphere(t_scene *scene, char **datarow);
void		check_plane(t_scene *scene, char **datarow);
void		check_cylinder(t_scene *scene, char **datarow);

///check_input.c 1,2
int			check_ratio(char *data);
int			check_angle(char *data);
int			check_color(char *data);
int			check_vector(char *data);
int			check_nvector(char *data);
int			check_nbrpositive(char *data);

///rgb.c
t_rgb		set_rgb(char *row);
t_rgb		rgb_mult(t_rgb c1, t_rgb c2);
t_rgb		rgb_multd(t_rgb c1, double r);
t_rgb		rgb_sum(t_rgb c1, t_rgb c2);
t_rgb		rgb_norm(t_rgb c);

//ray.c
void		ray_init(t_ray *ray, bool type, t_vector v1, t_vector v2);
int			ray_camera(t_scene *scene, t_pixel pos);
bool		ray_light(t_scene *scene, t_ray *ray, t_light *light);
void		ray_update(t_ray *ray, t_rgb object_color, double d, t_vector normal_colision, int orderref);

//intersection.c
void		intersection_vision(t_scene *scene, t_ray *r);
void		intersection_sphere(t_ray *r, t_sphere *o);
void		intersection_plane(t_ray *r, t_plane *o);
void		plane_cyl(t_ray *r, t_cylinder *o, t_vector point, t_plane plane);
void		intersection_cylinder(t_ray *r, t_cylinder *o);

//set_color.c
void		set_color(t_scene *scene, t_ray *ray);
t_rgb		ambient_color(t_ray *r, t_amblight *a);
t_rgb		diffuse_color(t_ray *r, t_light *l);
t_rgb		specular_color(t_scene *scene, t_ray *r, t_light *l);

///vector.c 1,2
t_vector	vector_init(double x, double y, double z);
t_vector	set_vector(char *row);
t_vector	v_multd(double esc, t_vector vec);
t_vector	v_substr(t_vector v1, t_vector v2);
t_vector	v_sum(t_vector v1, t_vector v2);
double		v_mod(t_vector v1);
double		distance(t_vector point1, t_vector point2);
double		v_inner(t_vector vector1, t_vector vector2);
t_vector	v_mult(t_vector vector1, t_vector vector2);
t_vector	v_norm(t_vector v1);

///free.c
void		free_scene(t_scene *scene);
void		free_light(void *light);
void		free_sphere(void *sphere);
void		free_plane(void *plane);
void		free_cylinder(void *cylinder);

///mlx.c, draw.c
void		window_create(t_scene *scene);
int			display_mlx_win(t_scene *scene);
int			scene_exit(t_scene *scene);
int			scene_exit(t_scene *scene);
void		draw_px(t_scene *scene, t_pixel pos);
int			key_hook(int keycode, t_scene *scene);
void		draw_win(t_scene *scene);
void		put_pixel(t_mlx *mlx, int x, int y, int color);

//test
//void	screen_set(t_scene *scene);
void		print_vector(t_vector vector, char *str);

#endif
