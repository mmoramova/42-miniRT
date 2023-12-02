/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_noprintable.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 11:38:47 by mmoramov          #+#    #+#             */
/*   Updated: 2023/12/02 12:08:00 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isspace(int c)
{
	if (c == 32 || c == 9 || (c >= 11 && c <= 13))
		return (1);
	return (0);
}

int	ft_wordcount(char const *s, char c)
{
	int	nbr;
	int	is_c;

	nbr = 0;
	is_c = 1;
	while (*s)
	{
		if (*s != c && ft_isspace(*s) == 0 && is_c)
		{
			is_c = 0;
			nbr++;
		}
		else if (*s == c || ft_isspace(*s) == 1)
			is_c = 1;
		s++;
	}
	return (nbr);
}

int	ft_wordlen(char const *s, char c)
{
	int	len;

	len = 0;
	while (*s && ft_isspace(*s) == 0 && *s++ != c)
		len++;
	return (len);
}

void	ft_free(char **s, int len)
{
	while (len--)
		free(s[len]);
	free(s);
}

char	**ft_split_noprintable(char const *s, char c)
{
	int		i;
	char	**p;

	i = 0;
	p = malloc(sizeof(char *) * (ft_wordcount(s, c) + 1));
	if (!p)
		return (NULL);
	while (*s)
	{
		if (*s != c && ft_isspace(*s) == 0)
		{
			p[i] = ft_substr(s, 0, ft_wordlen(s, c));
			if (!p[i])
			{
				ft_free(p, i);
				return (NULL);
			}
			i++;
			s += ft_wordlen(s, c) - 1;
		}
		s++;
	}
	p[i] = NULL;
	return (p);
}

/*int main(void)
{
	char *s  = ",,abcd,efgh,ijklm,,";
	char *s2 = "Test";
	char *s3;
	s3 = "Hi";

	char *a[2];
     a[0] = "test";
     a[1] = s3;

	 char **t;
	 t = ft_split(s, ',');
//	 return(a);
	printf("%d\n", ft_wordcount(s, ','));

	printf("%d\n", ft_wordlen(s, ','));
   //	printf("%s",a[1]);
    printf("%s", t[0]);
}
*/
