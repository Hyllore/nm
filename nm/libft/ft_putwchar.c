/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putwchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/18 16:45:14 by droly             #+#    #+#             */
/*   Updated: 2016/03/03 16:59:06 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static uintmax_t	ft_tobase10(char *n, int base)
{
	int				i;
	int				conv;
	int				power;

	conv = 0;
	power = 0;
	i = ft_strlen(n);
	i--;
	while (i != -1)
	{
		if (base == 16
				&& ((n[i] >= 65 && n[i] <= 70) || (n[i] >= 97 && n[i] <= 102)))
			conv += (n[i--] - 55) * ft_power(base, power);
		else
			conv += (n[i--] - 48) * ft_power(base, power);
		power++;
	}
	return (conv);
}

static void			putwchar_print(char **split)
{
	int				i;
	int				dec;

	i = 0;
	while (split[i])
	{
		dec = ft_tobase10(split[i], 2);
		write(1, &dec, 1);
		i++;
	}
}

static char			**putwchar_fill(char *mask, char *bin)
{
	int				i;
	int				j;

	j = ft_strlen(bin);
	i = ft_strlen(mask);
	i--;
	j--;
	while (i != -1 && j != -1)
	{
		if (mask[i] == 'x')
			mask[i] = bin[j--];
		i--;
	}
	if (i != -1)
		while (i != -1)
		{
			if (mask[i] == 'x')
				mask[i] = '0';
			i--;
		}
	return (ft_strsplit(mask, ' '));
}

void				ft_putwchar(wchar_t c)
{
	char			*bin;
	char			*mask;
	char			**split;
	int				len;

	bin = ft_itoa_base(c, 2);
	len = ft_strlen(bin);
	if (len <= 7)
		ft_putchar((char)c);
	else
	{
		if (len <= 11)
			mask = ft_strdup("110xxxxx 10xxxxxx");
		else if (len <= 16)
			mask = ft_strdup("1110xxxx 10xxxxxx 10xxxxxx");
		else
			mask = ft_strdup("11110xxx 10xxxxxx 10xxxxxx 10xxxxxx");
		split = putwchar_fill(mask, bin);
		putwchar_print(split);
	}
}
