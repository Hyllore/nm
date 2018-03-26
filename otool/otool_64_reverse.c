/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool_64_reverse.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 16:20:20 by droly             #+#    #+#             */
/*   Updated: 2018/03/26 11:54:53 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

int		handle_64s3_reverse(struct s_stru *stru, char *ptr)
{
	size_t i;

	i = -1;
	if (ft_strcmp(stru->sec->sectname, "__text") == 0)
		ft_printf("\nContents of (__TEXT,__text) section");
	while (++i < reversebytes32(stru->sec->size) &&
			ft_strcmp(stru->sec->sectname, "__text") == 0)
		reverse64(stru, ptr, i);
	if (ft_strcmp(stru->sec->sectname, "__text") == 0)
		ft_printf("\n");
	stru->secname[stru->i[1]] = stru->sec->sectname;
	stru->sec = (struct section_64 *)(((void*)stru->sec) + \
		sizeof(struct section_64));
	if (checkcorrupt(ptr + stru->sizefile, stru->sec, stru) == 0)
		return (0);
	stru->i[1]++;
	stru->i[2]++;
	return (1);
}

int		handle_64s2_reverse(struct s_stru *stru, struct segment_command_64 *seg,
		int nsects, char *ptr)
{
	if (stru->lc->cmd == LC_SEGMENT_64)
	{
		seg = (struct segment_command_64*)stru->lc;
		nsects += seg->nsects;
	}
	stru->lc = (void *)stru->lc + stru->lc->cmdsize;
	if (checkcorrupt(ptr + stru->sizefile, stru->lc, stru) == 0)
		return (nsects);
	stru->i[0]++;
	return (nsects);
}

int		handle_64s_reverse(struct s_stru *stru, struct \
		segment_command_64 *seg, char *ptr)
{
	if (stru->lc->cmd == LC_SEGMENT_64)
	{
		seg = (struct segment_command_64*)stru->lc;
		stru->sec = (struct section_64*)(seg + sizeof(seg) / sizeof(void*));
		if (checkcorrupt(ptr + stru->sizefile, stru->sec, stru) == 0)
			return (0);
		while (stru->i[2] < seg->nsects)
		{
			if (handle_64s3_reverse(stru, ptr) == 0)
				return (0);
		}
		stru->i[2] = 0;
	}
	if (stru->lc->cmd == LC_SYMTAB)
	{
		stru->check2 = 0;
		stru->sym = (struct symtab_command *)stru->lc;
		return (0);
	}
	stru->lc = (void *)stru->lc + stru->lc->cmdsize;
	if (checkcorrupt(ptr + stru->sizefile, stru->lc, stru) == 0)
		return (0);
	stru->i[0]++;
	return (1);
}

int		initstru_reverse(struct s_stru *stru)
{
	int	nsects;

	stru->lc = stru->lc;
	stru->i[0] = 0;
	stru->i[1] = 0;
	stru->i[2] = 0;
	stru->check2 = 1;
	nsects = stru->seg->nsects;
	stru->i[2] = nsects;
	if (stru->header->filetype == MH_OBJECT)
		stru->obj = 0;
	else
		stru->obj = 1;
	return (nsects);
}

void	handle_64_reverse(char *ptr, struct s_stru *stru)
{
	int	nsects;

	nsects = initstru_reverse(stru);
	while (stru->i[0] < stru->header->ncmds)
	{
		nsects = handle_64s2_reverse(stru, stru->seg, nsects, ptr);
		if (stru->check[0] == 1)
			return ;
	}
	stru->i[0] = 0;
	stru->i[2] = 0;
	stru->lc = (void *)ptr + sizeof(*stru->header);
	if (checkcorrupt(ptr + stru->sizefile, stru->lc, stru) == 0)
		return ;
	stru->secname = (char **)malloc(sizeof(char*) * nsects);
	stru->seg = (struct segment_command_64*)stru->lc;
	while (stru->i[0] < stru->header->ncmds)
	{
		if (handle_64s_reverse(stru, stru->seg, ptr) == 0)
			break ;
		if (stru->check[0] == 1)
			return ;
	}
	if (stru->check2 == 1)
		stru->check[0] = 1;
}
