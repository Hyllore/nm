/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 15:37:20 by droly             #+#    #+#             */
/*   Updated: 2016/04/29 15:47:34 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char		*precision_minus(char *str, int i2, t_printf *lst, char *c)
{
	lst->precision = ft_strlen(str) - lst->precision;
	if (str[0] == '-' && str[1] == '0')
	{
		c[0] = str[0];
		str[0] = '0';
	}
	if (str[0] == '0')
	{
		while (str[i2] == '0' && lst->precision > 0)
		{
			str[i2] = ' ';
			i2++;
			lst->precision--;
		}
		i2--;
		if (c[0] != 0)
			str[i2] = '-';
	}
	return (str);
}

static int	count(wchar_t *str)
{
	int		i;

	i = 0;
	while (*str)
	{
		ft_unicode(*str++);
		i += 3;
	}
	return (i);
}

t_printf	minus_1(t_printf *lst, va_list argptr)
{
	int		i;
	wchar_t	*str;

	i = 0;
	str = va_arg(argptr, wchar_t*);
	i = count(str);
	ft_putwstr(str);
	lst->field = lst->field - i + 1;
	lst->i2 += i;
	while (lst->field > 1)
	{
		ft_putchar(' ');
		lst->field--;
		lst->i2++;
	}
	return (*lst);
}

t_printf	minus_0(t_printf *lst, va_list argptr)
{
	int		i;
	wchar_t	*str;

	i = 0;
	str = va_arg(argptr, wchar_t*);
	i = count(str);
	lst->field = lst->field - i + 1;
	while (lst->field > 1)
	{
		ft_putchar(' ');
		lst->field--;
		lst->i2++;
	}
	ft_putwstr(str);
	lst->i2 += i;
	return (*lst);
}

t_printf	countdmrd(t_printf *lst, va_list argptr)
{
	wchar_t	str;

	str = va_arg(argptr, wchar_t);
	ft_putwchar(str);
	if (str >= 0x00 && str <= 0x7F)
		lst->i2 += 1;
	if (str >= 0x80 && str <= 0x7FF)
	{
		lst->i2 += 2;
		lst->field -= 1;
	}
	if (str >= 0x800 && str <= 0xFFFF)
	{
		lst->i2 += 3;
		lst->field -= 2;
	}
	if (str >= 0x10000 && str <= 0x10FFFF)
	{
		lst->i2 += 4;
		lst->field -= 3;
	}
	return (*lst);
}
