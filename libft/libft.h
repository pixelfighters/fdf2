/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kami <kami@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 09:59:49 by fschuh            #+#    #+#             */
/*   Updated: 2024/06/07 18:44:44 by kami             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <stdio.h>
# include <stdarg.h>
# include <string.h>
# include <fcntl.h>
# include <limits.h>
# define MAX_FD 1024
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"
#define KYEL "\x1B[33m"
#define KBLU "\x1B[34m"
#define KMAG "\x1B[35m"
#define KCYN "\x1B[36m"
#define KWHT "\x1B[37m"

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
size_t	ft_strlen(const char *str);
int		ft_toupper(int c);
int		ft_tolower(int c);
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
char	*ft_strchr(const char *str, int character);
char	*ft_strrchr(const char *str, int character);
int		ft_strncmp(const char *str1, const char *str2, size_t num);
void	*ft_memchr(const void *str, int character, size_t num);
int		ft_memcmp( const void *ptr1, const void *ptr2, size_t num );
char	*ft_strnstr(const char *str, const char *c, size_t num);
char	*ft_strstr(const char *str, int character);
int		ft_atoi(const char *str);
void	*ft_calloc(size_t num, size_t size);
char	*ft_strdup(const char *str1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strtrim(const char *s1, const char *set);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
char	*ft_itoa(int n);
char	**ft_split(char const *s, char c);
void	ft_print_ascii_art(char teststring[26], char color[], int fd);
int		ft_putchar(char c);
int		ft_putnbr_rlen(int n, int rlen);
int		ft_putnbr_unsigned_rlen(unsigned int n, int rlen);
int		ft_putnbr_hex_rlen(unsigned int n, int rlen, char uppercase);
int		ft_putstr(char *s);
int		ft_putptr_rlen(void *ptr);

int		ft_printf(const char *format, ...);


char	*get_next_line(int fd);
char	*get_string(char *str);
char	*read_the_line(char *str);
char	*free_and_null(char *buff1, char *buff2);
size_t	ft_strlen(const char *str);
char	*ft_strchr(const char *str, int c);
char	*ft_strdup(const char *src);
char	*ft_gnl_strjoin(char *buffer, char *content);
char	*ft_strjoin(char const *s1, char const *s2);

#endif