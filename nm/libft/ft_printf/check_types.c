/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/20 14:36:14 by droly             #+#    #+#             */
/*   Updated: 2016/04/29 15:47:05 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_printf		seek_len_modif_types(t_printf *lst, const char *format, int i)
{
	int			i2;

	i2 = 0;
	lst->len_modif = malloc(sizeof(char) * 2);
	while ((ft_strchr("hljz", format[i])) != NULL)
	{
		lst->len_modif[i2] = format[i];
		i++;
		i2++;
	}
	lst->len_modif[i2] = '\0';
	if ((ft_strchr("sSpdDioOuUxXcC", format[i])) != NULL)
	{
		lst->type = format[i];
		i++;
	}
	if (lst->len_modif[0] == 'l' && lst->type == 's')
		lst->type = 'S';
	if (lst->type == 'U' || lst->type == 'O' || lst->type == 'D')
	{
		lst->type = ft_tolower(lst->type);
		lst->len_modif[0] = 'l';
		lst->len_modif[1] = '\0';
	}
	return (*lst);
}

t_printf		seek_field_precision(t_printf *lst, const char *format, int i)
{
	lst->field = -1;
	lst->precision = -1;
	if (format[i] >= '0' && format[i] <= '9')
		lst->field = ft_atoi((char*)&format[i]);
	while (format[i] >= '0' && format[i] <= '9')
		i++;
	if (format[i] == '.' && format[i + 1] >= '0' && format[i + 1] <= '9')
	{
		i++;
		lst->precision = ft_atoi((char*)&format[i]);
	}
	while (format[i] >= '0' && format[i] <= '9')
		i++;
	if (format[i] == '.' && (format[i + 1] <= '0' || format[i + 1] >= '9'))
	{
		lst->precision = -2;
		i++;
	}
	return (*lst);
}

t_flags			seek_flags(t_flags *lst2, char *t)
{
	if (t[0] == '#')
		lst2->diese = 1;
	if (t[0] == '-')
		lst2->minus = 1;
	if (t[0] == '+')
		lst2->plus = 1;
	if (t[0] == ' ')
		lst2->space = 1;
	if (t[0] == '0')
		lst2->zero = 1;
	if (lst2->plus == 1 && lst2->space == 1)
		lst2->space = 0;
	if (lst2->zero == 1 && lst2->minus == 1)
		lst2->zero = 0;
	return (*lst2);
}

t_printf		write_c(t_printf *lst, va_list argptr, t_flags *lst2)
{
	char *str;

	str = NULL;
	if (lst2->minus == 1 && lst->field != -1)
	{
		*lst = countdmrd(lst, argptr);
		while (lst->field > 1)
		{
			ft_putchar(' ');
			lst->field--;
			lst->i2++;
		}
	}
	if (lst->field != -1 && lst2->minus != 1)
	{
		str = " ";
		lst->field--;
		while (lst->field > 1)
		{
			str = ft_strjoin(str, " ");
			lst->field--;
		}
		*lst = countdmrd2(lst, str, argptr);
	}
	return (*lst);
}

t_printf		seek_types(t_printf *lst, const char *format, va_list argptr,
		t_flags *lst2)
{
	char		*t;

	t = (char*)malloc(sizeof(char) * 2);
	while ((t = ft_strchr("#-+ 0", format[lst->i])) != NULL)
	{
		*lst2 = seek_flags(lst2, t);
		lst->i++;
	}
	*lst = seek_field_precision(lst, format, lst->i);
	while ((format[lst->i] >= '0' && format[lst->i] <= '9')
			|| format[lst->i] == '.')
		lst->i++;
	*lst = seek_len_modif_types(lst, format, lst->i);
	while (ft_strchr("hljzsSpdDioOuUxXcC", format[lst->i]) != NULL
				&& ft_strchr("sSpdDioOuUxXcC", format[lst->i - 1]) == NULL)
		lst->i++;
	if ((ft_strchr("C", lst->type) != NULL || (ft_strchr("c", lst->type) != NULL
				&& lst->len_modif[0] == 'l')) && lst->field != -1)
		*lst = write_c(lst, argptr, lst2);
	else if ((lst->type == 'c' && lst->len_modif[0] == 'l') || lst->type == 'S'
			|| lst->type == 'C')
		*lst = write_s(lst, argptr, lst2);
	else if (ft_strchr("spdDioOuUxXc", lst->type) != NULL)
		*lst = apply_flags(lst, lst2, argptr, NULL);
	return (*lst);
}
