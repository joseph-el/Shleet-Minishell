/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 14:33:24 by aelkhali          #+#    #+#             */
/*   Updated: 2023/02/05 11:57:16 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "minishell.h"

int	pipes_counter(t_cmdexc *head_grp)
{
	int pipes;

	pipes = 0;
	if (!head_grp)
		return (pipes);
	while (head_grp)
	{
		if (head_grp->node_type & NODE_PIPE)
			pipes++;
		head_grp = head_grp->next;
	}
	return (pipes);
}

void	logical_manager(t_exp *logical_node)
{
	if (!logical_node)
		return ;
	group_manager(logical_node->prev->grb->head);
	if (logical_node->nature & NODE_AND)
	{
		if (WIFEXITED(g_global.status) && WEXITSTATUS(g_global.status) == 0)
			group_manager(logical_node->next->grb->head);
	}
	if (logical_node->nature & NODE_OR)
	{
		if (WIFEXITED(g_global.status) && WEXITSTATUS(g_global.status) != 0)
			group_manager(logical_node->next->grb->head);
	}
}

void	group_manager(t_cmdexc *head_grp)
{
	if (!head_grp)
		return ;
	if (pipes_counter(head_grp))
		exec_pipline(head_grp);
	else
		exec_cmd(head_grp);
}

bool    is_builtins(char *args, char **list_args)
{
	if (!ft_strncmp(args, "echo", ft_strlen("echo")))
		return (shleet_echo(list_args), true);
	else if (!ft_strncmp(args, "cd", ft_strlen("cd")))
		return (shleet_cd(list_args), true);
	else if (!ft_strncmp(args, "export", ft_strlen("export")))
		return (shleet_export(list_args), true);
	else if (!ft_strncmp(args, "env", ft_strlen("env")))
		return (shleet_env(list_args), true);
	else if (!ft_strncmp(args, "unset", ft_strlen("unset")))
		return (shleet_unset(list_args), true);
	else if (!ft_strncmp(args, "exit", ft_strlen("exit")))
		return (shleet_exit(list_args), true); 
	else if (!ft_strncmp(args, "pwd", ft_strlen("pwd")))
		return (shleet_pwd(list_args), true);
	return (false);
}
