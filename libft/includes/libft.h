/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anazar <anazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 10:14:28 by anazar            #+#    #+#             */
/*   Updated: 2017/12/26 15:42:09 by anazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# define BUFF_SIZE 1
# define DBG_INT(str, x) ft_putstr(str); ft_putnbr(x); ft_putchar('\n');
# define DBG_CHAR(str, x) ft_putstr(str); ft_putchar(x); ft_putchar('\n');
# define MIN(x, y) (x < y ? x : y )
# define MAX(x, y) (x >= y ? x : y)
# define ABS(x) (x >= 0 ? x : -x)
# define PI 3.141592653
# define POW(x, y, o) o = x; int p_it = 0; while(++p_it < y) o *= x;
# define AVG(x, y) ((x + y) / 2.0)
# define SWITCH(a, b) if (a) b;
# define CASE(a, b) else if (a) b;
# define DEFAULT(a) else a;

# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/stat.h>
# include <math.h>
# include <stdarg.h>
# include <stdint.h>
# include <inttypes.h>

/*
 **Part 1
*/

void				*ft_memset(void *b, int c, size_t len);

void				ft_bzero(void *s, size_t n);

void				*ft_memcpy(void *dst, const void *src, size_t n);

void				*ft_memccpy(void *dst, const void *src, int c, size_t n);

void				*ft_memmove(void *dst, const void *src, size_t len);

void				*ft_memchr(const void *s, int c, size_t n);

int					ft_memcmp(const void *s1, const void *s2, size_t n);

size_t				ft_strlen(const char *s);

char				*ft_strdup(const char *s1);

char				*ft_strcpy(char *dst, const char *src);

char				*ft_strncpy(char *dst, const char *src, size_t len);

char				*ft_strcat(char *s1, const char *s2);

char				*ft_strncat(char *s1, const char *s2, size_t n);

size_t				ft_strlcat(char *dst, const char *src, size_t size);

char				*ft_strchr(const char *s, int c);

char				*ft_strrchr(const char *s, int c);

char				*ft_strstr(const char *big, const char *little);

char				*ft_strnstr(const char *big, const char *little,
					size_t len);

int					ft_strcmp(const char *s1, const char *s2);

int					ft_strncmp(const char *s1, const char *s2, size_t n);

int					ft_atoi(const char *s1);

int					ft_isalpha(int c);

int					ft_isdigit(int c);

int					ft_isalnum(int c);

int					ft_isascii(int c);

int					ft_isprint(int c);

int					ft_toupper(int c);

int					ft_tolower(int c);

/*
 **Part 2
*/

void				*ft_memalloc(size_t size);

void				ft_memdel(void **ap);

char				*ft_strnew(size_t size);

void				ft_strdel(char **as);

void				ft_strclr(char *s);

void				ft_striter(char *s, void (*f)(char *));

void				ft_striteri(char *s, void (*f)(unsigned int, char *));

char				*ft_strmap(char const *s, char (*f)(char));

char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));

int					ft_strequ(char const *s1, char const *s2);

int					ft_strnequ(char const *s1, char const *s2, size_t n);

char				*ft_strsub(char const *s, unsigned int start, size_t len);

char				*ft_strjoin(char const *s1, char const *s2);

char				*ft_strtrim(const char *s);

char				**ft_strsplit(const char *s, char c);

char				*ft_itoa(int n);

void				ft_putchar(char c);

void				ft_putstr(char const *s);

void				ft_putendl(char const *s);

void				ft_putnbr(int n);

void				ft_putchar_fd(char c, int fd);

void				ft_putstr_fd(char const *s, int fd);

void				ft_putendl_fd(char const *s, int fd);

void				ft_putnbr_fd(int n, int fd);

/*
** Bonus
*/

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

t_list				*ft_lstnew(void const *content, size_t content_size);

void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));

void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));

void				ft_lstadd(t_list **alst, t_list *n);

void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));

t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));

/*
** Additional Functions
*/

int					ft_iswhitespace(char c);

void				ft_swap(char *a, char *b);

int					ft_isupper(int c);

int					ft_islower(int c);

int					ft_find(char *str, char *to_find);

char				*ft_find_and_replace(char *str, char *t_f, char *t_r);

char				**ft_split_by_delims(const char *s, char *delims);

char				**ft_split_by_function(const char *s, int(*f)(char));

char				*ft_trim_by_delims(const char *s, char *delims);

