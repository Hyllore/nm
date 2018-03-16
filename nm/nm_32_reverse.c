/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_32_reverse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 15:29:39 by droly             #+#    #+#             */
/*   Updated: 2018/03/16 17:16:45 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int		handle_32s3_reverse(struct s_stru *stru, char *ptr)
{
	stru->secname[stru->i[1]] = stru->sec32->sectname;
	stru->sec32 = (struct section *)(((void*)stru->sec32) + \
		sizeof(struct section));
	if (checkcorrupt(ptr + stru->sizefile, stru->sec32, stru) == 0)
	{
		printf("error1\n");
		return (0);
	}
	stru->i[1]++;
	stru->i[2]++;
	return (1);
}

int		handle_32s2_reverse(struct s_stru *stru, struct segment_command *seg,
		int nsects, char *ptr)
{
	if (reversebytes32(stru->lc->cmd) == LC_SEGMENT)
	{
		seg = (struct segment_command*)stru->lc;
		nsects += reversebytes32(seg->nsects);
	}
	stru->lc = (void *)stru->lc + reversebytes32(stru->lc->cmdsize);
	if (checkcorrupt(ptr + stru->sizefile, stru->lc, stru) == 0)
	{
		printf("error2\n");
		return (nsects);
	}
	stru->i[0]++;
	return (nsects);
}

int		handle_32s_reverse(struct s_stru *stru, struct \
		segment_command *seg, char *ptr)
{
//	printf("hey\n");
	if (reversebytes32(stru->lc->cmd) == LC_SEGMENT)
	{
		seg = (struct segment_command*)stru->lc;
		stru->sec32 = (struct section*)(seg + sizeof(seg) / sizeof(void*));
		if (checkcorrupt(ptr + stru->sizefile, stru->sec32, stru) == 0)
		{
			printf("error3\n");
			return (0);
		}
//		printf("seg->nsect: %d\n", seg->nsects);
		while (stru->i[2] < reversebytes32(seg->nsects))
		{
			if (handle_32s3_reverse(stru, ptr) == 0)
				return (0);
		}
		stru->i[2] = 0;
	}
//	ft_printf("i : %d\n", stru->i[1]);
	if (reversebytes32(stru->lc->cmd) == LC_SYMTAB)
	{
//		printf("testmdr\n");
		stru->check2 = 0;
//		printf("testmdr2\n");
		stru->sym = (struct symtab_command *)stru->lc;
//		printf("testmdr3\n");
//		printf("sexname2 : %s\n", stru->secname[26]);
//		printf("testmdr4\n");
		print_output32_reverse(stru, ptr);
//		printf("testmdr5\n");
		return (0);
	}
	stru->lc = (void *)stru->lc + reversebytes32(stru->lc->cmdsize);
	if (checkcorrupt(ptr + stru->sizefile, stru->lc, stru) == 0)
	{
//		printf("error4\n");
		return (0);
	}
	stru->i[0]++;
	return (1);
}

int		initstru32_reverse(struct s_stru *stru)
{
	int	nsects;

	stru->lc = stru->lc;
	stru->i[0] = 0;
	stru->i[1] = 0;
	stru->i[2] = 0;
	stru->check2 = 1;
//	printf("ay8\n");
	nsects = reversebytes32(stru->seg32->nsects);
	stru->i[2] = nsects;
//	printf("ay7\n");
	if (reversebytes32(stru->header32->filetype) == MH_OBJECT)
	{
//		printf("ay11\n");
		stru->obj = 0;
	}
	else
	{
//		printf("ay10\n");
		stru->obj = 1;
	}
//	printf("ay9\n");
	return (nsects);
}

void	handle_32_reverse(char *ptr, struct s_stru *stru)
{
	int	nsects;

//	printf("ay\n");
	nsects = initstru32_reverse(stru);
	while (stru->i[0] < reversebytes32(stru->header32->ncmds))
	{
//		printf("ay2\n");
		nsects = handle_32s2_reverse(stru, stru->seg32, nsects, ptr);
		if (stru->check[0] == 1)
			return ;
	}
	stru->i[0] = 0;
	stru->i[2] = 0;
	stru->lc = (void *)ptr + sizeof(*stru->header32);
//	printf("yo\n");
//	printf("ay3\n");
	if (checkcorrupt(ptr + stru->sizefile, stru->lc, stru) == 0)
	{
//		printf("error5\n");
		return ;
	}
//	printf("ay4\n");
	stru->secname = (char **)malloc(sizeof(char*) * nsects);
	stru->seg32 = (struct segment_command*)stru->lc;
	while (stru->i[0] < reversebytes32(stru->header32->ncmds))
	{
//		printf("ay5\n");
		if (handle_32s_reverse(stru, stru->seg32, ptr) == 0)
			break ;
		if (stru->check[0] == 1)
			return ;
	}
//	printf("ay6\n");
	if (stru->check2 == 1)
		stru->check[0] = 1;
}
