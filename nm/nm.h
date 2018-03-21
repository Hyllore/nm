/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 11:12:34 by droly             #+#    #+#             */
/*   Updated: 2018/03/21 13:27:46 by droly            ###   ########.fr       */
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
# include <mach-o/fat.h>
# include "../libft/libft.h"
# include <ar.h>
# include <mach-o/ranlib.h>

typedef struct					s_stru
{
	struct symtab_command		*sym;
	struct section_64			*sec;
	uint32_t					offset;
	void						*tmpptr;
	int							magic_number;
	struct section				*sec32;
	unsigned int				i[5];
	struct ar_hdr				*ar;
	char						**info;
	int							nbarch;
	struct load_command			*lc;
	char						**secname;
	struct s_nm					*nm;
	off_t						sizefile;
	uint32_t					sizepart;
	char						*stringtable;
	struct mach_header_64		*header;
	struct mach_header			*header32;
	struct fat_header			*fat_header;
	struct fat_arch				*fat_arch;
	struct segment_command_64	*seg;
	struct segment_command		*seg32;
	int							check[2];
	int							check2;
	int							obj;
}								t_stru;

typedef struct					s_nm
{
	char						*name;
	char						type;
	uint32_t					value;
	struct s_nm					*next;
}								t_nm;

char							secto(unsigned int n_sect, char **secname,
		struct s_stru *stru);
int								checkcorrupt(char *tmp, void *ptr, \
		struct s_stru *stru);
void							handle_64(char *ptr, struct s_stru *stru);
void							handle_32(char *ptr, struct s_stru *stru);
int								exitstr(char *str, int error);
void							print_output(struct s_stru *stru, char *ptr);
void							print_output32(struct s_stru *stru, char *ptr);
void							print_output32_reverse(struct s_stru *stru,
		char *ptr, uint32_t i);
uint64_t						reversebytes64(uint64_t nb);
uint32_t						reversebytes32(uint32_t nb);
void							handle_32_reverse(char *ptr, struct
		s_stru *stru);
void							handle_64_reverse(char *ptr, struct
		s_stru *stru);
int								nm6(struct s_stru *stru, void *ptr,
		char *name);
void							struinit(struct s_stru *stru, int sizefile,
		void *ptr);
int								nm(char *ptr, off_t sizefile, char *name,
		int count);
void							nm2(struct s_stru *stru, void *ptr,
		int sizefile);
char							*nm3(struct s_stru *stru, void *ptr,
		char *name);
int								nm4(struct s_stru *stru, void *ptr, int
		count, char *name);
int								nm5(struct s_stru *stru, void *ptr);
int								nm6(struct s_stru *stru, void *ptr,
		char *name);

#endif
