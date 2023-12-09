/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_objects.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 17:09:00 by mmoramov          #+#    #+#             */
/*   Updated: 2023/12/09 14:13:19 by josorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	set_amblight(t_scene *scene, char **datarow)
{
	check_amblight(scene, datarow);
	scene->amblight.al_ratio = ft_atod(datarow[1]);
	scene->amblight.al_color = set_rgb(datarow[2]);
	scene->amblight.al_count = 1;
}

void	set_camera(t_scene *scene, char **datarow)
{
	t_vector	width_v;
	t_vector	hight_v;
	t_vector	north;
	double		fov;

	check_camera(scene, datarow);
	scene->camera.c_point_init = set_vector(datarow[1]);
	print_vector(scene->camera.c_point_init, "camara inicial");
	scene->camera.c_point = vector_init(0, 0, 0);
	scene->camera.c_nvector = v_norm(set_vector(datarow[2]));
	scene->camera.c_angle = ft_atod(datarow[3]) * 2 * M_PI / 360;
	scene->camera.c_count = 1;
	north = find_nvector(scene->camera.c_nvector, 1);
	fov = 150;
	scene->camera.c_ray = v_norm(v_sum(scene->camera.c_point,
				scene->camera.c_nvector));
	width_v = v_norm(v_mult(scene->camera.c_ray, north));
	hight_v = v_mult(width_v, scene->camera.c_ray);
	scene->camera.c_left = v_multd(fov * 2 * tan(scene->camera.c_angle / 2),
			width_v);
	scene->camera.c_up = v_multd((fov * 2 * tan(scene->camera.c_angle / 2)
				* scene->mlx.win_size.y) / scene->mlx.win_size.x, hight_v);
	scene->camera.c_ray = v_multd(fov, scene->camera.c_ray);
}

void	set_light(t_scene *scene, char **datarow)
{
	t_light	*light;

	check_light(scene, datarow);
	light = (t_light *) malloc(sizeof(t_light));
	if (!light)
		ft_error(scene, 1, "Malloc error - light");
	light->l_point = v_substr(set_vector(datarow[1]),
			scene->camera.c_point_init);
	light->l_brightness = ft_atod(datarow[2]);
	light->color = set_rgb(datarow[3]);
	ft_lstadd_front(&(scene->lights), ft_lstnew(light));
}

void	set_sphere(t_scene *scene, char **datarow, int *orderref)
{
	t_sphere	*sphere;

	check_sphere(scene, datarow);
	sphere = (t_sphere *) malloc(sizeof(t_sphere));
	if (!sphere)
		ft_error(scene, 1, "Malloc error - sphere");
	sphere->sp_point = v_substr(set_vector(datarow[1]),
			scene->camera.c_point_init);
	sphere->sp_diameter = ft_atod(datarow[2]);
	sphere->sp_color = set_rgb(datarow[3]);
	sphere->sp_orderref = *orderref;
	*orderref += 1;
	ft_lstadd_front(&(scene->spheres), ft_lstnew(sphere));
}

void	set_plane(t_scene *scene, char **datarow, int *orderref)
{
	t_plane	*plane;

	check_plane(scene, datarow);
	plane = (t_plane *) malloc(sizeof(t_plane));
	if (!plane)
		ft_error(scene, 1, "Malloc error - plane");
	plane->p_point = v_substr(set_vector(datarow[1]),
			scene->camera.c_point_init);
	plane->p_nvector = set_vector(datarow[2]);
	plane->p_color = set_rgb(datarow[3]);
	plane->p_orderref = *orderref;
	*orderref += 1;
	plane->p_surface.a = -plane->p_nvector.x;
	plane->p_surface.b = -plane->p_nvector.y;
	plane->p_surface.c = -plane->p_nvector.z;
	plane->p_surface.d = -(plane->p_surface.a * (plane->p_point.x)
			+ plane->p_surface.b * (plane->p_point.y)
			+ plane->p_surface.c * (plane->p_point.z));
	ft_lstadd_front(&(scene->planes), ft_lstnew(plane));
}
