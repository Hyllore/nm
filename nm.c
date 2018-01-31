/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 11:18:12 by droly             #+#    #+#             */
/*   Updated: 2018/01/31 17:11:15 by droly            ###   ########.fr       */
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

void						print_output(struct symtab_command *sym, \
		char *ptr, struct load_command *lc, char **secname)
{
	int						i;
	char					*stringtable;
	struct nlist_64			*array;
	char					ret;
	struct section_64		*sec;
	struct segment_command_64 *seg;
	struct s_nm					*nm;
	struct s_nm					*tmp;

	seg = (struct segment_command_64*)lc;
	sec = (struct section_64*)(seg + sizeof(seg) / sizeof(void*));
	array = (void *) ptr + sym->symoff;
	stringtable = (void *) ptr + sym->stroff;
	i = 0;
	nm = (t_nm*)malloc(sizeof(t_nm));
	tmp = nm;
	while (i < sym->nsyms)
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
			ft_printf("00000001%08x %c %s\n", nm->value, nm->type, nm->name);
		else
			ft_printf("                 %c %s\n", nm->type, nm->name);
		nm = nm->next;
		nm->next = NULL;
		i++;
	}
	nm = tmp;
}

void							handle_64(char *ptr, struct mach_header_64 \
		*header, struct load_command *lc, struct segment_command_64 *seg)
{
	int							nsects;
	int							ncmds;
	int							i[3];
	struct symtab_command		*sym;
	struct section_64			*sec;
	char						**secname;

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	ncmds = header->ncmds;
	nsects = seg->nsects;
	i[2] = nsects;
	while (i[0] < ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64)
		{
			seg = (struct segment_command_64*)lc;
			nsects += seg->nsects;
		}
		lc = (void *) lc + lc->cmdsize;
		i[0]++;
	}
	i[0] = 0;
	i[2] = 0;
	lc = (void *) ptr + sizeof(*header);
	secname = (char **)malloc(sizeof(char*)*nsects);
	seg = (struct segment_command_64*)lc;
	while (i[0] < ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64)
		{
			seg = (struct segment_command_64*)lc;
			sec = (struct section_64*)(seg + sizeof(seg) / sizeof(void*));
			while (i[2] < seg->nsects)
			{
				secname[i[1]] = sec->sectname;
				sec = (struct section_64 *)(((void*)sec) + sizeof(struct section_64));
				i[1]++;
				i[2]++;
			}
			i[2] = 0;
		}
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *) lc;
			print_output(sym, ptr, lc, secname);
			break ;
		}
		lc = (void *) lc + lc->cmdsize;
		i[0]++;
	}
}

void							nm(char *ptr)
{
	int							magic_number;
	struct mach_header_64		*header;
	struct load_command			*lc;
	struct segment_command_64	*seg;

	header = (struct mach_header_64 *) ptr;
	lc = (void *) ptr + sizeof(*header);
	seg = (struct segment_command_64*)lc;
	magic_number = *(int *) ptr;
	if ((unsigned int)magic_number == MH_MAGIC_64)
		handle_64(ptr, header, lc, seg);
}

int								check_error(int ac, char **av, int fd,
		struct stat buf)
{
	if (ac != 2)
	{
		if ((fd = open("a.out", O_RDONLY)) < 0)
		{
			ft_putstr_fd( \
	"Error please give one argument or put an \"a.out\" in the repository", 2);
			return (-1);
		}
	}
	else if ((fd = open(av[1], O_RDONLY)) < 0)
	{
		ft_putstr_fd("Error open", 2);
		return (-1);
	}
	if (fstat(fd, &buf) < 0)
	{
		ft_putstr_fd("Error fstat", 2);
		return (-1);
	}
	return (fd);
}

int								main(int ac, char **av)
{
	int							fd;
	char						*ptr;
	struct stat					buf;

	if ((fd = check_error(ac, av, fd, buf)) == -1)
		return(0);
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == \
			MAP_FAILED)
	{
		ft_putstr_fd("Error mmap", 2);
		return (0);
	}
	nm(ptr);
	if (munmap(ptr, buf.st_size) < 0)
	{
		ft_putstr_fd("Error munmap", 2);
		return (0);
	}
	return (1);
}

