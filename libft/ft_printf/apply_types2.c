/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_types2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 18:06:14 by droly             #+#    #+#             */
/*   Updated: 2016/04/29 15:47:15 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_printf	apply_percent(t_printf *lst)
{
	if (lst->type == '-')
	{
		*lst = minus_plus(lst);
	}
	else
	{
		while (lst->field >= 2)
		{
			if (lst->precision == 1)
				ft_putchar('0');
			else
				ft_putchar(' ');
			lst->i2++;
			lst->field--;
		}
		ft_putchar('%');
		lst->i2++;
	}
	return (*lst);
}

t_printf	write_char(t_printf *lst, char *str, int i)
{
	while (str[i] != '\0')
	{
		ft_putchar(str[i]);
		i++;
		lst->i2++;
	}
	if (ft_strchr("c", lst->type) != NULL && str[i - 1] == ' ' &&
			str[i - 2] == ' ')
		ft_putchar('\0');
	return (*lst);
}

char		*apply_precision_str(t_printf *lst, char *str)
{
	int		i;
	char	*tmp;

	tmp = NULL;
	i = 0;
	if (ft_strchr("sS", lst->type) != NULL)
	{
		if (ft_strlen(str) > (size_t)lst->precision)
		{
			lst->precision = ft_strlen(str) - lst->precision;
			while (lst->precision > 0)
			{
				i = 0;
				tmp = ft_strnew(ft_strlen(str));
				ft_strcpy(tmp, str);
				str = ft_strnew(ft_strlen(tmp));
				ft_strcpy(str, tmp);
				while (str[i + 1] != '\0')
					i++;
				str[i] = '\0';
				lst->precision -= 1;
			}
		}
	}
	return (str);
}

char		*apply_precision_num(t_printf *lst, char *str, int i)
{
	char	c[2];

	ft_bzero(c, 2);
	if (str[0] == '-')
		lst->precision++;
	if (i < lst->precision)
	{
		lst->precision = ((lst->precision) - i);
		if (str[0] == '-')
		{
			c[0] = str[0];
			str[0] = '0';
			lst->precision--;
		}
		while (lst->precision > 0)
		{
			str = ft_strjoin("0", str);
			lst->precision = ((lst->precision) - 1);
		}
		if (c[0] != 0)
			str = ft_strjoin(c, str);
	}
	else if (i > lst->precision)
		str = precision_minus(str, 0, lst, c);
	return (str);
}

char		*apply_len_modif(t_printf *lst, char *str, va_list argptr,
		t_flags *lst2)
{
	if (ft_strchr("dDi", lst->type) != NULL)
		str = len_modif_d_i(lst, str, argptr);
	if (ft_strchr("oOuUxX", lst->type) != NULL)
		str = len_modif_o_u(lst, str, argptr, lst2);
	return (str);
}
