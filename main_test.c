/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polmarti <polmarti@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 17:21:11 by polmarti          #+#    #+#             */
/*   Updated: 2024/01/08 17:21:13 by polmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <libc.h>
#include "libft/libft.h"
#include <fcntl.h>
#include <sys/wait.h>

//REVISAR si el path existe, y errores con sus salidas
void	exec_cmd(char *argv[], char *envp[], int n_cmd)
{
	char **cmd;
	char **path;
	char *filename;
	char *cmd_exec;
	int i;
	int x;

	i = 0;
	x = 0;
	filename = NULL;
	cmd = ft_split(argv[n_cmd], ' ');
	while (envp[i])
	{
		if (ft_strncmp("PATH=", envp[i], 5) != 0)
			i++;
		else
			break;
	}
	path = ft_split(envp[i], ':');
	path[x] = ft_substr(path[x], 5, ft_strlen(path[x]));
	cmd_exec = ft_strjoin("/", cmd[0]); 
	while(path[x])
	{
		filename = ft_strjoin(path[x], cmd_exec);
		if ((execve(filename, cmd, NULL) == -1))
			x++;
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	if (argc != 5)
		return (1);
	int pipefd[2];
	pipe(pipefd);
	int pid1 = fork();
	if (pid1 == 0)
	{
		close(pipefd[0]);
		if (access(argv[1], R_OK) == -1)
			perror("Error acces");
		int fd = open(argv[1], O_RDONLY);
		dup2(fd, 0);
		close(fd);
		dup2(pipefd[1], 1);
		close(pipefd[1]);
		exec_cmd(argv, envp, 2);
	}
	wait(NULL);
	int pid2 = fork();
	if (pid2 == 0)
	{
		close(pipefd[1]);
		if (access(argv[4], R_OK) == -1)
			perror("Error acces");
		int fd2 = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644); 
		dup2(fd2, 1);
		close(fd2);
		dup2(pipefd[0], 0);
		close(pipefd[0]);
		exec_cmd(argv, envp, 3);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	exit(1);
}

/*Check this https://csnotes.medium.com/pipex-tutorial-42-project-4469f5dd5901*/

