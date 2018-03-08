/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/29 12:37:22 by droly             #+#    #+#             */
/*   Updated: 2016/04/29 15:47:24 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*apply_diese(t_printf *lst, char *str)
{
	int i;

	i = 0;
	if (str[0] == ' ' && str[1] == '\0' && lst->precision == 0)
		str[0] = '\0';
	if (lst->type == 'o' || lst->type == 'O')
		str = ft_strjoin("0", str);
	while (str[i] == '0')
		i++;
	if (str[i] != '\0')
	{
		if (lst->type == 'x')
			str = ft_strjoin("0x", str);
		if (lst->type == 'X')
			str = ft_strjoin("0X", str);
	}
	return (str);
}

char	*apply_plus(char *str)
{
	if (ft_atoi(str) >= 0)
		str = ft_strjoin("+", str);
	return (str);
}

char	*apply_space(char *str)
{
	if (ft_atoi(str) >= 0)
		str = ft_strjoin(" ", str);
	return (str);
}

char	*apply_field_zero(t_printf *lst, t_flags *lst2, char *str, int i)
{
	char c[2];

	ft_bzero(c, 2);
	if (lst2->space != 1)
		i -= 1;
	if ((lst2->plus == 1 || ft_atoi(str) < 0) && lst2->space != 1)
		i += 1;
	if (lst2->zero == 1 && i < lst->field)
	{
		lst->field = ((lst->field) - i);
		if (str[0] == '-')
		{
			c[0] = str[0];
			str[0] = '0';
		}
		while (lst->field > 1)
		{
			str = ft_strjoin("0", str);
			lst->field = ((lst->field) - 1);
		}
		if (c[0] != 0)
			str = ft_strjoin(c, str);
	}
	return (str);
}

char	*apply_field_space(t_printf *lst, t_flags *lst2, char *str, int i)
{
	if (ft_strchr("dDi", lst->type) != NULL)
	{
		if (lst2->space == 1 && ft_atoi(str) >= 0)
			lst->field = ((lst->field) - 1);
	}
	if (i < lst->field && lst2->minus != 1)
	{
		lst->field = ((lst->field) - i);
		while (lst->field > 0)
		{
			str = ft_strjoin(" ", str);
			lst->field--;
		}
	}
	if (i < lst->field && lst2->minus == 1)
	{
		lst->field = ((lst->field) - i);
		while (lst->field > 0)
		{
			str = ft_strjoin(str, " ");
			lst->field = ((lst->field) - 1);
		}
	}
	return (str);
}
