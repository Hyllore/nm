/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 16:19:15 by droly             #+#    #+#             */
/*   Updated: 2018/03/22 16:43:39 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

void	nm2(struct s_stru *stru, void *ptr, int sizefile)
{
	struinit(stru, sizefile, ptr);
	if ((unsigned int)stru->magic_number == FAT_CIGAM)
	{
		stru->fat_header = (struct fat_header *)ptr;
		stru->nbarch = reversebytes32(stru->fat_header->nfat_arch);
		while (stru->i[3] < (unsigned int)stru->nbarch)
		{
			stru->fat_arch = ((void*)stru->tmpptr + sizeof(struct fat_header) +
					(sizeof(struct fat_arch) * stru->i[3]));
			if (reversebytes32(stru->fat_arch->cputype) == CPU_TYPE_X86_64)
			{
				stru->nbarch = stru->i[3] + 1;
				break ;
			}
			stru->i[3]++;
		}
	}
	if (stru->i[3] >= (unsigned int)stru->nbarch)
	{
		stru->i[3] = 0;
		stru->check[1] = 1;
	}
}

char	*nm3(struct s_stru *stru, void *ptr, char *name)
{
	stru->magic_number = *(int *)stru->tmpptr;
	if ((unsigned int)stru->magic_number == FAT_CIGAM ||
			(unsigned int)stru->magic_number == FAT_MAGIC)
	{
		stru->fat_header = (struct fat_header *)ptr;
		stru->fat_arch = ((void*)stru->tmpptr + sizeof(struct fat_header) +
				(sizeof(struct fat_arch) * stru->i[3]));
		if (stru->check[1] == 1)
		{
			ft_printf("\n%s (for architecture ", name);
			if (reversebytes32(stru->fat_arch->cputype) == CPU_TYPE_POWERPC)
				ft_printf("ppc):\n");
			if (reversebytes32(stru->fat_arch->cputype) == CPU_TYPE_I386)
				ft_printf("i386):\n");
		}
		stru->sizepart = reversebytes32(stru->fat_arch->size);
		if ((unsigned int)stru->magic_number == FAT_CIGAM)
			stru->offset = reversebytes32(stru->fat_arch->offset);
		else if ((unsigned int)stru->magic_number == FAT_MAGIC)
			stru->offset = stru->fat_arch->offset;
		stru->magic_number = *(int *)(stru->tmpptr + stru->offset);
		ptr = stru->tmpptr + stru->offset;
	}
	return (ptr);
}

int		nm4(struct s_stru *stru, void *ptr, char *name)
{
	ft_printf("%s:", name);
	if ((unsigned int)stru->magic_number == MH_MAGIC_64)
	{
		stru->header = (struct mach_header_64 *)ptr;
		stru->lc = (void *)ptr + sizeof(*stru->header);
		stru->seg = (struct segment_command_64*)stru->lc;
		if (checkcorrupt(ptr + stru->sizefile, stru->lc, stru) == 0)
			return (0);
		handle_64(ptr, stru);
	}
	if ((unsigned int)stru->magic_number == MH_CIGAM_64)
	{
		ft_printf("cigam64\n");
		stru->header = (struct mach_header_64 *)ptr;
		stru->lc = (void *)ptr + sizeof(*stru->header);
		stru->seg = (struct segment_command_64*)stru->lc;
		if (checkcorrupt(ptr + stru->sizefile, stru->lc, stru) == 0)
			return (0);
	}
	return (1);
}

int		nm5(struct s_stru *stru, void *ptr)
{
	if ((unsigned int)stru->magic_number == MH_MAGIC)
	{
		stru->header32 = (struct mach_header *)ptr;
		stru->lc = (void *)ptr + sizeof(*stru->header32);
		stru->seg32 = (struct segment_command*)stru->lc;
		if (checkcorrupt(ptr + stru->sizefile, stru->lc, stru) == 0)
			return (0);
		handle_32(ptr, stru);
	}
	if ((unsigned int)stru->magic_number == MH_CIGAM)
	{
		stru->header32 = (struct mach_header *)ptr;
		stru->lc = (void *)ptr + sizeof(*stru->header32);
		stru->seg32 = (struct segment_command*)stru->lc;
		if (checkcorrupt(ptr + stru->sizefile, stru->lc, stru) == 0)
			return (0);
		handle_32_reverse(ptr, stru);
	}
	return (1);
}

int		nm6(struct s_stru *stru, void *ptr, char *name)
{
	stru->info = ft_strsplit(ptr + SARMAG, ' ');
	stru->ar = (void*)ptr + SARMAG + sizeof(struct ar_hdr) +
		ft_atoi(stru->info[5]);
	stru->info = ft_strsplit((void*)stru->ar, ' ');
	if (stru->sizepart)
	{
		stru->sizefile = stru->sizepart;
	}
	while (checkcorrupt(ptr + stru->sizefile, (void*)stru->ar +
		sizeof(struct ar_hdr) + ft_atoi(stru->info[5]) - 1, stru) != 0)
	{
		ft_printf("\n%s(%s):\n", name, ft_strsub(stru->info[6], 2,
					ft_strlen(stru->info[6])));
		nm((void*)stru->ar + sizeof(struct ar_hdr) +
	ft_atoi(ft_strsub(stru->ar->ar_name, 3, ft_strlen(stru->ar->ar_name))),
	ft_atoi(stru->info[5]), name);
		if (checkcorrupt(ptr + stru->sizefile, (void*)stru->ar +
			sizeof(struct ar_hdr) + ft_atoi(stru->info[5]), stru) != 0)
			stru->ar = (void*)stru->ar + sizeof(struct ar_hdr) +
				ft_atoi(stru->info[5]);
		else
			return (1);
		stru->info = ft_strsplit((void*)stru->ar, ' ');
	}
	return (2);
}
