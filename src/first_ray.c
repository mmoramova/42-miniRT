/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 13:49:12 by josorteg          #+#    #+#             */
/*   Updated: 2023/11/26 16:06:06 by mmoramov         ###   ########.fr       */
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

	//provisional
	//pixel_color_normal(ray_vision);
	pixel_color(scene, &ray_vision);

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

	return ;
}

bool	check_intersection (t_scene *scene, t_ray *ray, t_light *light)
{
	t_ray	ray_vision;

	ray_vision.color.rgb = 0;
	ray_vision.n_colision_vector = vector_init(0,0,0);
	ray_vision.distance = 30000000;
	ray_vision.colision = 0;
	ray_vision.line = (two_points_line (light->l_point,ray->colision_point));
	//color = intersection_sphere (ray_vision.line,(t_sphere*) scene->spheres->content);
	intersection_vision (scene, &ray_vision);

	//need to improve, not working
	if (ray_vision.colision == 0) // && ray->distance > ray_vision.distance)
		return 1;
	return 0;
}
void	pixel_color(t_scene *scene, t_ray *ray)
{
	t_list	*l_list;
	l_list = scene->lights;

	double	al_ratio = scene->amblight.al_ratio;
	t_rgb	al_color = scene->amblight.al_color;
	t_rgb	o_color = ray->color;

	t_rgb	ambient_color;
	t_rgb	light_color;
	t_rgb	specular_color;
	t_rgb	final_color;

	bool	in_shadow;

	final_color = set_rgb("0","0","0");

	//calculate ambient color
	if (ray->color.rgb == 0)
		ambient_color = set_rgb("0","0","0");
		//ambient_color = rgbXdouble(al_color,al_ratio);
	else
		ambient_color = rgbXrgb(o_color, rgbXdouble(al_color,al_ratio));

	if (l_list)
	{
		while (l_list->content != NULL)
		{

			in_shadow = check_intersection(scene,ray,(t_light*) l_list->content);
			//in_shadow = 0; //provisonal
			if (in_shadow == 0)
			{
				light_color = pixel_light_calculate (ray,(t_light*) l_list->content);
				final_color = rgb_add(light_color, final_color);
				specular_color = rgbXrgb(o_color,pixel_specular_calculate (scene, ray,(t_light*) l_list->content));
				final_color = rgb_add(specular_color, final_color);
			}
			l_list = l_list -> next;
		}
	}
	final_color = rgb_add(ambient_color, final_color);
	ray->color = rgb_norm(final_color);
}

t_rgb	pixel_light_calculate (t_ray *ray, t_light *light)
{
	t_vector	l_point = light->l_point;
	t_vector	o_point = ray->colision_point;
	double		l_brightness = light->l_brightness;

	t_rgb light_color;
	t_rgb		l_color = light->color;

	t_vector	o_nvector = normalize_vector(ray->n_colision_vector);
	t_vector	l_nvector = normalize_vector(vectorminus(l_point, o_point));

	if (ray->color.rgb == 0)
		light_color = set_rgb("0","0","0");
	else
		light_color = rgbXrgb(ray->color, rgbXdouble(rgbXdouble(l_color,l_brightness),fmax(0, producto_escalar(l_nvector,o_nvector))));
	return(light_color);
	//printf("colors (%d,%d,%d)\n", ray->color.r,ray->color.g,ray->color.b);
}

t_rgb	pixel_specular_calculate (t_scene *scene, t_ray *ray, t_light *light)
{
	t_vector	c_point = scene->camera.c_point;
	t_vector	l_point = light->l_point;
	t_vector	o_point = ray->colision_point;

	t_rgb		specular_color;
	t_rgb		s_color = light->color;
	double		specular_factor;

	t_vector	o_nvector = normalize_vector(ray->n_colision_vector);
	t_vector	l_nvector = normalize_vector(vectorminus(o_point, l_point));

	t_vector reflection_vector = vectorminus(l_nvector, escalarxvector(2 * producto_escalar(l_nvector, o_nvector), o_nvector));
	t_vector view_vector = normalize_vector(vectorminus(c_point, o_point));
	specular_factor = pow(fmax(0, producto_escalar(reflection_vector,view_vector)),32);

	if (ray->color.rgb == 0)
		specular_color = set_rgb("0","0","0");
	else
		specular_color = rgbXdouble(s_color,specular_factor);
		//specular_color = rgbXdouble(rgbXdouble(s_color,s_brightness),specular_factor);
	return(specular_color);
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
