/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_qsort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 13:22:02 by droly             #+#    #+#             */
/*   Updated: 2018/02/14 13:23:19 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_swap(void *a, void *b, size_t size)
{
	void	*tmp;

	tmp = (void*)malloc(size);
	ft_memcpy(tmp, a, size);
	ft_memcpy(a, b, size);
	ft_memcpy(b, tmp, size);
}

void		ft_qsort(void *base, size_t nmemb, size_t size,
		int (*compar)(const void *, const void *))
{
	void	*pivot;
	int		i;
	int		j;

	i = -1;
	j = 0;
	pivot = base + (size * (nmemb - 1));
	while ((unsigned int)j < nmemb - 1)
	{
		if (compar(base + (size * j), pivot) <= 0)
		{
			i++;
			ft_swap(base + (size * j), base + (size * i), size);
		}
		j++;
	}
	ft_swap(pivot, base + (size * (i + 1)), size);
	if (i >= 1)
		ft_qsort(base, i + 1, size, compar);
	if ((nmemb - (i + 1)) > 1)
		ft_qsort(base + (size * (i + 1)), nmemb - (i + 1), size, compar);
}
