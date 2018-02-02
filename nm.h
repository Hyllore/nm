/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 11:12:34 by droly             #+#    #+#             */
/*   Updated: 2018/02/02 11:24:17 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H

# include <stdio.h>
# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <stdlib.h>
# include "libft/libft.h"


typedef struct				s_stru
{
	struct symtab_command	*sym;
	struct section_64		*sec;
	int						i[3];
	struct load_command		*lc;
	char					**secname;
	struct s_nm				*nm;
	struct s_nm				*tmp;
	off_t						sizefile;
	char					*stringtable;
	struct mach_header_64		*header;
	struct segment_command_64	*seg;
	int							check;
}							t_stru;

typedef struct				s_nm
{
	char					*name;
	char					type;
	uint32_t				value;
	struct s_nm				*next;
}							t_nm;

#endif
