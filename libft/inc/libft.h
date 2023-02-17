/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 17:23:20 by aoropeza          #+#    #+#             */
/*   Updated: 2022/05/10 18:17:28 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

/********************/
/*		LIBFT		*/
/********************/

typedef unsigned char	t_size;

int		ft_isalpha(int arg);
int		ft_isdigit(int arg);
int		ft_isalnum(int arg);
int		ft_isascii(int arg);
int		ft_isprint(int arg);
size_t	ft_strlen(const char *str);
void	*ft_memset(void *str, int ch, size_t nb);
void	ft_bzero(void *str, size_t nb);
void	*ft_memcpy(void *dest, const void *src, size_t nb);
void	*ft_memmove(void *dest, const void *src, size_t nb);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
int		ft_toupper(int ch);
int		ft_tolower(int ch);
char	*ft_strchr(const char *str, int ch);
char	*ft_strrchr(const char *str, int ch);
int		ft_strncmp(const char *str_one, const char *str_two, size_t n);
void	*ft_memchr(const void *str, int ch, size_t nb);
int		ft_memcmp(const void *str_one, const void *str_two, size_t nb);
char	*ft_strnstr(const char *str, const char *to_find, size_t len);
int		ft_atoi(const char *str);
void	*ft_calloc(size_t nitems, size_t size);
char	*ft_strdup(const char *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *str, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

/* BONUS FUNCTIONS */

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list	**lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/********************/
/*		PRINTF		*/
/********************/

int		ft_printf(char const *str, ...);
void	check_conversion(char ch, va_list args, int	*ptrlen);
void	ft_putchar(char c, int *ptrlen);
void	ft_putstr(char *s, int *ptrlen);
void	ft_putnbr(int n, int *ptrlen);
void	ft_putunbr(unsigned int n, int *ptrlen);
void	ft_tohex(unsigned int nb, char c, int *ptrlen);
void	ft_toptr(unsigned long nb, int *ptrlen);

/********************/
/*	GET_NEXT_LINE	*/
/********************/

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

char	*get_next_line(int fd);

#endif
