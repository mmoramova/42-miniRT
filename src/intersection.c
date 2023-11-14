/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:27:38 by josorteg          #+#    #+#             */
/*   Updated: 2023/11/14 19:49:37 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include"miniRT.h"

void		intersection_sphere(t_ray *ray, t_sphere *object)
{
	double	discriminante;
	t_vector u_norm;
	t_vector punto_centro;
	t_vector punto_recta;
	double	d;

	u_norm.x = ray->line.Ux;
	u_norm.y = ray->line.Uy;
	u_norm.z = ray->line.Uz;
	punto_recta.x =ray->line.x0;
	punto_recta.y =ray->line.y0;
	punto_recta.z =ray->line.z0;
	u_norm = normalize_vector (u_norm);
	punto_centro.x = ray->line.x0 - object->sp_point.x;
	punto_centro.y = ray->line.y0 - object->sp_point.y;
	punto_centro.z = ray->line.z0 - object->sp_point.z;
	//printf("punto_centro (%f,%f,%f)\n",ray->line.Ux,ray->line.Uy,ray->line.Uz);
	//printf("Producto escalar =%f,modulo al cuadrado=%f)\n",producto_escalar(u_norm,punto_centro),pow(modulo(punto_centro),2));
	discriminante = pow(producto_escalar(u_norm,punto_centro),2)- pow(modulo(punto_centro),2) + pow(object->sp_diameter/2,2);
	//printf("discriminante = %f\n",discriminante);
	if (discriminante < 0)
	{
		//no colision, no point, no normal
		//ray->colision = 0;
		return ;
	}
	else if ( discriminante == 0)
		d = -producto_escalar(u_norm,punto_centro);
	else
	{
		d = -producto_escalar(u_norm,punto_centro) + discriminante;
		if (-producto_escalar(u_norm,punto_centro) - discriminante < d)
			d = -producto_escalar(u_norm,punto_centro) - discriminante;
	}
	if (ray->colision == 0 || ray->distance > d)
		ray_update(ray, object->sp_color, d);
}

void	intersection_plane(t_ray *ray, t_plane *object)
{
	//todo
	double	d;

	d = 0.0;

	if (ray->colision == 0 || ray->distance > d)
		ray_update(ray, object->p_color, d);
}

void ray_update(t_ray *ray, t_rgb object_color, double d)
{
		ray->colision = 1;
		ray->colision_point.x = ray->line.x0 + d*ray->line.Ux;
		ray->colision_point.y = ray->line.y0 + d*ray->line.Uy;
		ray->colision_point.z = ray->line.z0 + d*ray->line.Uz;
		ray->color = object_color;
		ray->distance = d;

}
