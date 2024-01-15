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
	if (!cmd)
		exit(1);
	while (ft_strncmp("PATH=", envp[i], 5) != 0)
	{
		i++;
		if (envp[i] == NULL)
		{
			perror("Deleted PATH");
			exit(1);
		}
	}
	path = ft_split(envp[i], ':');
	if (!path)
		exit(1);
	path[x] = ft_substr(path[x], 5, ft_strlen(path[x]));
	if (!path[x])
		exit(1);
	cmd_exec = ft_strjoin("/", cmd[0]);
	if (!cmd_exec)
		exit(1);
	while(path[x])
	{
		if (x > 0)
			free(filename);
		filename = ft_strjoin_s(path[x], cmd_exec);
		if (!filename)
			exit(1);
		if ((execve(filename, cmd, NULL) == -1))
			x++;
		if (path[x] == NULL)
		{
			perror("Error comand");
			exit(1);
		}
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
		int fd = open(argv[1], O_RDONLY);
		if (fd < 0)
		{
			perror("File ERROR");
			exit(1);
		}
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
		int fd2 = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644); 
		dup2(fd2, 1);
		close(fd2);
		dup2(pipefd[0], 0);
		close(pipefd[0]);
		exec_cmd(argv, envp, 3);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	exit(0);
}

/*Check this https://csnotes.medium.com/pipex-tutorial-42-project-4469f5dd5901*/

