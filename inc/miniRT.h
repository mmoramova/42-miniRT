/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 12:59:11 by mmoramov          #+#    #+#             */
/*   Updated: 2023/12/08 22:05:38 by mmoramov         ###   ########.fr       */
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
	t_vector	l_point;
	t_vector	l_vector;
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
	int				al_count;

}					t_amblight;

typedef struct s_camera
{
	t_vector	c_point;
	t_vector	c_point_init;
	t_vector	c_inter; //point of intersection with unitary vector
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

///scene.c
void scene_create(t_scene *scene, char *file);
void scene_fill(t_scene *scene, char **datarow, int *orderref);

//utils.c
int	ft_check_arg(char *file);

///set_objects 1,2;
void	set_amblight(t_scene *scene, char **datarow);
void	set_camera(t_scene *scene, char **datarow);
void	set_light(t_scene *scene, char **datarow);
void	set_sphere(t_scene *scene, char **datarow, int *orderref);
void	set_plane(t_scene *scene, char **datarow, int *orderref);
void	set_cylinder(t_scene *scene, char **datarow, int *orderref);
void	set_planes_cylinder (t_plane *plane,t_vector point,t_vector axis);

///check_objects 1,2;
void	check_amblight(t_scene *scene, char **datarow);
void	check_camera(t_scene *scene, char **datarow);
void	check_light(t_scene *scene, char **datarow);
void	check_sphere(t_scene *scene, char **datarow);
void	check_plane(t_scene *scene, char **datarow);
void	check_cylinder(t_scene *scene, char **datarow);

///check_input.c
int check_ratio(char *data);
int check_angle(char *data);
int check_color(char *data);
int check_vector(char *data);
int check_nbrpositive(char *data);

///rgb.c
t_rgb	set_rgb(char *row);
t_rgb	rgb_mult(t_rgb c1, t_rgb c2);
t_rgb	rgb_multd(t_rgb c1, double r);
t_rgb	rgb_sum(t_rgb c1, t_rgb c2);
t_rgb	rgb_norm(t_rgb c);

//set_color.c
void	set_color(t_scene *scene, t_ray *ray);
t_rgb	set_ambient_color (t_ray *ray, t_amblight *amblight);
t_rgb	set_diffuse_color (t_ray *ray, t_light *light);
t_rgb	set_specular_color (t_scene *scene, t_ray *ray, t_light *light);

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
void	window_create(t_scene *scene);
int		display_mlx_win(t_scene *scene);
void	draw_px(t_scene *scene, t_pixel pos);
void	draw_win(t_scene *scene);
void	put_pixel(t_mlx *mlx, int x, int y, int color);
//hook
int		key_hook(int keycode, t_scene *scene); //exit
int		scene_exit(t_scene *scene);

//Calculus
int		ray_color(t_scene *scene, t_pixel pos);
void	ray_update(t_ray *ray, t_rgb object_color, double d, t_vector normal_colision, int orderref);
void 	intersection_vision (t_scene *scene, t_ray *ray);
void	intersection_sphere(t_ray *ray, t_sphere *object);
void	intersection_cylinder(t_ray *ray,t_cylinder *object,t_vector point,t_plane plane);
void	intersection_plane(t_ray *ray, t_plane *object);
void	screen_set(t_scene *scene);
bool	check_intersection (t_scene *scene, t_ray *ray, t_light *light);

//General calculus
double		distance (t_vector point1,t_vector point2);
double		v_inner (t_vector vector1, t_vector vector2);
t_vector 	v_mult (t_vector vector1, t_vector vector2);
t_vector 	v_multd(double esc, t_vector vec);
t_vector	find_normal_vector (t_vector v1, double lengh);
t_vector 	v_norm(t_vector v1);
double		v_mod(t_vector v1);
t_line		l_create (t_vector pi, t_vector pf);
t_vector 	v_substr(t_vector v1, t_vector v2);
t_vector	v_sum(t_vector v1, t_vector v2);



//test
void	intersection_cylinder_test (t_ray *ray,t_cylinder *object);
void	print_vector(t_vector vector,char	*str);
#endif
