/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 20:18:33 by droly             #+#    #+#             */
/*   Updated: 2015/12/07 20:14:34 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_count1(char const *s, int i, char c, int tmp)
{
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] == '\0')
			return (tmp);
		if (s[i] != c)
		{
			while (s[i] != c && s[i] != '\0')
				i++;
			tmp++;
		}
	}
	return (tmp);
}

static char		**ft_count2(const char *s, int tmp2, char c, char **tab)
{
	int			i;
	int			i2;

	i = 0;
	i2 = 0;
	while (s[i2] != '\0')
	{
		while (s[i2] == c)
			i2++;
		if (s[i2] != c)
		{
			i = 0;
			while (s[i2] != c && s[i2] != '\0')
			{
				i++;
				i2++;
			}
			if ((tab[tmp2] = (char*)malloc(sizeof(char) * (i + 1))) == NULL)
				return (NULL);
			tmp2++;
		}
	}
	return (tab);
}

static char		**ft_treat(char **tab, int i2, char *s, char c)
{
	int			tmp2;
	int			i;

	i = 0;
	tmp2 = 0;
	while (s[i2] != '\0')
	{
		while (s[i2] == c)
			i2++;
		if (s[i2] != c && s[i2] != '\0')
		{
			i = 0;
			while (s[i2] != c && s[i2] != '\0')
			{
				tab[tmp2][i] = s[i2];
				i++;
				i2++;
			}
			tab[tmp2][i] = '\0';
			tmp2++;
		}
	}
	tab[tmp2] = NULL;
	return (tab);
}

static char		**ft_exeption(char **tab, int p, char const *s, char c)
{
	int			v;

	v = 0;
	if ((tab = (char**)malloc(sizeof(char*) + 1)) == NULL)
		return (NULL);
	if ((tab[0] = (char*)malloc(sizeof(char) * p)) == NULL)
		return (NULL);
	p = 0;
	while (s[p] == c)
		p++;
	while (s[p] != '\0' && s[p] != c)
	{
		tab[0][v] = s[p];
		p++;
		v++;
	}
	tab[0][p] = '\0';
	tab[1] = NULL;
	return (tab);
}

char			**ft_strsplit(char const *s, char c)
{
	char		**tab;
	int			v;
	int			p;

	v = 0;
	p = 0;
	tab = NULL;
	if (!s)
		return (NULL);
	if (ft_count1(s, 0, c, 0) == 1)
	{
		while (s[v] == c)
			v++;
		while (s[v] != '\0' && s[v] != c)
		{
			v++;
			p++;
		}
		return (ft_exeption(tab, p, s, c));
	}
	if ((tab = (char**)malloc(sizeof(char*) *
					(ft_count1(s, 0, c, 0) + 1))) == NULL)
		return (NULL);
	tab = ft_count2(s, 0, c, tab);
	return (ft_treat(tab, 0, (char *)s, c));
}
