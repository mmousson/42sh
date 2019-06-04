/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 02:11:28 by mmousson          #+#    #+#             */
/*   Updated: 2019/06/04 13:01:52 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>

# define BUFF_SIZE 1664
# define FT_ARG1 0x01
# define FT_ARG2 0x02
# define FT_ARG3 0x04
# define FT_ARG4 0x08

char				*ft_strapp(char *str, char c);
int					ft_putchar(wchar_t ch);
void				ft_putstr(char const *s);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putllong(long long ll);
void				ft_putfloat(float f);
size_t				ft_strlen(const char *str);
void				ft_bzero(void *s, size_t n);
long int			ft_atol(const char *s, int *error);
int					ft_atoi(const char *str);
int					ft_valid_to_atoi(const char *str);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isxdigit(int c);
int					ft_string_isdigit(const char *s);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
int					ft_memcmp(const void *str1, const void *str2, size_t n);
void				*ft_memcpy(void *str1, const void *str2, size_t n);
void				*ft_memccpy(void *dest, const void *src, int c, size_t n);
void				*ft_memmove(void *str1, const void *str2, size_t n);
void				*ft_memchr(const void *str, int c, size_t n);
void				*ft_memset(void *s, int c, size_t n);
char				*ft_strshift(char *str, char replacement, size_t count);
char				*ft_strdup(const char *s);
char				*ft_strcpy(char *dest, const char *src);
char				*ft_strncpy(char *dest, const char *src, size_t n);
char				*ft_strcat(char *dest, const char *src);
char				*ft_strncat(char *dest, char *src, size_t n);
size_t				ft_strlcat(char *dest, const char *src, size_t size);
char				*ft_strchr(const char *str, int c);
char				*ft_strrchr(const char *str, int c);
char				*ft_strstr(const char *haystack, const char *needle);
char				*ft_strrstr(const char *haystack, const char *needle);
char				*ft_strnstr(const char *haystack, const char *needle,
	size_t len);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
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
char				*ft_strjoinf(char *s1, char *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
char				*ft_itoa(int nb);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
char				*ft_stradd(char *addend1, char *addend2,
	short rm_front_zeros);
char				*ft_strmultiply(char *factor1, char *factor2,
	short rm_front_zeros);
char				*ft_strdivide_two(char *str);
void				*ft_rotate_left(void *array, size_t array_size, size_t n,
	size_t data_size);
int					get_line(const int fd, char **line, char **isread);
void				ft_del_words_tables(char ***tab);
int					ft_order_of_magnitude(int nb);
int					get_next_line(const int fd, char **line);
int					ft_strendswith(char *str, const char *end);
void				ft_strremove_at(char *str, size_t index);
void				ft_print_words_tables(char **str);

typedef	struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

union				u_fabs_matcher
{
	double			double_corres;
	unsigned long	int_corres;
};

int					ft_lstdepth(t_list *list);
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void				ft_lstpush(t_list **alst, t_list *new);
int					ft_abs(int x);
int					ft_min(int x, int y);
double				ft_dmin(int count, ...);
int					ft_max(int x, int y);
double				ft_dmax(int count, ...);
int					ft_clamp(int x, int low, int high);
double				ft_fabs(double x);
int					ft_count_n(int nbr);

/* 
** Libft hben-yah
*/

char				*ft_strimplode(char **tab, char delim);
char				*ft_strimplodef(char **tab, char delim);
void				ft_tabdel(void ***tab);
void				ft_strtabdel(char ***tab);
void				ft_strtabdel2(char ***tab1, char ***tab2);
int					ft_strtabadd(char ***tab, char *new);
char				*ft_strjoinfs(char *s1, char *s2, char flag);
char				*ft_strjoin3fs(char *s1, char *s2, char *s3, char flag);
char				*ft_strrmvfirst(char *s);
size_t				ft_strtablen(char **tab);
size_t				ft_tabstrlen(char **tab, size_t *i);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
char				*ft_strmove(char *dst, const char *src);
size_t				ft_tablen(void **tab);
void				**ft_tabrealloc(void **tab, size_t len);
void				**ft_taballoc(size_t len);
size_t				ft_tablcpy(void **dst, void **src, size_t size);
char				*ft_ltoa(long n);
long				ft_atol_base(char *str, char base_len);
int					ft_indexof(char c, char *str);
int					ft_is_base(char base, char *s);
void				ft_putstr2_fd(char const *s1, char const *s2, int fd);
void				ft_putstr3_fd(char const *s1, char const *s2, char const *s3, int fd);
void				ft_putendl2_fd(char const *s1, char const *s2, int fd);
void				ft_putendl3_fd(char const *s1, char const *s2, char const *s3, int fd);
char				**ft_strtabdup(char **tab);
char				**ft_strtaballoc(size_t len);

#endif
