/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 14:58:23 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/02/12 01:15:38 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	destroyer(char **arr)
{
	int	index;

	if (!arr)
		return ;
	index = 0;
	while (arr[index])
		free(arr[index++]);
	free(arr);
}

static char	*get_path(char *cmdline)
{
	char	**path;
	char	*p_cmd;
	int		i;

	if (ft_strchr(cmdline, '/'))
		return (cmdline);
	p_cmd = find_environment(g_global.envp, "PATH")->content;
	if (!p_cmd)
		return (NULL);
	cmdline = gc(g_global.gc, ft_strjoin("/", cmdline), TMP);
	path = ft_split(p_cmd, ':');
	i = 0;
	while (path && path[i])
	{
		p_cmd = gc(g_global.gc, ft_strjoin(path[i], cmdline), TMP);
		if (!access(p_cmd, X_OK))
			return (destroyer(path), p_cmd);
		i++;
	}
	return (NULL);
}

int	ft_execve(char *cmd, char **cmd_argument)
{
	char		*p_cmd;
	char		**env;
	struct stat	s_stat;

	p_cmd = get_path(cmd);
	if (!p_cmd)
		return (shleet_error(cmd, "command not found", 1), exit(127), -1);
	stat(p_cmd, &s_stat);
	if (S_ISDIR(s_stat.st_mode))
		return (shleet_error(p_cmd, strerror(EISDIR), 1), exit(126), -1);
	env = export_array(g_global.envp);
	execve(p_cmd, cmd_argument, env);
	return (-1);
}
