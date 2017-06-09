/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/02 15:47:07 by droly             #+#    #+#             */
/*   Updated: 2015/12/03 17:58:14 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	int i;
	int end;

	i = 0;
	end = 0;
	if (s == NULL)
		return (NULL);
	if (s[0] != ' ' && s[0] != '\t' && s[0] != '\n')
	{
		while (s[i] != '\0')
			i++;
		if (s[i - 1] != ' ' && s[i - 1] != '\t' && s[i - 1] != '\n')
			return (ft_strsub(s, end, i));
		i = 0;
	}
	while (s[end] != '\0')
		end++;
	while (s[end - 1] == ' ' || s[end - 1] == '\t' || s[end - 1] == '\n')
		end--;
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
		i++;
	if (i > end)
		return (ft_strsub(s, end, end));
	end = end - i;
	return (ft_strsub(s, i, end));
}
