/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polmarti <polmarti@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:10:39 by polmarti          #+#    #+#             */
/*   Updated: 2024/01/15 11:10:40 by polmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/pipex.h"

static void	first_child(char *argv[], char *envp[], t_pipex *data)
{
	close(data->pipefd[0]);
	data->fd = open(argv[1], O_RDONLY);
	if (data->fd < 0)
	{
		close(data->pipefd[1]);
		ft_error(3);
	}
	dup2(data->fd, 0);
	close(data->fd);
	dup2(data->pipefd[1], 1);
	close(data->pipefd[1]);
	data->n_cmd = 2;
	exec_cmd(argv, envp, data);
}

static void	second_child(char *argv[], char *envp[], t_pipex *data, int argc)
{
	close(data->pipefd[1]);
	data->fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (data->fd == -1)
		ft_error(1);
	dup2(data->fd, 1);
	close(data->fd);
	dup2(data->pipefd[0], 0);
	close(data->pipefd[0]);
	data->n_cmd = 3;
	exec_cmd(argv, envp, data);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	data;
	int		status;

	if (argc <= 4)
		ft_error(1);
	ft_init_struct(&data);
	pipe(data.pipefd);
	data.pid1 = fork();
	if (data.pid1 == 0)
		first_child(argv, envp, &data);
	wait(NULL);
	data.pid2 = fork();
	if (data.pid2 == 0)
		second_child(argv, envp, &data, argc);
	close(data.pipefd[0]);
	close(data.pipefd[1]);
	wait(&status);
	if (WIFEXITED(status) != 0)
		exit(WEXITSTATUS(status));
	exit(1);
}
