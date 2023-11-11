/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 12:59:11 by mmoramov          #+#    #+#             */
/*   Updated: 2023/11/11 18:49:42 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include"libft.h"
//# include"mlx.h"
# include <math.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <fcntl.h>

/* UTILS */
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

/* BASICS */
typedef struct s_amblight
{
	double			ratio;
	t_rgb			color;
}					t_amblight;

typedef struct s_camera
{
	t_vector	point;
	t_vector	nvector;
	int			angle; //int?
}				t_camera;

typedef struct s_light
{
	t_vector	point;
	double		brightness;
	//t_rgb		color; for bonus
}				t_light;

/* OBJECTS */
typedef struct s_sphere
{
	t_vector	point;
	double		diameter;
	t_rgb		color;
}				t_sphere;

typedef struct s_plane
{
	t_vector	point;
	t_vector	nvector;
	t_rgb		color;
}				t_plane;

typedef struct s_cylinder
{
	t_vector	point;
	t_vector	nvector;
	double		diameter;
	double		height;
	t_rgb		color;
}				t_cylinder;

/* SCENE */
typedef struct s_scene
{
	/*t_amblight	*amblight;
	t_camera	*camera;
	t_light		*light;
	t_sphere	*spheres;
	t_plane		*planes;
	t_cylinder	*cylinders;*/

	t_list	*amblight;
	t_list	*camera;
	t_list	*light;
	t_list	*spheres;
	t_list	*planes;
	t_list	*cylinders;
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
void free_amblight(void *amblight);
void free_camera(void *camera);
void free_light(void *light);
void free_sphere(void *sphere);
void free_plane(void *plane);
void free_cylinder(void *cylinder);

#endif
