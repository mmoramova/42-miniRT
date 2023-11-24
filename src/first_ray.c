/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 13:49:12 by josorteg          #+#    #+#             */
/*   Updated: 2023/11/21 18:03:29 by josorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"miniRT.h"

int	ray_color(t_scene *scene,t_pixel pos)
{
	t_vector	with;
	t_vector	higt;
	t_vector	init;
	t_ray		ray_vision;

	with = scene->camera.c_left;
	higt = scene->camera.c_up;
	init.x = scene->camera.c_ray.x + with.x + higt.x - 2 * pos.x * (with.x/scene->mlx.win_size.x) - 2 * pos.y *(higt.x/scene->mlx.win_size.y);
	init.y = scene->camera.c_ray.y + with.y + higt.y - 2 * pos.x * (with.y/scene->mlx.win_size.x) - 2 * pos.y *(higt.y/scene->mlx.win_size.y);
	init.z = scene->camera.c_ray.z + with.z + higt.z - 2 * pos.x * (with.z/scene->mlx.win_size.x) - 2 * pos.y *(higt.z/scene->mlx.win_size.y);
	//printf("ray = (%f,%f,%f)\n",init.x,init.y,init.z);
	//calculate the ray vector
	ray_vision.color.rgb = 0;
	ray_vision.n_colision_vector = vector_init(0,0,0);
	ray_vision.distance = 30000000;
	ray_vision.colision = 0;
	ray_vision.line = (two_points_line (scene->camera.c_point,init));
	//color = intersection_sphere (ray_vision.line,(t_sphere*) scene->spheres->content);
	intersection_vision (scene, &ray_vision);
	return(ray_vision.color.rgb);
}
void intersection_vision (t_scene *scene, t_ray *ray)
{
	t_list	*sp_list;
	t_list	*p_list;
	t_list	*c_list;

	sp_list = scene->spheres;
	p_list = scene->planes;
	c_list = scene->cylinders;

	if (sp_list)
	{
		while (sp_list->content != NULL)
		{
			intersection_sphere (ray,(t_sphere*) sp_list->content);
			sp_list = sp_list -> next;
		}
	}
	if (p_list)
	{
		while (p_list->content != NULL)
		{
			//write(1,"a",1);
			intersection_plane (ray,(t_plane*) p_list->content);
			p_list = p_list -> next;
		}
	}
	if (c_list)
	{
		while (c_list->content != NULL)
		{
			//intersection_cylinder (ray,(t_cylinder*) c_list->content);
			c_list = c_list -> next;
		}
	}
	//provisional
	pixel_color_normal(ray);
	//pixel_color(ray);
	return ;
}

void	pixel_color(t_ray *ray)
{
	//int max_color;

	//double	al_ratio = 0.85;
	//t_rgb	al_color = set_rgb("255","255","255");

	double		l_brightness = 1;
	t_vector	l_point = vector_init(1,1,1);
	t_rgb		l_color = set_rgb("255","255","0");


	t_vector	o_nvector = ray->n_colision_vector;
	t_vector	o_point = ray->colision_point;
	t_vector	l_vector = vectorminus(l_point, o_point);

	o_nvector = normalize_vector(o_nvector);
	l_vector = normalize_vector(l_vector);
	if (ray->color.rgb == 0)
	{
		ray->color.rgb = ft_create_trgb (0,0,0);
		return;
	}
	//ray->color.r= al_color.r * al_ratio + ray->color.r * (1-al_ratio);
	//ray->color.g= al_color.g * al_ratio + ray->color.g * (1-al_ratio);
	//ray->color.b= al_color.b * al_ratio + ray->color.b * (1-al_ratio);
	//ray->color.r= al_color.r * al_ratio + ((ray->color.r * l_brightness) * l_color.r * fmax(0, producto_escalar(l_vector,o_nvector)) * (1-al_ratio));
	//ray->color.g= al_color.g * al_ratio + ((ray->color.g * l_brightness) * l_color.g * fmax(0, producto_escalar(l_vector,o_nvector)) * (1-al_ratio));
	//ray->color.b= al_color.b * al_ratio + ((ray->color.b * l_brightness) * l_color.b * fmax(0, producto_escalar(l_vector,o_nvector)) * (1-al_ratio));
	//new_color.x= ((ray->color.r/255.0) * (l_color.r/255.0) * l_brightness * fmax(0, producto_escalar(l_vector,o_nvector)));
	//new_color.y= ((ray->color.g/255.0) * (l_color.g/255.0) * l_brightness * fmax(0, producto_escalar(l_vector,o_nvector)));
	//new_color.z= ((ray->color.b/255.0) * (l_color.b/255.0) * l_brightness * fmax(0, producto_escalar(l_vector,o_nvector)));

	ray->color.r= ((ray->color.r/255.0) * (l_color.r/255.0) * l_brightness * fmax(0, producto_escalar(l_vector,o_nvector)))*255;
	ray->color.g= ((ray->color.g/255.0) * (l_color.g/255.0) * l_brightness * fmax(0, producto_escalar(l_vector,o_nvector)))*255;
	ray->color.b= ((ray->color.b/255.0) * (l_color.b/255.0) * l_brightness * fmax(0, producto_escalar(l_vector,o_nvector)))*255;
	//ray->color.r= 255*((al_color.r/255.0)*(ray->color.r/255.0) * al_ratio + (ray->color.r/255.0) * (1-al_ratio));
	//ray->color.g= 255*((al_color.g/255.0)*(ray->color.g/255.0) * al_ratio + (ray->color.g/255.0) * (1-al_ratio));
	//ray->color.b= 255*((al_color.b/255.0)*(ray->color.b/255.0) * al_ratio + (ray->color.b/255.0) * (1-al_ratio));

	//printf("colors (%d,%d,%d)\n", ray->color.r,ray->color.g,ray->color.b);
	/*if (ray->color.r > 255 || ray->color.g > 255 || ray->color.b > 255 )
	{
		max_color = fmax(fmax(ray->color.r,ray->color.g),ray->color.b);
		//printf("max color is %d\n", max_color);

		ray->color.r= (255 * ray->color.r) / max_color;
		ray->color.g= (255 * ray->color.g) / max_color;
		ray->color.b= (255 * ray->color.b) / max_color;
	}*/
	ray->color.rgb = ft_create_trgb (ray->color.r,ray->color.g,ray->color.b);
	//printf("colors (%d,%d,%d)\n", ray->color.r,ray->color.g,ray->color.b);
}

//provisional
void	pixel_color_normal(t_ray *ray)
{
	double	coef;
	t_vector u_norm;
	t_vector light;

	light= vector_init(50 -ray->colision_point.x,50-ray->colision_point.y,50-ray->colision_point.z);
	u_norm.x = ray->line.Ux;
	u_norm.y = ray->line.Uy;
	u_norm.z = ray->line.Uz;
	coef = 0;
	if (ray->colision == 1)
		coef =fabs(producto_escalar (normalize_vector(light),normalize_vector(ray->n_colision_vector)));
	ray->color.r= ray->color.r*coef;
	ray->color.g= ray->color.g*coef;
	ray->color.b= ray->color.b*coef ;
	ray->color.rgb = ft_create_trgb (ray->color.r,ray->color.g,ray->color.b);

	//printf("escalar = %f u_norm = %f color = %d\n", coef,modulo(u_norm),ray->color.rgb);
}
