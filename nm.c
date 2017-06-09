/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 11:18:12 by droly             #+#    #+#             */
/*   Updated: 2017/06/08 15:09:53 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void						print_output(int nsyms, int symoff, int stroff, char *ptr)
{
	int						i;
	char					*stringtable;
	struct nlist_64 *array;

	array = (void *) ptr + symoff;
	stringtable = (void *) ptr + stroff;
	i = 0;
	while (i < nsyms)
	{
		i++;
		ft_printf ("%s\n", stringtable + array[i].n_un.n_strx);
	}
}

void						handle_64(char *ptr)
{
	int						ncmds;
	int						i;
	struct mach_header_64	*header;
	struct load_command		*lc;
	struct symtab_command	*sym;

	i = 0;
	header = (struct mach_header_64 *) ptr;
	ncmds = header->ncmds;
	lc = (void *) ptr + sizeof(*header);
	while (i < ncmds)
	{
		i++;
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *) lc;
			print_output(sym->nsyms, sym->symoff, sym->stroff, ptr);
			break ;
		}
		lc = (void *) lc + lc->cmdsize;
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
		ft_putstr_fd("Error please give one argument", 2);
		return (EXIT_FAILURE);
	}
	if ((fd = open(av[1], O_RDONLY)) < 0)
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

