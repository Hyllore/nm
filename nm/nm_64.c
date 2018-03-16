/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_64.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 13:43:28 by droly             #+#    #+#             */
/*   Updated: 2018/03/16 17:16:25 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int		handle_64s3(struct s_stru *stru, char *ptr)
{
	char *tmp;

	tmp  = ptr;
	tmp = ptr + stru->sec->offset + 1;
//	printf("lol\n");
//	printf("mdr : %s, hexa octet : %x\n", stru->sec->sectname, (int)*tmp);
	stru->secname[stru->i[1]] = stru->sec->sectname;
	stru->sec = (struct section_64 *)(((void*)stru->sec) + \
		sizeof(struct section_64));
	if (checkcorrupt(ptr + stru->sizefile, stru->sec, stru) == 0)
	{
		ft_printf("corrupt1\n");
		return (0);
	}
	stru->i[1]++;
	stru->i[2]++;
	return (1);
}

int		handle_64s2(struct s_stru *stru, struct segment_command_64 *seg,
		int nsects, char *ptr)
{
	if (stru->lc->cmd == LC_SEGMENT_64)
	{
//		ft_printf("nik\n");
		seg = (struct segment_command_64*)stru->lc;
		nsects += seg->nsects;
	}
	stru->lc = (void *)stru->lc + stru->lc->cmdsize;
	if (checkcorrupt(ptr + stru->sizefile, stru->lc, stru) == 0)
	{
		ft_printf("corrupt2\n");
		return (nsects);
	}
	stru->i[0]++;
	return (nsects);
}

int		handle_64s(struct s_stru *stru, struct \
		segment_command_64 *seg, char *ptr)
{
	if (stru->lc->cmd == LC_SEGMENT_64)
	{
		seg = (struct segment_command_64*)stru->lc;
		stru->sec = (struct section_64*)(seg + sizeof(seg) / sizeof(void*));
		if (checkcorrupt(ptr + stru->sizefile, stru->sec, stru) == 0)
		{
			ft_printf("corrupt3\n");
			return (0);
		}
		while (stru->i[2] < seg->nsects)
		{
			if (handle_64s3(stru, ptr) == 0)
				return (0);
		}
		stru->i[2] = 0;
	}
	if (stru->lc->cmd == LC_SYMTAB)
	{
		stru->check2 = 0;
		stru->sym = (struct symtab_command *)stru->lc;
		print_output(stru, ptr);
		return (0);
	}
	stru->lc = (void *)stru->lc + stru->lc->cmdsize;
	if (checkcorrupt(ptr + stru->sizefile, stru->lc, stru) == 0)
	{
		ft_printf("corrupt4\n");
		return (0);
	}
	stru->i[0]++;
	return (1);
}

int		initstru(struct s_stru *stru)
{
	int	nsects;

	stru->i[0] = 0;
	stru->i[1] = 0;
	stru->i[2] = 0;
	stru->check2 = 1;
	nsects = stru->seg->nsects;
	stru->i[2] = nsects;
	if (stru->header->filetype == MH_OBJECT || stru->header->filetype == MH_DYLIB)
		stru->obj = 0;
	else
		stru->obj = 1;
	return (nsects);
}

void	handle_64(char *ptr, struct s_stru *stru)
{
	int	nsects;

	nsects = initstru(stru);
//	printf("nb lc : %d\n", stru->header->ncmds);
	while (stru->i[0] < stru->header->ncmds)
	{
		nsects = handle_64s2(stru, stru->seg, nsects, ptr);
		if (stru->check[0] == 1)
			return ;
	}
	stru->i[0] = 0;
	stru->i[2] = 0;
	stru->lc = (void *)ptr + sizeof(*stru->header);
	if (checkcorrupt(ptr + stru->sizefile, stru->lc, stru) == 0)
	{
		ft_printf("corrupt5\n");
		return ;
	}
	stru->secname = (char **)malloc(sizeof(char*) * nsects);
	stru->seg = (struct segment_command_64*)stru->lc;
	while (stru->i[0] < stru->header->ncmds)
	{
		if (handle_64s(stru, stru->seg, ptr) == 0)
			break ;
		if (stru->check[0] == 1)
			return ;
	}
	if (stru->check2 == 1)
		stru->check[0] = 1;
}