char				*ft_trim_by_function(const char *s, int(*f)(char));

int					ft_is_in(char c, char *str);

int					ft_countif(char *str, char c);

char				*ft_strjoinfree(char *s1, char *s2);

void				ft_strfncpy(char *dst, char *src, int len);

void				ft_strrncpy(char *dst, char *src, int len);

long long			ft_atoll(const char *str);

int					ft_general_validate(char *format, char *str);

/*
** printf
*/

int					ft_printf(const char *str, ...);

void				parse_flags(int *i, const char *str, va_list args, int *p);

void				parse_j(va_list args, int *p, const char *str, int *i);

void				parse_z(va_list args, int *p, const char *str, int *i);

void				parse_l(va_list args, int *p, const char *str, int *i);

void				parse_ll(va_list args, int *p, const char *str, int *i);

void				parse_rightalign(int *i, const char *str,
						va_list args, int *p);

void				parse_leftalign(int *i, const char *str,
						va_list args, int *p);

void				parse_rightpalign(int *i, const char *str,
						va_list args, int *p);

void				parse_leftpalign(int *i, const char *str,
						va_list args, int *p);

void				parse_zero(int *i, const char *str,
						va_list args, int *p);

void				parse_pzero(int *i, const char *str,
						va_list args, int *p);

void				flags_int(va_list args, int *p);

void				flags_oct(va_list args, int *p);

void				flags_uint(va_list args, int *p);

void				flags_hex(va_list args, int *p);

void				flags_uhex(va_list args, int *p);

void				flags_inth(va_list args, int *p);

void				flags_octh(va_list args, int *p);

void				flags_uinth(va_list args, int *p);

void				flags_hexh(va_list args, int *p);

void				flags_uhexh(va_list args, int *p);

void				flags_inthh(va_list args, int *p);

void				flags_octhh(va_list args, int *p);

void				flags_uinthh(va_list args, int *p);

void				flags_hexhh(va_list args, int *p);

void				flags_uhexhh(va_list args, int *p);

void				flags_intl(va_list args, int *p);

void				flags_octl(va_list args, int *p);

void				flags_uintl(va_list args, int *p);

void				flags_hexl(va_list args, int *p);

void				flags_uhexl(va_list args, int *p);

void				flags_intll(va_list args, int *p);

void				flags_octll(va_list args, int *p);

void				flags_uintll(va_list args, int *p);

void				flags_hexll(va_list args, int *p);

void				flags_uhexll(va_list args, int *p);

void				flags_intj(va_list args, int *p);

void				flags_octj(va_list args, int *p);

void				flags_uintj(va_list args, int *p);

void				flags_hexj(va_list args, int *p);

void				flags_uhexj(va_list args, int *p);

void				flags_intz(va_list args, int *p);

void				flags_octz(va_list args, int *p);

void				flags_uintz(va_list args, int *p);

void				flags_hexz(va_list args, int *p);

void				flags_uhexz(va_list args, int *p);

void				flags_adr(va_list args, int *p);

void				flags_per(int *p);

void				flags_str(va_list args, int *p);

void				flags_char(va_list args, int *p);

void				flags_wchar(va_list args, int *p, const char *str, int *i);

void				flags_ws(va_list args, int *p, const char *str, int *i);

void				flags_plus(va_list args, int *p, const char *str, int *i);

void				flags_hash(va_list args, int *p, const char *str, int *i);

int					ft_strucmp(const char *s1, const char *s2);

void				ft_putoct(unsigned int n, int *p);

void				ft_putunbr(unsigned int n, int *p);

void				ft_puthex(unsigned int n, int *p);

void				ft_putuhex(unsigned int n, int *p);

void				ft_putstrf(char const *s, int *p);

void				ft_putnbrf(int n, int *p);

size_t				ft_numulen(unsigned int n);

void				ft_putadr(unsigned long n, int *p);

void				ft_putull(unsigned long long n, int *p);

void				ft_putld(long n, int *p);

void				ft_putwstrf(wchar_t *s, int *p);

size_t				ft_numlen(int n);

char		*ft_itoa_base(unsigned long long int value, int base, int lowercase);

/*
**	Get_next_line
*/

typedef struct		s_gnl
{
	char			*str;
	int				last;
	int				newline;
	int				bytes_read;
}					t_gnl;

int					get_next_line(int fd, char **line);

#endif
