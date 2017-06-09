/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 17:46:00 by droly             #+#    #+#             */
/*   Updated: 2015/12/03 19:05:24 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int i;
	int dst;
	int i2;

	if (n == 0)
		return (0);
	i2 = (int)n;
	dst = 0;
	i = 0;
	while ((s1[i] != '\0') && (s2[i] != '\0') && n > 0)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
		n--;
	}
	if (n > 0)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (0);
}
