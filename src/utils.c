/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmuller <flmuller@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:25:58 by flmuller          #+#    #+#             */
/*   Updated: 2024/05/17 09:39:49 by flmuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"

void	*ft_memset(void *s, int c, size_t n)
{
	char	*ptr;
	int		i;

	i = 0;
	ptr = (char *) s;
	while (i < (int)n)
	{
		ptr[i] = c;
		i++;
	}
	return (s);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*res;
	unsigned int	tsize;
	unsigned int	i;

	tsize = nmemb * size;
	if (!nmemb || !size)
		return (malloc(0));
	if (tsize / size != nmemb || tsize / nmemb != size)
		return (0);
	res = malloc(tsize);
	if (res)
	{
		i = 0;
		while (i < tsize)
		{
			res[i] = '\0';
			i++;
		}
	}
	return ((void *)res);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!src && !dest)
		return (0);
	while (i < n)
	{
		((unsigned char *) dest)[i] = ((unsigned char *) src)[i];
		i++;
	}
	return (dest);
}
