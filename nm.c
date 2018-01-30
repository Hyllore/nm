/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 11:18:12 by droly             #+#    #+#             */
/*   Updated: 2018/01/30 17:14:38 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

//32, 64, little et big endian, Fat binaries et archives

//recuper array[i].n_value, .

char secto(struct section_64 *sec, unsigned int n_sect, char **secname)
{
	//	if (tmp->nb == n_sect)
	//	{
//	ft_printf("%s", sec->sectname);
//	ft_printf("%s", sec->segname);
	if (!ft_strcmp(secname[n_sect - 1], SECT_DATA))
		return ('D');
	else if (!ft_strcmp(secname[n_sect - 1], SECT_BSS))
		return ('B');
	else if (!ft_strcmp(secname[n_sect - 1], SECT_TEXT))
		return ('T');
	else
		return ('S');
	//	}
	return ('S');
}

void						print_output(int nsyms, int symoff, int stroff, char *ptr, struct load_command *lc, char **secname)
{
	int						i;
	char					*stringtable;
	struct nlist_64			*array;
	char					ret;
	struct section_64		*sec;
	struct segment_command_64 *seg;
	struct s_nm					*nm;
	struct s_nm					*tmp;
	//	char					* cmd;

	seg = (struct segment_command_64*)lc;
	sec = (struct section_64*)(seg + sizeof(seg) / sizeof(void*));
	array = (void *) ptr + symoff;
	stringtable = (void *) ptr + stroff;
	i = 0;
	nm = (t_nm*)malloc(sizeof(t_nm));
	tmp = nm;
	while (i < nsyms)
	{
		ret = '?';
		if ((array[i].n_type & N_TYPE) == N_UNDF)
		{
			if (array[i].n_value)
				ret = 'C';
			else
				ret = 'U';
		}
		else if ((array[i].n_type & N_TYPE) == N_ABS)
			ret = 'A';
		else if ((array[i].n_type & N_TYPE) == N_PBUD)
			ret = 'U';
		else if ((array[i].n_type & N_TYPE) == N_SECT)
			ret = secto(sec, array[i].n_sect, secname);
		else if ((array[i].n_type & N_TYPE) == N_INDR)
			ret = 'I';
		if ((array[i].n_type & N_STAB) != 0)
			ret = 'Z';
		if ((array[i].n_type & N_EXT) == 0 && ret != '?')
			ret += 32;
		nm->name = stringtable + array[i].n_un.n_strx;
		nm->type = ret;
		nm->value = array[i].n_value;
		nm->next = (t_nm*)malloc(sizeof(t_nm));
		if (ret != 'u' && ret != 'U')
			ft_printf("%016x %c %s\n", nm->value, nm->type, nm->name);
		else
			ft_printf("                 %c %s\n", nm->type, nm->name);
		nm = nm->next;
		nm->next = NULL;
		i++;
	}
}

void						handle_64(char *ptr)
{
	int						nsects;
	int						ncmds;
	int						i;
	struct mach_header_64	*header;
	struct load_command		*lc;
	struct symtab_command	*sym;
	struct section_64		*sec;
	struct segment_command_64 *seg;
	char					**secname;
	int i2;
	int i3;

	i2 = 0;
	i = 0;
	i3 = 0;
	header = (struct mach_header_64 *) ptr;
	lc = (void *) ptr + sizeof(*header);
	seg = (struct segment_command_64*)lc;
//	sec = (struct section_64*)(seg + sizeof(seg) / sizeof(void*));
	ncmds = header->ncmds;
	nsects = seg->nsects;
	i3 = nsects;
	while (i < ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64)
		{
			seg = (struct segment_command_64*)lc;
			nsects += seg->nsects;
		}
		lc = (void *) lc + lc->cmdsize;
		i++;
	}
	i = 0;
	i3 = 0;
	lc = (void *) ptr + sizeof(*header);
	secname = (char **)malloc(sizeof(char*)*nsects);
	seg = (struct segment_command_64*)lc;
	while (i < ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64)
		{
//			ft_printf("%d", seg->nsects);
			seg = (struct segment_command_64*)lc;
			sec = (struct section_64*)(seg + sizeof(seg) / sizeof(void*));
			while (i3 < seg->nsects)
			{
				secname[i2] = sec->sectname;
//				ft_printf("segname : %s ", seg->segname);
//				ft_printf("struct : %s char* : %s\n", sec->sectname, secname[i2]);
				sec = (struct section_64 *)(((void*)sec) + sizeof(struct section_64));
				i2++;
				i3++;
			}
			i3 = 0;
//			i2 = 0;
//			secname[i2] = sec->sectname;
//			i2++;
		}
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *) lc;
			//			ft_printf("%d\n",  ft_itoa_base(lc->cmd, 16));
			print_output(sym->nsyms, sym->symoff, sym->stroff, ptr, lc, secname);
			break ;
		}
		lc = (void *) lc + lc->cmdsize;
		i++;
	}
}

void						nm(char *ptr)
{
	int						magic_number;

	magic_number = *(int *) ptr;
	if ((unsigned int)magic_number == MH_MAGIC_64)
		handle_64(ptr);
}

int							main(int ac, char **av)
{
	int						fd;
	char					*ptr;
	struct stat				buf;

	if (ac != 2)
	{
		if ((fd = open("a.out", O_RDONLY)) < 0)
		{
			ft_putstr_fd("Error please give one argument or put an \"a.out\" in the repository", 2);
			return (EXIT_FAILURE);
		}
	}
	else if ((fd = open(av[1], O_RDONLY)) < 0)
	{
		ft_putstr_fd("Error open", 2);
		return (EXIT_FAILURE);
	}
	if (fstat(fd, &buf) < 0)
	{
		ft_putstr_fd("Error fstat", 2);
		return (EXIT_FAILURE);
	}
	if ((ptr = mmap (0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
	{
		ft_putstr_fd("Error mmap", 2);
		return (EXIT_FAILURE);
	}
	nm(ptr);
	if (munmap(ptr, buf.st_size) < 0)
	{
		ft_putstr_fd("Error munmap", 2);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

