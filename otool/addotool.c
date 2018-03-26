/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addotool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 11:35:11 by droly             #+#    #+#             */
/*   Updated: 2018/03/26 13:04:23 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

void		normal32(struct s_stru *stru, char *ptr, int i)
{
	if (i % 16 == 0 && stru->obj == 0 && stru->header->filetype ==
		MH_DYLIB)
		ft_printf("\n%08x\t", ((char)ptr + i +
				stru->sec32->offset) + 4096);
	else if (i % 16 == 0 && stru->obj == 0)
		ft_printf("\n%08x\t",16 * (i / 16 ));
	else if (i % 16 == 0 && stru->obj == 1)
		ft_printf("\n%08x\t", ((char)ptr + i +
				stru->sec32->offset) + 4096);
	ft_printf("%02x ", *(unsigned char*)(ptr + i + stru->sec32->offset));
}

void		reverse32(struct s_stru *stru, char *ptr, int i)
{
	if (i % 16 == 0 && stru->obj == 0 &&
			reversebytes32(stru->header32->filetype) == MH_DYLIB)
		ft_printf("\n%08x\t", ((char)ptr + i +
				reversebytes32(stru->sec32->offset)) + 4096);
	else if (i % 16 == 0 && stru->obj == 0)
		ft_printf("\n%08x\t",16 * (i / 16 ));
	else if (i % 16 == 0 && stru->obj == 1)
		ft_printf("\n%08x\t", ((char)ptr + i +
				reversebytes32(stru->sec32->offset)) + 4096);
	ft_printf("%02x", *(unsigned char*)(ptr + i +
				reversebytes32(stru->sec32->offset)));
	if ((i + 1) % 4 == 0)
		ft_printf(" ");
}

void		normal64(struct s_stru *stru, char *ptr, int i)
{
	if (i % 16 == 0 && stru->obj == 0 && stru->header->filetype ==
		MH_DYLIB)
		ft_printf("\n0000000%d%08x\t", stru->obj, (char)ptr + i +
				stru->sec->offset);
	else if (i % 16 == 0 && stru->obj == 0)
		ft_printf("\n0000000%d%08x\t", stru->obj, 16 * (i / 16 ));
	else if (i % 16 == 0 && stru->obj == 1)
		ft_printf("\n0000000%d%08x\t", stru->obj, (char)ptr + i +
				stru->sec->offset);
	ft_printf("%02x ", *(unsigned char*)(ptr + i + stru->sec->offset));
}

void		reverse64(struct s_stru *stru, char *ptr, int i)
{
	if (i % 16 == 0 && stru->obj == 0 && stru->header->filetype ==
		MH_DYLIB)
		ft_printf("\n0000000%d%08x\t", stru->obj, (char)ptr + i +
				stru->sec->offset);
	else if (i % 16 == 0 && stru->obj == 0)
		ft_printf("\n0000000%d%08x\t", stru->obj, 16 * (i / 16 ));
	else if (i % 16 == 0 && stru->obj == 1)
		ft_printf("\n0000000%d%08x\t", stru->obj, (char)ptr + i +
				stru->sec->offset);
	ft_printf("%02x ", *(unsigned char*)(ptr + i + stru->sec->offset));
}
