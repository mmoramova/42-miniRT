/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:27:38 by josorteg          #+#    #+#             */
/*   Updated: 2023/11/14 17:30:16 by josorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include"miniRT.h"

int		intersection_sfere(t_line ray, t_sphere *object)
{
	double	discriminante;
	t_vector u_norm;
	t_vector punto_centro;
	t_vector punto_recta;
	double		d;
	t_vector pcolision;

	u_norm.x = ray.Ux;
	u_norm.y = ray.Uy;
	u_norm.z = ray.Uz;
	punto_recta.x =ray.x0;
	punto_recta.y =ray.y0;
	punto_recta.z =ray.z0;
	u_norm = normalize_vector (u_norm);
	punto_centro.x = ray.x0 - object->sp_point.x;
	punto_centro.y = ray.y0 - object->sp_point.y;
	punto_centro.z = ray.z0 - object->sp_point.z;
	//printf("punto_centro (%f,%f,%f)\n",ray.Ux,ray.Uy,ray.Uz);
	//printf("Producto escalar =%f,modulo al cuadrado=%f)\n",producto_escalar(u_norm,punto_centro),pow(modulo(punto_centro),2));
	discriminante = pow(producto_escalar(u_norm,punto_centro),2)- pow(modulo(punto_centro),2) + pow(object->sp_diameter/2,2);
	//printf("discriminante = %f\n",discriminante);
	if (discriminante < 0)
		return (0);
		//no colision, no point, no normal

	else if ( discriminante == 0)
		d = -producto_escalar(u_norm,punto_centro);
	else
	{
		d = -producto_escalar(u_norm,punto_centro) + discriminante;
		if (-producto_escalar(u_norm,punto_centro) - discriminante < d)
			d = -producto_escalar(u_norm,punto_centro) - discriminante;
	}
	pcolision.x = ray.x0 + d*ray.Ux;
	pcolision.y = ray.y0 + d*ray.Uy;
	pcolision.z = ray.z0 + d*ray.Uz;
	pcolision = normalize_vector(pcolision);
	return (d * 10 + d * 100 + d * 1000);
}
