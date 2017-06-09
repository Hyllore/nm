/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_modif.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/17 14:03:51 by droly             #+#    #+#             */
/*   Updated: 2016/04/29 15:45:49 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_printf	minus_plus(t_printf *lst)
{
	ft_putchar('%');
	lst->i2++;
	while (lst->field >= 2)
	{
		ft_putchar(' ');
		lst->i2++;
		lst->field--;
	}
	return (*lst);
}

long long	plus(long long i)
{
	if (i < 0)
		i = i * -1;
	return (i);
}

char		*db(long long i, char *str)
{
	int i2;

	i2 = 0;
	if (i < 0)
		i2 = 1;
	i = plus(i);
	str = ft_utoa(i);
	if (i2 == 1)
		str = ft_strjoin("-", str);
	return (str);
}

char		*len_modif_h_j(t_printf *lst, char *str, va_list argptr,
		long long i)
{
	if (lst->len_modif[0] == 'h' && lst->len_modif[1] == 'h')
	{
		i = (signed char)va_arg(argptr, int);
		str = db(i, str);
	}
	else if (ft_strchr("h", lst->len_modif[0]) != NULL)
	{
		i = (short)va_arg(argptr, int);
		str = db(i, str);
	}
	else if (ft_strchr("j", lst->len_modif[0]) != NULL)
	{
		i = (intmax_t)va_arg(argptr, intmax_t);
		str = db(i, str);
	}
	return (str);
}

char		*len_modif_l_z(t_printf *lst, char *str, va_list argptr,
		long long i)
{
	if (lst->len_modif[0] == 'l' && lst->len_modif[1] == 'l')
	{
		i = va_arg(argptr, long long);
		str = db(i, str);
	}
	else if (ft_strchr("l", lst->len_modif[0]) != NULL)
	{
		i = (long)va_arg(argptr, long);
		str = db(i, str);
	}
	else if (ft_strchr("z", lst->len_modif[0]) != NULL)
	{
		i = (ssize_t)va_arg(argptr, ssize_t);
		str = db(i, str);
	}
	return (str);
}
