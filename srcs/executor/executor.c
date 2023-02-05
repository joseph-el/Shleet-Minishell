/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 10:51:00 by aelkhali          #+#    #+#             */
/*   Updated: 2023/02/05 16:47:43 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_cmd(t_cmdexc *cmd_data)
{
	pid_t	p_id;
    int		status;

	if (is_builtins(cmd_data->cmdexc[0], cmd_data->cmdexc + 1))
		return (EXIT_SUCCESS);
	p_id = fork();
	if (p_id == 0)
	{
		if (cmd_data->io_src == -1 || cmd_data->io_dest == -1)
			 return (shleet_error("No such file or directory", NULL, 1), -1);
		dup2(cmd_data->io_dest, 1);
		dup2(cmd_data->io_src, 0);
        exec_cmdline(cmd_data->cmdexc[0], cmd_data->cmdexc);
    }
    if (p_id == -1)
        return (EXIT_FAILURE);
    if (wait(&status) == p_id)
        g_global.status = WEXITSTATUS(status);
	return (EXIT_FAILURE);
}

int	exec_cmdline(char *cmd, char **cmd_args)
{
	ft_execve(cmd, cmd_args);
	shleet_error(cmd, strerror(errno), 1);
	if (errno == ENOENT)
		exit(127);
	if (errno == EACCES)
		exit(126);
	exit(EXIT_FAILURE);
}

int	exec_manager(t_cmdexc *head, int *tmp_fd, int p_fds[2], int flag)
{
	pid_t	p_id;
	int		fd_write;
	int		fd_read;

	p_id = fork();
	if (flag == 0 && !p_id)
	{
		if (head->io_src == -1 || head->io_dest == -1)
			 return (shleet_error("No such file or directory", NULL, 1), -1);
		close(p_fds[0]);
		dup2(head->io_src, 0);
		dup2(p_fds[1], 1);
		if (is_builtins(head->cmdexc[0], head->cmdexc + 1))
			exit (EXIT_SUCCESS);
		exec_cmdline(head->cmdexc[0], head->cmdexc);
	}
	else if (flag == 1 && !p_id)
	{
		if (head->io_src == -1 || head->io_dest == -1)
			 return (shleet_error("No such file or directory", NULL, 1), -1);
		fd_read = *tmp_fd;
		fd_write = p_fds[1];
		if (head->io_src != 0)
			fd_read = head->io_src;
		if (head->io_dest != 1)
			fd_write = head->io_dest;
		dup2(fd_write, 1);
		dup2(fd_read, 0);
		if (is_builtins(head->cmdexc[0], head->cmdexc + 1))
			exit (EXIT_SUCCESS);
		exec_cmdline(head->cmdexc[0], head->cmdexc);
	}
	else if (flag == 2 && !p_id)
	{
		if (head->io_src == -1 || head->io_dest == -1)
			 return (shleet_error("No such file or directory", NULL, 1), -1);
		dup2(head->io_dest, 1);
		dup2(*tmp_fd, 0);
		if (head->io_src != 0)
			dup2(head->io_src, 0);
		if (is_builtins(head->cmdexc[0], head->cmdexc + 1))
			exit (EXIT_SUCCESS);
		exec_cmdline(head->cmdexc[0], head->cmdexc);
	}
	close(*tmp_fd);
	*tmp_fd = dup(p_fds[0]);
	return(EXIT_SUCCESS);
}

void	exec_pipline(t_cmdexc *head_grp)
{
	int	*tmp_fd;
	int	status;
	int	p_fds[2];

	tmp_fd = gc(g_global.gc, malloc(sizeof(int)), TMP);
	if (!head_grp || !tmp_fd)
		return ;
	while (head_grp)
	{
		pipe(p_fds);
		if (!head_grp->prev && head_grp->node_type & NODE_CMDEXC)
			exec_manager(head_grp, tmp_fd, p_fds, 0);
		else if (!head_grp->next && head_grp->node_type & NODE_CMDEXC)
			exec_manager(head_grp, tmp_fd, p_fds, 2);
		else if (head_grp->node_type & NODE_CMDEXC)
			exec_manager(head_grp, tmp_fd, p_fds, 1);
		close(p_fds[0]);
		close(p_fds[1]);
		head_grp = head_grp->next;
	}
	close(*tmp_fd);
	while (wait(&status) != -1)
		;
	g_global.status = WEXITSTATUS(g_global.status);
}

int	executor(t_expander *exp_list)
{
	t_exp	*head;

	head = exp_list->head;
	if (!exp_list || !exp_list->head || !exp_list->head->grb || !exp_list->head->grb->head || !exp_list->head->grb->head->cmdexc)
		return (EXIT_FAILURE);
	while (head && head->nature != NODE_ENDOFCMD)
	{
		if (head->next && head->next->nature & (NODE_AND | NODE_OR))
		{
			logical_manager(head->next);
			head = head->next->next->next;
		}
		else if (head && head->nature & NODE_CMDEXC)
		{
			group_manager(head->grb->head);
			head = head->next;
		}
		else
			head = head->next;
	}
	return (EXIT_SUCCESS);
}
