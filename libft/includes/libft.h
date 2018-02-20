/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anazar <anazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 10:14:28 by anazar            #+#    #+#             */
/*   Updated: 2018/02/19 16:14:22 by ihodge           ###   ########.fr       */
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

size_t				ft_atoz(const char *str);

int					ft_general_validate(char *format, char *str);

/*
** printf
*/

typedef	struct		s_format
{
	char			conv;
	char			length;
	int				space;
	int				plus;
	int				minus;
	int				alternate;
	int				zero;
	int				mfw;
	int				precision;
	int				strlength;
	int				fd;
}					t_format;

union				u_data_union
{
	unsigned int	uint;
	unsigned char	uchar;
	unsigned short	ushort;
	unsigned long	ulong;
	size_t			usizet;
	uintmax_t		uintmaxt;
};

typedef char		*(*t_ufptr)(union u_data_union du, t_format *format,
		unsigned int base);

int					ft_printf(const char *str, ...);

int					ft_printf_fd(int fd, const char *str, ...);

t_format			*create_format(void);

char				*dispatcher(t_format *format, long long data);

char				*u_dispatcher(t_format *format, unsigned long data);

char				*plus_flag(char *str, long long data);

char				*space_flag(char *str, long long data);

char				*min_field_wid(char *str, t_format *format);

void				fill_after(char *str, char **result, int fill);

void				fill_before(char *str, char **result, int fill,
		char character);

char				*int_precision(char *str, int precision, int data);

char				*negative_int(char *str, long long data);

char				*ft_lltoa(long long n);

char				*ft_ultoa_base(union u_data_union du, t_format *format,
		unsigned int base);

char				*fptr_with_length(char c, char l, long long *data);

char				*ufptr_with_length(t_format *format, unsigned long *data);

char				*alt_flag(char *str, t_format *format);

int					is_flag(char c);

int					is_conv(char c);

int					is_length(char *str, t_format *format);

char				*string_conv(t_format *format, char *str);

char				*str_precision(char *str, int precision);

char				*mfw_char(char *str, t_format *format);

void				write_arg(va_list ap, t_format *format, char conv);

void				write_arg_fd(va_list ap, t_format *format, char conv);

void				char_conv(t_format *format, unsigned char c);

void				change_conv(t_format *format);

void				save_signs(t_format *format, char c);

void				save_flag(t_format *format, char *str);

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
