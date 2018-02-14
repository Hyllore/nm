/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 11:18:12 by droly             #+#    #+#             */
/*   Updated: 2018/02/14 12:15:38 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

//32, 64, little et big endian, Fat binaries et archives

void							ft_swap(void *a, void *b, size_t size)
{
	void						*tmp;

	tmp = (void*)malloc(size);
	ft_memcpy(tmp, a, size);
	ft_memcpy(a, b, size);
	ft_memcpy(b, tmp, size);
}

void							ft_qsort(void *base, size_t nmemb, size_t size,
		int (*compar)(const void *, const void *))
{
	void						*pivot;
	int							i;
	int							j;

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

char							secto(unsigned int n_sect, char **secname)
{
	if (!ft_strcmp(secname[n_sect - 1], SECT_DATA))
		return ('D');
	else if (!ft_strcmp(secname[n_sect - 1], SECT_BSS))
		return ('B');
	else if (!ft_strcmp(secname[n_sect - 1], SECT_TEXT))
		return ('T');
	return ('S');
}

int								checkcorrupt(char *tmp, void *ptr, \
		struct s_stru *stru)
{
	if (ptr >= (void*)tmp)
	{
		stru->check = 1;
		return (0);
	}
	return (1);
}

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

int								handle_64s3(struct s_stru *stru, char *ptr)
{
	stru->secname[stru->i[1]] = stru->sec->sectname;
	stru->sec = (struct section_64 *)(((void*)stru->sec) + \
		sizeof(struct section_64));
	if (checkcorrupt(ptr + stru->sizefile, stru->sec, stru) == 0)
		return (0);
	stru->i[1]++;
	stru->i[2]++;
	return (1);
}

int								handle_64s2(struct s_stru *stru, struct \
		segment_command_64 *seg, int nsects, char *ptr)
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

int								handle_64s(struct s_stru *stru, struct \
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
		return (0);
	stru->i[0]++;
	return (1);
}

int								initstru(struct s_stru *stru)
{
	int							nsects;

	stru->lc = stru->lc;
	stru->i[0] = 0;
	stru->i[1] = 0;
	stru->i[2] = 0;
	stru->check2 = 1;
	nsects = stru->seg->nsects;
	stru->i[2] = nsects;
	return (nsects);
}

void							handle_64(char *ptr, struct s_stru *stru)
{
	int							nsects;

	nsects = initstru(stru);
	while (stru->i[0] < stru->header->ncmds)
	{
		nsects = handle_64s2(stru, stru->seg, nsects, ptr);
		if (stru->check == 1)
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
		if (handle_64s(stru, stru->seg, ptr) == 0)
			break ;
		if (stru->check == 1)
			return ;
	}
	if (stru->check2 == 1)
		stru->check = 1;
}

int								nm(char *ptr, off_t sizefile)
{
	int							magic_number;
	struct s_stru				*stru;

	stru = (t_stru*)malloc(sizeof(t_stru));
	stru->check = 0;
	stru->header = (struct mach_header_64 *)ptr;
	stru->lc = (void *)ptr + sizeof(*stru->header);
	stru->seg = (struct segment_command_64*)stru->lc;
	stru->sizefile = sizefile;
	magic_number = *(int *)ptr;
	if (checkcorrupt(ptr + stru->sizefile, stru->lc, stru) == 0)
		return (0);
	if ((unsigned int)magic_number == MH_MAGIC_64)
		handle_64(ptr, stru);
	if (stru->check == 1)
		return (0);
	return (1);
}

int								check_error(int ac, char **av, int fd)
{
	if (ac != 2)
	{
		if ((fd = open("a.out", O_RDONLY)) < 0)
		{
			ft_putstr_fd(\
"Error please give one argument or put an \"a.out\" in the repository\n", 2);
			return (-1);
		}
	}
	else if ((fd = open(av[1], O_RDONLY)) < 0)
	{
		ft_putstr_fd("Error open\n", 2);
		return (-1);
	}
	return (fd);
}

int								exitstr(char *str, int error)
{
	ft_putstr_fd(str, error);
	return (0);
}

int								main(int ac, char **av)
{
	int							fd;
	char						*ptr;
	struct stat					buf;

	fd = 0;
	if ((fd = check_error(ac, av, fd)) == -1)
		return (0);
	if (fstat(fd, &buf) < 0)
		return (exitstr("Error fstat\n", 2));
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == \
			MAP_FAILED)
		return (exitstr("Error fstat\n", 2));
	if (nm(ptr, buf.st_size) == 0)
		return (exitstr("Error file corrupted\n", 2));
	if (munmap(ptr, buf.st_size) < 0)
		return (exitstr("Error munmap\n", 2));
	return (1);
}
