/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 18:19:49 by droly             #+#    #+#             */
/*   Updated: 2016/03/03 16:58:32 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned long long	ft_add(int i, char *str1, long long dst)
{
	while (str1[i] != '\0' && str1[i] >= '0' && str1[i] <= '9')
	{
		dst = (dst * 10) + (str1[i] - 48);
		i++;
	}
	return (dst);
}

unsigned long long			ft_utoi(const char *str)
{
	int						i;
	unsigned long long		dst;
	char					*str1;
	int						neg;

	neg = 0;
	dst = 0;
	i = 0;
	str1 = (char*)str;
	while (str1[i] >= 9 && str1[i] <= 32)
		i++;
	if (str1[i] == '+')
	{
		i++;
		if (str1[i] == '-')
			return (0);
	}
	if (str1[i] == '-')
	{
		neg = 1;
		i++;
	}
	if (neg == 1)
		return (ft_add(i, str1, dst) * -1);
	return (ft_add(i, str1, dst));
}
