/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 10:55:50 by droly             #+#    #+#             */
/*   Updated: 2015/12/02 15:09:17 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned int	i;
	char			*tmp;
	char			*s1;
	char			*s2;

	i = 0;
	tmp = (char*)malloc(sizeof(char) * (n + 1));
	if (tmp == NULL)
		return (NULL);
	s1 = (char*)src;
	s2 = (char*)dest;
	while (i < n)
	{
		tmp[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < n)
	{
		s2[i] = tmp[i];
		i++;
	}
	free(tmp);
	return (s2);
}
