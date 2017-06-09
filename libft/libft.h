/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 15:09:59 by droly             #+#    #+#             */
/*   Updated: 2016/04/29 15:34:30 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# define BUFF_SIZE 100
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include <wchar.h>
# include <stdlib.h>
# include <stdarg.h>

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef struct		s_flags
{
	int				diese;
	int				zero;
	int				minus;
	int				plus;
	int				space;
}					t_flags;

typedef struct		s_printf
{
	int				field;
	int				precision;
	char			*len_modif;
	char			type;
	int				i;
	int				i2;
	int				tmp;
}					t_printf;

int					ft_printf(const char *format, ...);
t_printf			seek_len_modif_types(t_printf *lst, const char *format,
		int i);
t_printf			seek_field_precision(t_printf *lst, const char *format,
		int i);
t_flags				seek_flags(t_flags *lst2, char *t);
t_printf			seek_types(t_printf *lst, const char *format,
		va_list argptr, t_flags *lst2);
t_printf			apply_flags(t_printf *lst, t_flags *lst2, va_list argptr,
		char *str);
char				*put_in_maj(char *str);
char				*take_type1(t_printf *lst, t_flags *lst2, char *str,
			va_list argptr);
char			*take_type2(t_printf *lst, char *str, va_list argptr);
char				*apply_diese(t_printf *lst, char *str);
char				*apply_space(char *str);
char				*apply_plus(char *str);
char				*apply_field_zero(t_printf *lst, t_flags *lst2, char *str,
		int i);
char				*apply_field_space(t_printf *lst, t_flags *lst2, char *str,
		int i);
char				*apply_precision_str(t_printf *lst, char *str);
char				*apply_precision_num(t_printf *lst, char *str,
		int i);
char				*apply_len_modif(t_printf *lst, char *str, va_list argptr,
		t_flags *lst2);
char				*len_modif_d_i(t_printf *lst, char *str, va_list argptr);
char				*len_modif_o_u(t_printf *lst, char *str, va_list argptr,
		t_flags *lst2);
char				*len_modif_l_z(t_printf *lst, char *str, va_list argptr,
		long long i);
char				*len_modif_h_j(t_printf *lst, char *str, va_list argptr,
		long long i);
char				*len_modif_l_z2(t_printf *lst, char *str, va_list argptr,
		unsigned long long i);
char				*len_modif_h_j2(t_printf *lst, char *str, va_list argptr,
		unsigned long long i);
t_printf			write_char(t_printf *lst, char *str, int i);
t_printf			ft_printf_bis(const char *format, va_list argptr,
		t_printf *lst);
char				*db(long long i, char *str);
char				*db2(unsigned long long i, char *str);
long long			plus(long long i);
char				*ft_unicode(wchar_t c);
t_printf			write_c(t_printf *lst, va_list argptr, t_flags *lst2);
t_printf			percent_analysis(const char *format, t_printf *lsti);
t_printf			apply_percent(t_printf *lst);
t_printf			add_bonus(const char *format, t_printf *lsti);
t_printf			minus_plus(t_printf *lst);
t_printf			write_s(t_printf *lst, va_list argptr, t_flags *lst2);
t_printf			minus_1(t_printf *lst, va_list argptr);
t_printf			minus_0(t_printf *lst, va_list argptr);
char				*precision_minus(char *str, int i2, t_printf *lst, char *c);
t_printf			countdmrd(t_printf *lst, va_list argptr);
t_printf			countdmrd2(t_printf *lst, char *str, va_list argptr);
t_printf			countq(t_printf *lst, wchar_t c);
char				*special(char *str, va_list argptr, t_printf *lst);
int					get_next_line(int const fd, char **line);
char				*ft_itoa_base(int value, int base);
void				ft_putnbr_u(unsigned n);
char				*ft_itoa_u(unsigned int n);
void				ft_putstr(char *str);
void				ft_putchar(char c);
char				*ft_strcpy(char *dest, const char *src);
size_t				ft_strlen(const char *s);
char				*ft_strncpy(char *dest, const char *src, size_t n);
char				*ft_strdup(const char *s);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strnstr(const char *s1, const char *s2, size_t n);
char				*ft_strstr(const char *s1, const char *s2);
char				*ft_strrchr(const char *s, int c);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strchr(const char *s, int c);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
char				*ft_strncat(char *s1, const char *s2, size_t n);
long long			ft_atoi(const char *str);
size_t				ft_strlcat(char *dst, const char *src, size_t n);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char*s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char(*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				*ft_itoa(int n);
char				*ft_utoa(unsigned long long n);
char				**ft_strsplit(char const *s, char c);
void				ft_putendl(char const *s);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr(int n);
void				ft_putnbr_fd(int n, int fd);
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void*, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
int					ft_power(int n, int power);
void				ft_putwchar(wchar_t c);
char				*ft_itoa_base_ull(unsigned long long value, int base);
int					ft_putwstr(wchar_t *str);
unsigned long long	ft_utoi(const char *str);

#endif
