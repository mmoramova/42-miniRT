/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 10:24:37 by josorteg          #+#    #+#             */
/*   Updated: 2023/10/04 09:07:01 by josorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"
/*#include <fcntl.h>
#include <stdio.h>*/

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
	return ;
}
/*
int main()
{
	int	fd;

	fd = open("text.txt",O_WRONLY);
	printf("%d",fd);
	ft_putchar_fd('h',fd);

}*/
