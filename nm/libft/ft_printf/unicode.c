/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putwchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/18 16:45:14 by droly             #+#    #+#             */
/*   Updated: 2016/04/29 15:45:15 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_printf			countq(t_printf *lst, wchar_t c)
{
	if (c >= 0 && c <= 127)
	{
		lst->i2 += 1;
		lst->tmp += 4;
	}
	if (c >= 128 && c <= 2047)
	{
		lst->i2 += 2;
		lst->tmp += 3;
	}
	if (c >= 2048 && c <= 65535)
	{
		lst->i2 += 3;
		lst->tmp += 2;
	}
	if (c >= 65536 && c <= 1114111)
	{
		lst->i2 += 4;
		lst->tmp += 1;
	}
	return (*lst);
}

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

static char			*putwchar_print(char **split)
{
	int				i;
	int				dec;
	char			*str;

	i = 0;
	str = malloc(sizeof(char) * 2);
	while (split[i])
	{
		dec = ft_tobase10(split[i], 2);
		str[0] = dec;
		i++;
	}
	str[1] = '\0';
	return (str);
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

char				*ft_unicode(wchar_t c)
{
	char			*bin;
	char			*mask;
	char			**split;

	bin = ft_itoa_base(c, 2);
	if (ft_strlen(bin) <= 7)
	{
		mask = malloc(sizeof(char) * 2);
		mask[0] = (char)c;
		mask[1] = '\0';
		return (mask);
	}
	else
	{
		if (ft_strlen(bin) <= 11)
			mask = ft_strdup("110xxxxx 10xxxxxx");
		else if (ft_strlen(bin) <= 16)
			mask = ft_strdup("1110xxxx 10xxxxxx 10xxxxxx");
		else
			mask = ft_strdup("11110xxx 10xxxxxx 10xxxxxx 10xxxxxx");
		split = putwchar_fill(mask, bin);
		return (putwchar_print(split));
	}
	return (NULL);
}
