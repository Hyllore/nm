/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 11:18:12 by droly             #+#    #+#             */
/*   Updated: 2018/03/15 17:03:33 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

char				secto(unsigned int n_sect, char **secname, struct s_stru *stru)
{
//	printf("nsect - 1 : %d\n", n_sect - 1);
//	printf("sexname : %s\n", secname[26]);
	if (n_sect - 1 > stru->i[1] - 1)
	{
//		printf("corruptmdr\n");
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
//		printf("corrupt test\n");
		stru->check = 1;
		return (0);
	}
	return (1);
}

int					nm(char *ptr, off_t sizefile, char *name, int count)
{
	int				magic_number;
	struct s_stru	*stru;
	uint32_t		offset;
	int i;
	int check;
	int nbarch;
	void *tmpptr;
	struct ranlib	*ran;
	struct ar_hdr	*ar;
	char			**info;
	int				checkmult;
//	uint32_t		magic;

	nbarch = 1;
	check = 0;
	i = 0;
	stru = (t_stru*)malloc(sizeof(t_stru));
	stru->check = 0;
	stru->sizefile = sizefile;
	magic_number = *(int *)ptr;
	tmpptr = ptr;
	checkmult = 0;
//	printf("heymdr\n");
	if ((unsigned int)magic_number == FAT_CIGAM)
	{
		stru->fat_header = (struct fat_header *)ptr;
		nbarch = reversebytes32(stru->fat_header->nfat_arch);
		while (i < nbarch)
		{
			stru->fat_arch = ((void*)tmpptr + sizeof(struct fat_header) + (sizeof(struct fat_arch) * i));
			if (reversebytes32(stru->fat_arch->cputype) == CPU_TYPE_X86_64)
			{
//				printf("64 bittttt : %u\n", stru->fat_arch->offset);
				nbarch = i + 1;
				break;
			}
			i++;
		}
	}
	if (i >= nbarch)
	{
		i = 0;
		checkmult = 1;
	}
//	printf("nb arch %d, magic_number : %x\n", nbarch, magic_number);
	while (i < nbarch)
	{
		magic_number = *(int *)tmpptr;
//		ft_printf("yo, %d\n", i);
		if ((unsigned int)magic_number == FAT_CIGAM || (unsigned int)magic_number == FAT_MAGIC)
		{
			stru->fat_header = (struct fat_header *)ptr;
			stru->fat_arch = ((void*)tmpptr + sizeof(struct fat_header) + (sizeof(struct fat_arch) * i));
			if (checkmult == 1)
			{
				ft_printf("\n%s (for architecture ", name);
				if (reversebytes32(stru->fat_arch->cputype) == CPU_TYPE_POWERPC)
					ft_printf("ppc):\n");
				if (reversebytes32(stru->fat_arch->cputype) == CPU_TYPE_I386)
					ft_printf("i386):\n");
			}
			stru->sizepart = reversebytes32(stru->fat_arch->size);
			if ((unsigned int)magic_number == FAT_CIGAM)
				offset = reversebytes32(stru->fat_arch->offset);
			else if ((unsigned int)magic_number == FAT_MAGIC)
				offset = stru->fat_arch->offset;
//			printf("64 bittttt : %u\n", stru->fat_arch->offset);
//			printf("hehec bon : %d\n", offset);
//			printf("hehec bon2 \n");
			magic_number = *(int *)(tmpptr + offset);
			ptr = tmpptr + offset;
		}
		if (count > 2 && (unsigned int)magic_number != 0x72613c21)
			ft_printf("\n%s:\n", name);
		if ((unsigned int)magic_number == MH_MAGIC_64)
		{
//			printf("magic64\n");
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
			ft_printf("cigam64\n");
			stru->header = (struct mach_header_64 *)ptr;
			stru->lc = (void *)ptr + sizeof(*stru->header);
			stru->seg = (struct segment_command_64*)stru->lc;
			if (checkcorrupt(ptr + stru->sizefile, stru->lc, stru) == 0)
				return (0);
		}
		if ((unsigned int)magic_number == MH_MAGIC)
		{
//			printf("magic32\n");
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
//			ft_printf("cigam32\n");
			stru->header32 = (struct mach_header *)ptr;
			stru->lc = (void *)ptr + sizeof(*stru->header32);
			stru->seg32 = (struct segment_command*)stru->lc;
			if (checkcorrupt(ptr + stru->sizefile, stru->lc, stru) == 0)
			{
				ft_printf("eror c con\n");
				return (0);
			}
			handle_32_reverse(ptr, stru);
		}
		if ((unsigned int)magic_number == 0x72613c21)
		{
			info = ft_strsplit(ptr + SARMAG, ' ');
			ar = (void*)ptr + SARMAG + sizeof(struct ar_hdr) + ft_atoi(info[5]);
			info = ft_strsplit((void*)ar, ' ');
//			ar = (void*)ar + sizeof(ar) + 2356;
			ran = 0;
//			printf("ar name : %s\n", ar->ar_fmag);
//			printf("arch : %d\n", ran->ran_off);
//			printf("ARCHIVE\n");
			if (stru->sizepart)
			{
//				ft_printf("sizepart : %d\n", stru->sizepart);
				stru->sizefile = stru->sizepart;
			}
			while (checkcorrupt(ptr + stru->sizefile, (void*)ar + sizeof(struct ar_hdr) + ft_atoi(info[5]) -1, stru) != 0)
			{
//				ft_printf("addr ptr : %p, addr ptr + size : %p\n", ptr, ptr + stru->sizefile);
				ft_printf("\n%s(%s):\n", name, ft_strsub(info[6], 2, ft_strlen(info[6])));
//				ft_printf("size : %d\n", ft_atoi(ft_strsub(ar->ar_name, 3, ft_strlen(ar->ar_name))));
//				ft_printf("size struct : %d size fmag : %d\n", sizeof(struct ar_hdr), sizeof(ar->ar_fmag));
				nm((void*)ar + sizeof(struct ar_hdr) + ft_atoi(ft_strsub(ar->ar_name, 3, ft_strlen(ar->ar_name))), ft_atoi(info[5]), name, 1);
//				printf("resaluit\n");
				if (checkcorrupt(ptr + stru->sizefile, (void*)ar + sizeof(struct ar_hdr) + ft_atoi(info[5]), stru) != 0)
					ar = (void*)ar + sizeof(struct ar_hdr) + ft_atoi(info[5]);
				else
					return (1);
				info = ft_strsplit((void*)ar, ' ');
//				printf("resaluit2\n");
			}
//			printf("resaluit5\n");
//			stru->sym = (struct symtab_command*)ptr + 8;
//			printf("size : %d", stru->sym->size);
		}
//		printf("resaluit4\n");
		if (stru->check == 1)
			return (0);
		i++;
//		printf("resaluit3\n");
	}
//	printf("saluit\n");
	return (1);
}

int					check_error(int ac, char **av, int fd, int i)
{
//	ft_printf("i : %d, ac : %d, name : %s\n", i, ac, av[i]);
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
		if (fd > -2 && nm(ptr, buf.st_size, av[i], ac) == 0)
			return (exitstr("Error file corrupted\n", 2));
		if (fd > -2 && munmap(ptr, buf.st_size) < 0)
			return (exitstr("Error munmap\n", 2));
		if (ac == 1)
			ac++;
	}
}
