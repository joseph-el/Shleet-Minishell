/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libtools.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 23:27:32 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/02/11 22:54:24 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBTOOLS_H
# define LIBTOOLS_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

int		ft_isalnum(int c);
int		ft_isdigit(int c);
int		ft_isspace(int c);
int		ft_isalpha(int c);
int		ft_atoi(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
int		ft_strcmp(char *s1, char *s2);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t len);
void	*ft_memset(void *str, int c, size_t n);
void	ft_putstr_fd(char *s, int fd);

char	*ft_strchr(const char *str, int c);
char	*ft_strdup(const char *s1);
char	*ft_strndup(char *src, int len);
char	*ft_itoa(int n);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);

size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlen(const char *str);

#endif
