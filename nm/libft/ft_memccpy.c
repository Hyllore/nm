/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 18:57:21 by droly             #+#    #+#             */
/*   Updated: 2015/12/07 16:38:48 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*s1;
	unsigned char	*s2;

	i = 0;
	s1 = (unsigned char*)dst;
	s2 = (unsigned char*)src;
	if (!s1 && !s2)
		return (NULL);
	while (i < n)
	{
		s1[i] = s2[i];
		if (s2[i] == (unsigned char)c)
		{
			i++;
			return (char *)&(s1[i]);
		}
		i++;
	}
	return (NULL);
}
