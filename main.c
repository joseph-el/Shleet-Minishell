/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 14:02:20 by yoel-idr          #+#    #+#             */
/*   Updated: 2023/02/02 19:56:42 by yoel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*get_next_line(int fd);

# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <paths.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>
# include <stddef.h>
# include <string.h>

# define FILE_PERM 0664
# define WIRITE_ 1
# define READ_ 0

// int herdoc(char *limiter, int *fds)
// {
//     char    *line;
//     int     limiter_size;

//     if (!limiter || pipe(fds) == -1)
//         return (-1);
//     limiter_size = strlen(limiter);

// 	while (1)
// 	{
//         line = get_next_line(0);
// 		if (!strncmp(limiter, line, strlen(limiter)))
// 			break;
//         write(fds[WIRITE_], line, strlen(line));
// 		write(fds[WIRITE_], "\n", 1);		
// 	}
//     return (close(fds[WIRITE_]), fds[READ_]);
// }

// typedef struct s_cmd
// {
// 	int io_dest;
// 	int io_src;
// 	char *cmd;
// 	struct s_cmd *next;
// 	struct s_cmd *prev;
// }			t_cmd;

// # define RIGHT_SIDE 1
// # define LEFT_SIDE 2
// # define FD_TMP 4





// pid_t   run_pipe(t_cmd *obj, int fds[2], int fd_tmp, int fd_flag)
// {
//     pid_t   pid;
//     int     fd_write;
//     int     fd_read;
    
//     if (fd_flag & LEFT_SIDE)
//     {
//         fd_write = fds[1];
//         fd_read = obj->io_src;
//         if (fd_flag & FD_TMP)
//             fd_read = fd_tmp;
//     }
//     if (fd_flag & RIGHT_SIDE)
//     {
//         fd_write = obj->io_dest;
//         fd_read = fd_tmp;
//         if (fd_flag & FD_TMP)
//             fd_write = fds[1];
//     }
//     pid = fork();
//     if (pid == 0)
//     {
//         dup2(fd_write, 1);
//         dup2(fd_read, 0);
// 		write(fd_write, "Hello World iam here right now!", strlen("Hello World iam here right now!"));
//     }
// 	close(fd_tmp);
// 	fd_tmp = dup(fds[0]);
// 	char *test = get_next_line(fd_tmp);
// 	printf("this is ==> |%s|\n", test);
//     return (pid);
// }

// void ft_pipes(t_cmd *left, t_cmd *right, int fd_tmp)
// {
//     pid_t   process[2];
//     int     fds[2];
//     int     status;
//     int     fd_flag;

// 	fd_flag = LEFT_SIDE | FD_TMP;
// 	if (left->prev == 0x0)
//         fd_flag = LEFT_SIDE;

//     process[0] = run_pipe(left, fds, fd_tmp, fd_flag);
	
// 	fd_flag = RIGHT_SIDE;
	
//     if (right->next != 0X0)
//         fd_flag = RIGHT_SIDE | FD_TMP;

//     process[1] = run_pipe(right, fds, fd_tmp, fd_flag);
// 	close(fds[1]);
// 	close(fds[0]);
// 	while (wait(&status) != -1);
// 	printf("status |%d| ==>\n",WEXITSTATUS(status));
// }






int main(int ac, char **av)
{
	// t_cmd 	*cmd1 = malloc(sizeof(t_cmd));
	// t_cmd 	*cmd2 = malloc(sizeof(t_cmd));
	// t_cmd 	*cmd3 = malloc(sizeof(t_cmd));

	int eee;

	dup2(eee, 0);
	execve("/bin/ls", NULL, NULL);

	return 0;
	// // Link
	// cmd1->prev = 0x0;
	// cmd1->next = cmd2;
	// cmd2->prev = cmd1;
	// cmd2->next = cmd3;
	// cmd3->prev = cmd2;
	// cmd3->next = 0x0;
	
	// cmd1->io_dest = 1;
	// cmd1->io_src = open("Makefile", O_RDONLY);
	// cmd1->cmd = strdup("/bin/ls");
	
	// cmd2->io_src = 0;
	// cmd2->io_dest = 1;
	// cmd2->cmd = strdup("/bin/ls");

	// cmd3->io_dest = open("test.swift", O_CREAT | O_TRUNC, 644);
	// cmd3->io_src = 0;
	// cmd3->cmd = strdup("/bin/ls");

	// int		fd_tmp;

	// ft_pipes(cmd1, cmd2, fd_tmp);
	// ft_pipes(cmd2, cmd3, fd_tmp);
	// close(fd_tmp);
	return (0);
}