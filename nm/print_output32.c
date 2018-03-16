/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_output32.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 14:58:13 by droly             #+#    #+#             */
/*   Updated: 2018/03/16 17:15:13 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static int						compare(void const *a, void const *b)
{
	t_nm const					*pa = a;
	t_nm const					*pb = b;
	int							ret;

	ret = ft_strcmp(pa->name, pb->name);
	if (ret == 0)
	{
		if (pa->value > pb->value)
		{
			return (1);
		}
		if (pa->value == pb->value)
		{
			return (0);
		}
		if (pa->value < pb->value)
		{
			return (-1);
		}
	}
	return (ret);
}

char							print_output432(struct nlist *array, \
		int i, char ret)
{
	if (array[i].n_value)
		ret = 'C';
	else
		ret = 'U';
	return (ret);
}

char							print_output232(char *ptr, struct nlist *array,
		int i, struct s_stru *stru)
{
	char						ret;

	ret = '?';
//	printf("sexname4 : %s, array[i].nest - 1 : %d, i[1] = %d\n", stru->secname[26], array[i].n_sect - 1, stru->i[1]);
	if ((array[i].n_type & N_TYPE) == N_UNDF)
		ret = print_output432(array, i, ret);
	else if ((array[i].n_type & N_TYPE) == N_ABS)
		ret = 'A';
	else if ((array[i].n_type & N_TYPE) == N_PBUD)
		ret = 'U';
	else if ((array[i].n_type & N_TYPE) == N_SECT)
		ret = secto(array[i].n_sect, stru->secname, stru);
	else if ((array[i].n_type & N_TYPE) == N_INDR)
		ret = 'I';
	if ((array[i].n_type & N_STAB) != 0)
		ret = 'Z';
	if ((array[i].n_type & N_EXT) == 0 && ret != '?')
		ret += 32;
	stru->nm[i].name = stru->stringtable + array[i].n_un.n_strx;
	stru->nm[i].type = ret;
	stru->nm[i].value = array[i].n_value;
	if (checkcorrupt(ptr + stru->sizefile, stru->nm[i].name, stru) == 0 || stru->check[0] == 1)
	{
		printf("mdreor\n");
		return (0);
	}
	return (ret);
}

void							print_output332(struct s_stru *stru, int i)
{
	if (stru->nm[i].type != 'u' && stru->nm[i].type != 'U' &&
	stru->nm[i].type != 'z' && stru->nm[i].type != 'Z')
		ft_printf("%08x %c %s\n", stru->nm[i].value, stru->nm[i].type, \
		stru->nm[i].name);
	else if (stru->nm[i].type != 'z' && stru->nm[i].type != 'Z')
		ft_printf("         %c %s\n", stru->nm[i].type,
				stru->nm[i].name);
}

void							print_output32(struct s_stru *stru, \
		char *ptr)
{
	unsigned int				i;
	struct nlist				*array;
	char						ret;
	struct segment_command	*seg;

	seg = (struct segment_command*)stru->lc;
	stru->sec32 = (struct section*)(seg + sizeof(seg) / sizeof(void*));
	array = (void *)ptr + stru->sym->symoff;
	stru->stringtable = (void *)ptr + stru->sym->stroff;
	i = -1;
	stru->nm = (t_nm*)malloc(sizeof(t_nm) * stru->sym->nsyms);
	if (checkcorrupt(ptr + stru->sizefile, stru->sec32, stru) == 0 || \
	checkcorrupt(ptr + stru->sizefile, array, stru) == 0 || checkcorrupt(ptr + \
	stru->sizefile, stru->stringtable, stru) == 0)
	{
		printf("wsherror\n");
		return ;
	}
	while (++i < stru->sym->nsyms)
	{
//		printf("sexname3 : %s\n", stru->secname[26]);
		ret = print_output232(ptr, array, i, stru);
		if (stru->check[0] == 1)
			return ;
	}
	ft_qsort(stru->nm, stru->sym->nsyms, sizeof(t_nm), compare);
	i = -1;
	while (++i < stru->sym->nsyms)
		print_output332(stru, i);
}
