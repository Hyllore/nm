/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/29 14:42:25 by droly             #+#    #+#             */
/*   Updated: 2016/04/29 15:45:21 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*put_in_maj(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] >= 'a' && str[i] <= 'z')
			str[i] -= 32;
		i++;
	}
	return (str);
}

char	*take_type1(t_printf *lst, t_flags *lst2, char *str, va_list argptr)
{
	str = special(str, argptr, lst);
	if ((str[0] == '0' && str[1] == '\0' && ft_strchr("diuxXoO", lst->type)
				!= NULL && lst->precision == 0 && lst2->diese != 1) ||
			(ft_strchr("oOdD", lst->type) != NULL && lst->precision == -2 &&
			lst2->diese != 1 && str[0] == '0' && str[1] == '\0'))
		str[0] = '\0';
	if (str[0] == '0' && str[1] == '\0' && lst2->diese == 1 &&
			(lst->precision == -1 || lst->precision == -2))
	{
		if (ft_strchr("xX", lst->type) != NULL && lst->precision == -2)
			str[0] = '\0';
		lst2->diese = 0;
	}
	if (lst2->diese == 1 && lst->precision > 0 &&
			ft_strchr("xX", lst->type) == NULL)
		lst->precision--;
	if (lst->precision == -2 && ft_strchr("xXdDiuU", lst->type) != NULL &&
			str[0] == '0' && str[1] == '\0')
		str[0] = '\0';
	return (str);
}

char	*take_type2(t_printf *lst, char *str, va_list argptr)
{
	if ((ft_strchr("s", lst->type)) != NULL)
		str = va_arg(argptr, char*);
	if ((ft_strchr("s", lst->type)) != NULL && str == NULL)
		str = "(null)";
	if (lst->precision == -2)
		str = "\0";
	if ((ft_strchr("c", lst->type)) != NULL)
	{
		if (lst->field == -1)
			str = (char*)malloc(sizeof(char) * 2);
		if (lst->field != -1)
			str = (char*)malloc(sizeof(char) * (lst->field) - 1);
		str[0] = (char)va_arg(argptr, int);
		str[1] = '\0';
		if (str[0] == 0)
		{
			lst->field--;
			lst->i2++;
		}
	}
	if (lst->type == 'p')
		str = ft_strjoin("0x", ft_itoa_base_ull((unsigned long long)
					va_arg(argptr, void*), 16));
	return (str);
}
