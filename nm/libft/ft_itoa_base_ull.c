/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/03 16:31:16 by droly             #+#    #+#             */
/*   Updated: 2016/03/03 17:08:39 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		aux_dix(unsigned long long n, char *ans, int *p)
{
	if (9 < n)
		aux_dix(n / 10, ans, p);
	ans[(*p)++] = n % 10;
}

static void		aux(unsigned long long n, unsigned int b, char *ans, int *p)
{
	char		*base;

	base = "0123456789abcdef";
	if (n >= b)
		aux(n / b, b, ans, p);
	ans[(*p)++] = base[n % b];
}

char			*ft_itoa_base_ull(unsigned long long value, int base)
{
	char		*ans;
	int			p;

	if (base < 2 || 16 < base
			|| !(ans = (char *)malloc(sizeof(char) * 35)))
		return (NULL);
	p = 0;
	if (base == 10)
		aux_dix(value, ans, &p);
	else
		aux(value, (unsigned int)base, ans, &p);
	ans[p] = '\0';
	return (ans);
}
