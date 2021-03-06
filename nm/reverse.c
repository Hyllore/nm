/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 10:14:34 by droly             #+#    #+#             */
/*   Updated: 2018/03/21 13:24:28 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

uint16_t	reversebytes16(uint16_t nb)
{
	nb = (nb << 8) | (nb >> 8);
	return (nb);
}

uint32_t	reversebytes32(uint32_t nb)
{
	nb = ((nb & 0x000000FF) << 24 |
			(nb & 0x0000FF00) << 8 |
			(nb & 0x00FF0000) >> 8 |
			(nb & 0xFF000000) >> 24);
	return (nb);
}

uint64_t	reversebytes64(uint64_t nb)
{
	nb = ((nb & 0x00000000000000FF) << 56 |
			(nb & 0x000000000000FF00) << 40 |
			(nb & 0x0000000000FF0000) << 24 |
			(nb & 0x00000000FF000000) << 8 |
			(nb & 0x000000FF00000000) >> 8 |
			(nb & 0x0000FF0000000000) >> 24 |
			(nb & 0x00FF000000000000) >> 40 |
			(nb & 0xFF00000000000000) >> 56);
	return (nb);
}

void		struinit(struct s_stru *stru, int sizefile, void *ptr)
{
	stru->nbarch = 1;
	stru->i[3] = 0;
	stru->check[0] = 0;
	stru->sizefile = sizefile;
	stru->magic_number = *(int *)ptr;
	stru->tmpptr = ptr;
	stru->check[1] = 0;
}
