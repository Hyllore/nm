/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_modif.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/17 14:03:51 by droly             #+#    #+#             */
/*   Updated: 2016/04/29 15:46:15 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char		*special(char *str, va_list argptr, t_printf *lst)
{
	if ((ft_strchr("di", lst->type)) != NULL)
		str = ft_itoa(va_arg(argptr, int));
	if ((ft_strchr("D", lst->type)) != NULL)
		str = ft_utoa(va_arg(argptr, long));
	if ((ft_strchr("x", lst->type)) != NULL)
		str = ft_itoa_base((int)va_arg(argptr, unsigned int), 16);
	if ((ft_strchr("X", lst->type)) != NULL)
		str = put_in_maj(ft_itoa_base((int)va_arg(argptr, unsigned int), 16));
	if ((ft_strchr("oO", lst->type)) != NULL)
		str = ft_itoa_base((int)va_arg(argptr, unsigned int), 8);
	if ((ft_strchr("uU", lst->type)) != NULL)
		str = ft_utoa(va_arg(argptr, unsigned int));
	return (str);
}

t_printf	add_bonus(const char *format, t_printf *lst)
{
	if (format[lst->i] == '-')
		lst->type = '-';
	else if (format[lst->i] == '0' && lst->field == -1)
		lst->precision = 1;
	else if (format[lst->i] == '.')
	{
		while (format[lst->i + 1] != '%')
			lst->i++;
	}
	else if (format[lst->i] >= '0' && format[lst->i] <= '9')
	{
		lst->field = ft_atoi((char*)&format[lst->i]);
		while (format[lst->i + 1] != '%')
			lst->i++;
	}
	return (*lst);
}

char		*len_modif_d_i(t_printf *lst, char *str, va_list argptr)
{
	long long i;

	i = 0;
	if (ft_strchr("hj", lst->len_modif[0]))
		str = len_modif_h_j(lst, str, argptr, i);
	if (ft_strchr("lz", lst->len_modif[0]))
		str = len_modif_l_z(lst, str, argptr, i);
	return (str);
}

static char	*apply_types2(t_printf *lst, char *str, t_flags *lst2)
{
	long long i;

	i = ft_atoi(str);
	if ((ft_strchr("x", lst->type)) != NULL)
		str = ft_itoa_base(i, 16);
	if (lst2->diese == 1 && ft_strchr("xX", lst->type) != NULL)
		lst->field -= 2;
	if ((ft_strchr("X", lst->type)) != NULL)
	{
		str = ft_itoa_base(i, 16);
		str = put_in_maj(str);
	}
	if ((ft_strchr("oO", lst->type)) != NULL)
	{
		if (lst2->diese == 1)
			lst->field -= 1;
		str = ft_itoa_base(i, 8);
	}
	if ((ft_strchr("uU", lst->type)) != NULL)
		str = ft_utoa(i);
	if (str[0] == '0' && str[1] == '\0' && ft_strchr("uU", lst->type) != NULL
			&& lst->precision == 0)
		str[0] = '\0';
	return (str);
}

char		*len_modif_o_u(t_printf *lst, char *str, va_list argptr,
		t_flags *lst2)
{
	long long i;

	i = 0;
	if (ft_strchr("hj", lst->len_modif[0]))
		str = len_modif_h_j2(lst, str, argptr, i);
	if (ft_strchr("lz", lst->len_modif[0]))
		str = len_modif_l_z2(lst, str, argptr, i);
	if (ft_strchr("uU", lst->type) != NULL)
		str = apply_types2(lst, str, lst2);
	if (ft_strchr("oO", lst->type) != NULL && lst->len_modif[1] == 'h')
		str = apply_types2(lst, str, lst2);
	else if (ft_strchr("xX", lst->type) != NULL)
	{
		str = ft_itoa_base_ull(ft_utoi(str), 16);
		if (ft_strchr("X", lst->type) != NULL)
			str = put_in_maj(str);
	}
	return (str);
}
