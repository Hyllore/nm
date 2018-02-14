/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 12:18:52 by droly             #+#    #+#             */
/*   Updated: 2018/02/14 14:04:59 by droly            ###   ########.fr       */
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

char							print_output4(struct nlist_64 *array, \
		int i, char ret)
{
	if (array[i].n_value)
		ret = 'C';
	else
		ret = 'U';
	return (ret);
}

char							print_output2(char *ptr, struct nlist_64 *array,
		int i, struct s_stru *stru)
{
	char						ret;

	ret = '?';
	if ((array[i].n_type & N_TYPE) == N_UNDF)
		ret = print_output4(array, i, ret);
	else if ((array[i].n_type & N_TYPE) == N_ABS)
		ret = 'A';
	else if ((array[i].n_type & N_TYPE) == N_PBUD)
		ret = 'U';
	else if ((array[i].n_type & N_TYPE) == N_SECT)
		ret = secto(array[i].n_sect, stru->secname);
	else if ((array[i].n_type & N_TYPE) == N_INDR)
		ret = 'I';
	if ((array[i].n_type & N_STAB) != 0)
		ret = 'Z';
	if ((array[i].n_type & N_EXT) == 0 && ret != '?')
		ret += 32;
	stru->nm[i].name = stru->stringtable + array[i].n_un.n_strx;
	stru->nm[i].type = ret;
	stru->nm[i].value = array[i].n_value;
	if (checkcorrupt(ptr + stru->sizefile, stru->nm[i].name, stru) == 0)
		return (0);
	return (ret);
}

void							print_output3(struct s_stru *stru, int i)
{
	if (stru->nm[i].type != 'u' && stru->nm[i].type != 'U' &&
	stru->nm[i].type != 'z' && stru->nm[i].type != 'Z')
		ft_printf("00000001%08x %c %s\n", stru->nm[i].value, stru->nm[i].type, \
		stru->nm[i].name);
	else if (stru->nm[i].type != 'z' && stru->nm[i].type != 'Z')
		ft_printf("                 %c %s\n", stru->nm[i].type,
				stru->nm[i].name);
}

void							print_output(struct s_stru *stru, \
		char *ptr)
{
	unsigned int				i;
	struct nlist_64				*array;
	char						ret;
	struct segment_command_64	*seg;

	seg = (struct segment_command_64*)stru->lc;
	stru->sec = (struct section_64*)(seg + sizeof(seg) / sizeof(void*));
	array = (void *)ptr + stru->sym->symoff;
	stru->stringtable = (void *)ptr + stru->sym->stroff;
	i = -1;
	stru->nm = (t_nm*)malloc(sizeof(t_nm) * stru->sym->nsyms);
	if (checkcorrupt(ptr + stru->sizefile, stru->sec, stru) == 0 || \
	checkcorrupt(ptr + stru->sizefile, array, stru) == 0 || checkcorrupt(ptr + \
	stru->sizefile, stru->stringtable, stru) == 0)
		return ;
	while (++i < stru->sym->nsyms)
	{
		ret = print_output2(ptr, array, i, stru);
		if (stru->check == 1)
			return ;
	}
	ft_qsort(stru->nm, stru->sym->nsyms, sizeof(t_nm), compare);
	i = -1;
	while (++i < stru->sym->nsyms)
		print_output3(stru, i);
}
