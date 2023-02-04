/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_helpful2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 14:23:48 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/02/02 18:52:37 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_rederct(int *io_infile, int *io_outfile, char *filename, t_token token)
{
	int	o_flag;
	int	*fds;

	o_flag = O_RDONLY;
	if (token & (APPEND | GREAT))
	{
		if (token & APPEND)
			o_flag = O_CREAT | O_RDWR | O_APPEND;
		else
			o_flag = O_CREAT | O_RDWR | O_TRUNC;
		return (*io_outfile = open(filename, o_flag, FILE_PERM));
	}
	if (token & LESS)
		return (*io_infile = open(filename, o_flag, FILE_PERM));
	fds = gc(g_global.gc, malloc(sizeof(int) * 2), TMP);
	if (!fds || herdoc(filename, fds) < 0)
		return (-1);
	return (*io_infile = fds[0]);
}

int herdoc(char *limiter, int *fds)
{
    char    *line;
    int     limiter_size;

    if (!limiter || pipe(fds) == -1)
        return (-1);
    limiter_size = ft_strlen(limiter);
    while (true)
    {
        line = readline("> ");
        if (!line || !ft_memcmp(limiter, line, limiter_size + 1))
			break ;
        gc_adding_adress(g_global.gc, line, TMP);
        write(fds[WIRITE_], line, ft_strlen(line));
		write(fds[WIRITE_], "\n", 1);
    }
    return (close(fds[WIRITE_]), fds[READ_]);
}

char	**adding_wildcard(char **array, char **wild)
{
	char	**ret;
	int		i;
	int		j;

	i = -1;
	j = -1;
	while (array[++i])
		;
	while (wild[++j])
		;
	ret = gc(g_global.gc, malloc(sizeof(char *) * (i + j + 1)), TMP);
	if (!ret)
		return (NULL);
	i = j = -1;
	while (array[++i])
		ret[i] = gc(g_global.gc, ft_strdup(array[i]), TMP);
	while (wild[++j])
		ret[i++] = gc(g_global.gc, ft_strdup(wild[j]), TMP);
	return (ret[i] = NULL, ret);
}

char	**realloc_array(char **array, char *new, int flag)
{
	char	**ret;
	int		i;

	i = -1;
	if (!array)
	{
		ret = gc(g_global.gc, malloc(sizeof(char *) * 2), TMP);
		return (ret[0] = gc(g_global.gc, ft_strdup(new), TMP),\
			ret[1] = NULL, ret);
	}
	if (flag & WILD)
		array = adding_wildcard(array, ft_split(new, 32));
	while (array[++i])
		;
	ret = gc(g_global.gc, malloc(sizeof(char *) * (i + 2)), TMP);
	if (!ret)
		return (NULL);
	i = -1;
	while (array[++i])
		ret[i] = gc(g_global.gc, ft_strdup(array[i]), TMP);
	if (flag & ~WILD)
		ret[i++] = gc(g_global.gc, ft_strdup(new), TMP);
	return (ret[i] = NULL, ret);
}

void    add_cmdexc_back(t_grb **grb, t_cmdexc *new_cmdexc)
{
    if (!(*grb)->head)
        (*grb)->head = new_cmdexc;
    else
    {
        (*grb)->tail->next = new_cmdexc;
        new_cmdexc->prev = (*grb)->tail;
    }
    (*grb)->tail = new_cmdexc;
}