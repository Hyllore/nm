/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 11:18:12 by droly             #+#    #+#             */
/*   Updated: 2018/03/21 10:05:24 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

char				secto(unsigned int n_sect, char **secname,
		struct s_stru *stru)
{
	if (n_sect - 1 > stru->i[1] - 1)
	{
		stru->check[0] = 1;
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
		stru->check[0] = 1;
		return (0);
	}
	return (1);
}

int					nm(char *ptr, off_t sizefile, char *name, int count)
{
	struct s_stru	*stru;

	stru = (t_stru*)malloc(sizeof(t_stru));
	nm2(stru, ptr, sizefile);
	while (stru->i[3] < (unsigned int)stru->nbarch)
	{
		ptr = nm3(stru, ptr, name);
		if (nm4(stru, ptr, count, name) == 0 || nm5(stru, ptr)
				== 0)
			return (0);
		if ((unsigned int)stru->magic_number == 0x72613c21)
		{
			if (nm6(stru, ptr, name) == 1)
				return (1);
		}
		if (stru->check[0] == 1)
			return (0);
		stru->i[3]++;
	}
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
		return (-2);
	}
	return (fd);
}

int					main(int ac, char **av)
{
	int				fd;
	char			*ptr;
	struct stat		buf;
	int				i;

	fd = 0;
	i = 0;
	while (++i < ac)
	{
		if ((fd = check_error(ac, av, fd, i)) == -1)
			return (0);
		if (fstat(fd, &buf) < 0 && fd > -2)
			return (exitstr("Error fstat\n", 2));
		if (fd > -2 && (ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE,
						fd, 0)) == MAP_FAILED)
			return (exitstr("Error fstat\n", 2));
		if (fd > -2 && nm(ptr, buf.st_size, av[i], ac) == 0)
			return (exitstr("Error file corrupted\n", 2));
		if (fd > -2 && munmap(ptr, buf.st_size) < 0)
			return (exitstr("Error munmap\n", 2));
		if (ac == 1)
			ac++;
	}
}
