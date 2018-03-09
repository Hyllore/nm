/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 16:44:15 by droly             #+#    #+#             */
/*   Updated: 2018/03/09 16:55:02 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OTOOL_H
# define OTOOL_H

# include <stdio.h>
# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <mach-o/fat.h>
# include "libft/libft.h"
# include <ar.h>
# include <mach-o/ranlib.h>

typedef struct					s_stru
{
	struct symtab_command		*sym;
	struct section_64			*sec;
	struct section				*sec32;
	unsigned int				i[3];
	struct load_command			*lc;
	char						**secname;
	struct s_nm					*nm;
	off_t						sizefile;
	char						*stringtable;
	struct mach_header_64		*header;
	struct mach_header			*header32;
	struct fat_header			*fat_header;
	struct fat_arch				*fat_arch;
	struct segment_command_64	*seg;
	struct segment_command		*seg32;
	int							check;
	int							check2;
	int							obj;
}								t_stru;

int		exitstr(char *str, int errori);

#endif
