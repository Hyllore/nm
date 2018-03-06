/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 11:18:12 by droly             #+#    #+#             */
/*   Updated: 2018/03/06 17:16:00 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

char				secto(unsigned int n_sect, char **secname, struct s_stru *stru)
{
//	printf("nsect - 1 : %d\n", n_sect - 1);
//	printf("sexname : %s\n", secname[26]);
	if (n_sect - 1 > stru->i[1] - 1)
	{
		printf("corruptmdr\n");
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
		printf("corrupt\n");
		stru->check = 1;
		return (0);
	}
	return (1);
}

int					nm(char *ptr, off_t sizefile)
{
	int				magic_number;
	struct s_stru	*stru;
	uint32_t		offset;
	int i;
	int check;
	int nbarch;
	void *tmpptr;
//	uint32_t		magic;

	nbarch = 1;
	check = 0;
	i = 0;
	stru = (t_stru*)malloc(sizeof(t_stru));
	stru->check = 0;
	stru->sizefile = sizefile;
	magic_number = *(int *)ptr;
	printf("heymdr\n");
	if ((unsigned int)magic_number == FAT_CIGAM)
	{
		stru->fat_header = (struct fat_header *)ptr;
//		if (//add si architecture diff || si diff de 64 bits)
		nbarch = reversebytes32(stru->fat_header->nfat_arch);
	}
	printf("nb arch %d, magic_number : %d\n", nbarch, magic_number);
	tmpptr = ptr;
	while (i < nbarch)
	{
		magic_number = *(int *)tmpptr;
		ft_printf("yo, %d\n", i);
		if ((unsigned int)magic_number == FAT_MAGIC)
			printf("fat magic\n");
		else if ((unsigned int)magic_number == FAT_CIGAM)
		{
			stru->fat_header = (struct fat_header *)ptr;
			stru->fat_arch = ((void*)tmpptr + sizeof(struct fat_header) + (sizeof(struct fat_arch) * i));
			offset = reversebytes32(stru->fat_arch->offset);
			printf("hehec bon : %d\n", offset);
			printf("hehec bon2 \n");
			magic_number = *(int *)(tmpptr + offset);
			ptr = tmpptr + offset;
		}
		if ((unsigned int)magic_number == MH_MAGIC_64)
		{
			stru->header = (struct mach_header_64 *)ptr;
			stru->lc = (void *)ptr + sizeof(*stru->header);
			stru->seg = (struct segment_command_64*)stru->lc;
			if (checkcorrupt(ptr + stru->sizefile, stru->lc, stru) == 0)
				return (0);
			handle_64(ptr, stru);
		}
//a editer
		if ((unsigned int)magic_number == MH_CIGAM_64)
		{
			stru->header = (struct mach_header_64 *)ptr;
			stru->lc = (void *)ptr + sizeof(*stru->header);
			stru->seg = (struct segment_command_64*)stru->lc;
			if (checkcorrupt(ptr + stru->sizefile, stru->lc, stru) == 0)
				return (0);
			handle_64_reverse(ptr, stru);
		}
		if ((unsigned int)magic_number == MH_MAGIC)
		{
			stru->header32 = (struct mach_header *)ptr;
			stru->lc = (void *)ptr + sizeof(*stru->header32);
			stru->seg32 = (struct segment_command*)stru->lc;
			if (checkcorrupt(ptr + stru->sizefile, stru->lc, stru) == 0)
				return (0);
			handle_32(ptr, stru);
		}
//a editer
		if ((unsigned int)magic_number == MH_CIGAM)
		{
			printf("wesh");
			stru->header32 = (struct mach_header *)ptr;
			stru->lc = (void *)ptr + sizeof(*stru->header32);
			stru->seg32 = (struct segment_command*)stru->lc;
			if (checkcorrupt(ptr + stru->sizefile, stru->lc, stru) == 0)
				return (0);
			handle_32_reverse(ptr, stru);
		}
		if (stru->check == 1)
			return (0);
		i++;
	}
	return (1);
}

int					check_error(int ac, char **av, int fd, int i)
{
	ft_printf("i : %d, ac : %d, name : %s\n", i, ac, av[i]);
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
	int i;

	fd = 0;
	i = 0;
	while (++i < ac)
	{
		if ((fd = check_error(ac, av, fd, i)) == -1)
			return (0);
		if (fstat(fd, &buf) < 0 && fd > -2)
			return (exitstr("Error fstat\n", 2));
		if (fd > -2 && (ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == \
				MAP_FAILED)
			return (exitstr("Error fstat\n", 2));
		if (fd > -2 && ac > 2)
			ft_printf("\n%s:\n", av[i]);
		if (fd > -2 && nm(ptr, buf.st_size) == 0)
			return (exitstr("Error file corrupted\n", 2));
		if (fd > -2 && munmap(ptr, buf.st_size) < 0)
			return (exitstr("Error munmap\n", 2));
		i++;
		if (ac == 1)
			ac++;
	}
	return (1);
}
