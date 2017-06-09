/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/07 13:47:04 by droly             #+#    #+#             */
/*   Updated: 2016/02/01 16:19:02 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_strlen_num(int num)
{
	int				div;
	unsigned int	i;

	div = 10;
	i = 1;
	while (num / div)
	{
		div *= 10;
		i += 1;
	}
	return (i);
}

static char			*ft_num_in_str(unsigned long div, int n, char *str)
{
	int				i;

	i = 0;
	while (n / div)
		div *= 10;
	div /= 10;
	while (div > 1)
	{
		str[i] = (((n / div) % 10) + '0');
		i += 1;
		div /= 10;
	}
	str[i] = ((n % 10) + '0');
	return (str);
}

static char			*ft_exeption(int n)
{
	char			*str;

	if (n == -2147483648)
	{
		if ((str = (char *)malloc(sizeof(char) * ft_strlen("-2147483648"))))
			return (ft_strcpy(str, "-2147483648"));
		else
			return (NULL);
	}
	if (n == 2147483647)
	{
		if ((str = (char *)malloc(sizeof(char) * ft_strlen("2147483647"))))
			return (ft_strcpy(str, "2147483647"));
		else
			return (NULL);
	}
	return (NULL);
}

char				*ft_itoa(int n)
{
	char			*str;
	unsigned int	i;

	if ((str = ft_exeption(n)))
		return (str);
	if (n < 0)
	{
		n *= -1;
		i = 1 + ft_strlen_num(n);
	}
	else
		i = ft_strlen_num(n);
	if (!(str = (char *)malloc(sizeof(char) * (1 + i))))
		return (NULL);
	str[i] = '\0';
	if (ft_strlen_num(n) < i)
	{
		str[0] = '-';
		i = 1;
	}
	else
		i = 0;
	return (ft_num_in_str(10, n, str + i) - i);
}
