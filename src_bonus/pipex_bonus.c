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

#include "../inc_bonus/pipex_bonus.h"

static void	first_child(char *argv[], char *envp[], t_pipex *data)
{
	close(data->pipefd[0]);
	data->fd = open(argv[1], O_RDONLY);
	if (data->fd < 0)
		ft_error(3);
	dup2(data->fd, 0);
	close(data->fd);
	dup2(data->pipefd[1], 1);
	close(data->pipefd[1]);
	data->n_cmd = 2;
	exec_cmd(argv, envp, data);
}
void	middle_child(char *argv[], char *envp[], t_pipex *data)
{
	//if (data->n_cmd == 3)
	dup2(data->pipefd[0], 0);
	//else
		//dup2(data->iter_pipefd[0], 0);
	close(data->pipefd[0]);
	//close (data->iter_pipefd[0]);
	//dup2(data->iter_pipefd[1], 1);
	//close(data->iter_pipefd[1]);
	dup2(data->pipefd[1], 1);
	close(data->pipefd[1]);
	exec_cmd(argv, envp, data);
}

static void	last_child(char *argv[], char *envp[], t_pipex *data)
{
	close(data->pipefd[1]);
	data->fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->fd < 0)
		ft_error(3);
	dup2(data->fd, 1);
	close(data->fd);
	dup2(data->pipefd[0], 0);
	close(data->pipefd[0]);
	data->n_cmd = data->n_argc - 2;
	exec_cmd(argv, envp, data);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	data;

	if (argc < 5)
		ft_error(4);
	ft_init_struct(&data);
	data.n_argc = argc;
	pipe(data.pipefd);
	data.pid1 = fork();
	if (data.pid1 == 0)
		first_child(argv, envp, &data);
	wait(NULL);
	ft_iter_cmds(argv, envp, argc, &data);
	data.pid2 = fork();
	if (data.pid2 == 0)
		last_child(argv, envp, &data);
	close(data.pipefd[0]);
	close(data.pipefd[1]);
	exit(0);
}
