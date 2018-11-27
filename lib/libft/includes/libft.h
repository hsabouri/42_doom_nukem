/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/05 09:28:35 by hsabouri          #+#    #+#             */
/*   Updated: 2018/11/12 11:37:21 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <unistd.h>
# include <stdlib.h>
# include <string.h>

# define LPUSH(list, elem) push(list, (t_elem *)elem)
# define LPPUSH(list, elem) push(list, (t_pelem *)elem)
# define LINSERT(list, elem) insert(list, (t_elem *)elem)
# define LPINSERT(list, elem) insert(list, (t_pelem *)elem)

typedef struct	s_elem
{
	struct s_elem	*next;
}				t_elem;

typedef struct	s_pelem
{
	struct s_pelem	*next;
	struct s_pelem	*prev;
}				t_pelem;

typedef struct	s_list
{
	size_t			len;
	t_elem			*first;
	t_elem			*last;
	t_elem			*current;
	struct s_list	*(*push)(struct s_list *, t_elem *);
	struct s_list	*(*insert)(struct s_list *, t_elem *);
	struct s_list	(*map)(const struct s_list *, t_elem *(*)(const t_elem *));
	struct s_list	(*mapi)(const struct s_list *, t_elem *(*)(const t_elem *, size_t i));
	struct s_list	*(*foreach)(struct s_list *, void (*)(t_elem *));
	struct s_list	*(*foreachi)(struct s_list *, void (*)(t_elem *, size_t i));
	struct s_list	*(*join)(struct s_list *, struct s_list *);
	void			*(*fold)(const struct s_list *, void *, void *(*)(const t_elem *, void *));
	void			*(*foldi)(const struct s_list *,  void *, void *(*)(const t_elem *, void *, size_t));
	t_elem			*(*pop)(struct s_list *);
	t_elem			*(*shift)(struct s_list *);
	t_elem			*(*next)(struct s_list *);
}				t_list;

typedef struct	s_plist
{
	size_t			len;
	t_pelem			*first;
	t_pelem			*last;
	t_pelem			*current;
	struct s_plist	*(*push)(struct s_plist *, t_pelem *);
	struct s_plist	*(*insert)(struct s_plist *, t_pelem *);
	struct s_plist	(*map)(const struct s_plist *, t_pelem *(*)(const t_pelem *));
	struct s_plist	(*mapi)(const struct s_plist *, t_pelem *(*)(const t_pelem *, size_t i));
	struct s_plist	*(*foreach)(struct s_plist *, void (*)(t_pelem *));
	struct s_plist	*(*foreachi)(struct s_plist *, void (*)(t_pelem *, size_t i));
	struct s_plist	*(*join)(struct s_plist *, struct s_plist *);
	void			*(*fold)(const struct s_plist *, void *, void *(*)(const t_pelem *, void *));
	void			*(*foldi)(const struct s_plist *, void *, void *(*)(const t_pelem *, void *, size_t));
	t_pelem			*(*pop)(struct s_plist *);
	t_pelem			*(*shift)(struct s_plist *);
	t_pelem			*(*next)(struct s_plist *);
	t_pelem			*(*previous)(struct s_plist *);
}				t_plist;

void			*ft_memset(void *b, int c, size_t len);
void			ft_bzero(void *s, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memcpy(void *dst, const void *src,
				size_t n);
void			*ft_memccpy(void *dst, const void *src,
				int c, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memchr(const void *s, int c, size_t n);
void			*ft_memrchr(const void *s, int c, size_t n);
void			*ft_memjoin(const void *s1, const void *s2, size_t len1,
				size_t len2);
size_t			ft_strlen(const char *s);
char			*ft_strdup(const char *s1);
char			*ft_strcpy(char *dst, const char *src);
char			*ft_strncpy(char *dst, const char *src, size_t len);
char			*ft_strcat(char *s1, const char *s2);
char			*ft_strncat(char *s1, const char *s2,
				size_t len);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
char			*ft_strstr(const char *big, const char *little);
char			*ft_strnstr(const char *big, const char *little,
				size_t len);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_atoi(const char *str);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);
int				ft_isspace(int c);
int				ft_isblank(int c);
int				ft_isblankn(int c);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char const *s, int fd);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_putchar(char c);
void			ft_putstr(char const *s);
void			ft_putendl(char const *s);
void			ft_putnbr(int n);
void			*ft_memalloc(size_t size);
void			ft_memdel(void **ap);
char			*ft_strnew(size_t size);
void			ft_strdel(char **as);
void			ft_strclr(char *s);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int				ft_strequ(char const *s1, char const *s2);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s);
char			**ft_strsplit(char const *s, char c);
char			*ft_itoa(int n);

t_list			lnew(t_elem *first);
t_list			*lpush(t_list *list, t_elem *elem);
t_list			*linsert(t_list *list, t_elem *elem);
t_list			*ljoin(t_list *begin, t_list *end);
t_elem			*lnext(t_list *list);
void			*lfold(const t_list *list, void *acc, void *(*f)(const t_elem *elem, void *));
void			*lfoldi(const t_list *list, void *acc, void *(*f)(const t_elem *elem, void *,
				size_t i));
t_list			*lforeach(t_list *list, void (*f)(t_elem *elem));
t_list			*lforeachi(t_list *list, void (*f)(t_elem *elem, size_t i));
t_list			lmap(const t_list *list, t_elem *(*f)(const t_elem *elem));
t_list			lmapi(const t_list *list, t_elem *(*f)(const t_elem *elem, size_t i));
t_elem 			*lshift(t_list *list);
t_elem			*lpop(t_list *list);

t_plist			lpnew(t_pelem *first);
t_plist			*lppush(t_plist *list, t_pelem *elem);
t_plist			*lpinsert(t_plist *list, t_pelem *elem);
t_plist			*lpjoin(t_plist *begin, t_plist *end);
t_pelem			*lpnext(t_plist *list);
t_pelem			*lprevious(t_plist *list);
void			*lpfold(const t_plist *list, void *acc, void *(*f)(const t_pelem *elem, void *));
void			*lpfoldi(const t_plist *list, void *acc, void *(*f)(const t_pelem *elem, void *,
				size_t i));
t_plist			*lpforeach(t_plist *plist, void (*f)(t_pelem *pelem));
t_plist			*lpforeachi(t_plist *plist, void (*f)(t_pelem *pelem, size_t i));
t_plist			lpmap(const t_plist *list, t_pelem *(*f)(const t_pelem *elem));
t_plist			lpmapi(const t_plist *list, t_pelem *(*f)(const t_pelem *elem, size_t i));
t_pelem 		*lpshift(t_plist *list);
t_pelem			*lppop(t_plist *list);

#endif
