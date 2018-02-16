/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 11:18:12 by droly             #+#    #+#             */
/*   Updated: 2018/02/16 14:39:36 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

char				secto(unsigned int n_sect, char **secname, struct s_stru *stru)
{
//	printf("nsect - 1 : %d\n", n_sect - 1);
//	printf("sexname : %s\n", secname[26]);
	if (n_sect - 1 > stru->i[1] - 1)
	{
		stru->check = 1;
		return (0);
	}
	if (!ft_strcmp(secname[n_sect - 1], SECT_DATA))
		return ('D');
	else if (!ft_strcmp(secname[n_sect - 1], SECT_BSS))
		return ('B');
	else if (!ft_strcmp(secname[n_sect - 1], SECT_TEXT))
		return ('T');
	return ('S');
}

int					checkcorrupt(char *tmp, void *ptr, struct s_stru *stru)
{
	if (ptr >= (void*)tmp)
	{
//		printf("corrupt\n");
		stru->check = 1;
		return (0);
	}
	return (1);
}

int					nm(char *ptr, off_t sizefile)
{
	int				magic_number;
	struct s_stru	*stru;

	magic_number = *(int *)ptr;
	stru = (t_stru*)malloc(sizeof(t_stru));
	stru->check = 0;
	stru->sizefile = sizefile;
	if ((unsigned int)magic_number == MH_MAGIC_64)
	{
		stru->header = (struct mach_header_64 *)ptr;
		stru->lc = (void *)ptr + sizeof(*stru->header);
		stru->seg = (struct segment_command_64*)stru->lc;
		if (checkcorrupt(ptr + stru->sizefile, stru->lc, stru) == 0)
			return (0);
		handle_64(ptr, stru);
	}
	if ((unsigned int)magic_number == MH_MAGIC)
	{
//		ft_printf("wesh, %d\n", sizefile);
		stru->header32 = (struct mach_header *)ptr;
//		printf("way4\n");
		stru->lc = (void *)ptr + sizeof(*stru->header32);
//		printf("way3\n");
		stru->seg32 = (struct segment_command*)stru->lc;
//		printf("way2\n");
		if (checkcorrupt(ptr + stru->sizefile, stru->lc, stru) == 0)
			return (0);
//		printf("way1\n");
		handle_32(ptr, stru);
	}
	if (stru->check == 1)
		return (0);
	return (1);
}

int					check_error(int ac, char **av, int fd, int i)
{
	if (ac < 2)
	{
		if ((fd = open("a.out", O_RDONLY)) < 0)
		{
			ft_putstr_fd(\
"Error please give one argument or put an \"a.out\" in the repository\n", 2);
			return (-1);
		}
	}
	else if ((fd = open(av[i], O_RDONLY)) < 0)
	{
		ft_putstr_fd("Error open\n", 2);
		return (-1);
	}
	return (fd);
}

int					main(int ac, char **av)
{
	int				fd;
	char			*ptr;
	struct stat		buf;
	int i;

	fd = 0;
	i = 1;
	while (i < ac || ac == 1)
	{
		if ((fd = check_error(ac, av, fd, i)) == -1)
			return (0);
		if (fstat(fd, &buf) < 0)
			return (exitstr("Error fstat\n", 2));
		if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == \
				MAP_FAILED)
			return (exitstr("Error fstat\n", 2));
		if (ac > 2)
			ft_printf("\n%s:\n", av[i]);
		if (nm(ptr, buf.st_size) == 0)
			return (exitstr("Error file corrupted\n", 2));
		if (munmap(ptr, buf.st_size) < 0)
			return (exitstr("Error munmap\n", 2));
		i++;
		if (ac == 1)
			ac++;
	}
	return (1);
}
