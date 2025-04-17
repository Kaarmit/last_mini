/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 12:57:37 by aarmitan          #+#    #+#             */
/*   Updated: 2025/04/13 12:38:50 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALL_H
# define ALL_H

# include <assert.h>
# include <fcntl.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

//******************************************************************************
// BUFFER SIZE FOR GET NEXT LINE
//******************************************************************************
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

//******************************************************************************
//			DEFINE TEMINAL COLOR
//******************************************************************************
# define WRITE_COLOR_DEFAULT "\033[0m"
# define WRITE_COLOR_RED "\033[31m"
# define WRITE_COLOR_GREEN "\033[32m"
# define WRITE_COLOR_ORANGE "\033[33m"

//******************************************************************************
//			Typedefs
//******************************************************************************

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

//******************************************************************************
//			ft_printf
//******************************************************************************
int					ft_printf(const char *str, ...);
int					ft_printstr(char *str, int *output);
int					ft_printchar(int c);
void				ft_print_id(int n, int *output);
void				ft_print_u(unsigned int value, int *output);
void				ft_print_ptr(unsigned long long n, int *output);
void				ft_print_hexa(unsigned int value, const char c,
						int *output);
void				ft_putchar_fd(char c, int fd);

//******************************************************************************
//			Output Functions
//******************************************************************************
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);

//******************************************************************************
//			Character Classification Functions
//******************************************************************************
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
int					ft_tolower(int c);
int					ft_toupper(int c);

//******************************************************************************
//			String Functions
//******************************************************************************
// char				**ft_split(char const *s, char c);
// char				*ft_strjoin(const char *s1, const char *s2);
char				*ft_strcat(char *dest, const char *src);
char				*ft_strcpy(char *dest, const char *src);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strdup(const char *s1);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strncpy(char *dest, const char *src, size_t n);
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
size_t				ft_strlcat(char *dst, const char *src, size_t size);
size_t				ft_strlcpy(char *dst, const char *src, size_t siz);
size_t				ft_strlen(const char *s);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);

//******************************************************************************
//			Memory Functions
//******************************************************************************
void				ft_bzero(void *s, size_t n);
void				*ft_calloc(size_t nmemb, size_t size);
void				*ft_memchr(const void *s, int c, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memset(void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);

//******************************************************************************
//			Conversion Functions
//******************************************************************************
char				*ft_itoa(int n);
int					ft_atoi(const char *nptr);

//******************************************************************************
//			Linked List Functions
//******************************************************************************
void				ft_lstadd_front(t_list **lst, t_list *new);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstnew(void *content);
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
t_list				*ft_lstlast(t_list *lst);
int					ft_lstsize(t_list *lst);

//******************************************************************************
//			gnl.c
//******************************************************************************
char				*get_next_line(int fd);
char				*set_line(char *line_buffer);
char				*fill_line_buffer(int fd, char *left_c, char *buffer);
char				*ftt_strjoin(const char *s1, const char *s2);
char				*ftt_substr(char const *s, unsigned int start, size_t len);
char				*ftt_strdup(const char *s1);
char				*ftt_strchr(const char *s, int c);
size_t				ftt_strlen(const char *s);
void				test(void) __attribute__((destructor));

#endif
