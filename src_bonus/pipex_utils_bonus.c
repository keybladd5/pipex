/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polmarti <polmarti@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:10:52 by polmarti          #+#    #+#             */
/*   Updated: 2024/01/15 11:10:55 by polmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/pipex_bonus.h"

void	ft_error(int type_error)
{
	if (type_error == 127)
		perror("Error comand");
	else if (type_error == 2)
		perror("Error path");
	else if (type_error == 3)
		perror("Error file");
	else if (type_error == 1)
		perror("Error");
	else if (type_error == 5)
		perror("Error memory");
	else if (type_error == 6)
		perror("permission denied:");
	exit(type_error);
}

void	ft_init_struct(t_pipex *data)
{
	data->pid1 = 0;
	data->pid2 = 0;
	data->middle_pid = 0;
	data->pipefd[0] = 0;
	data->pipefd[1] = 1;
	data->fd = 0;
	data->i = 0;
	data->x = 0;
	data->filename = NULL;
	data->cmd_exec = NULL;
	data->n_cmd = 1;
	data->n_argc = 0;
	data->cmd = NULL;
	data->path = NULL;
	data->error_signal = 0;
}

void	get_path_nd_cmd(char *argv[], char *envp[], t_pipex *data)
{
	data->cmd = ft_split(argv[data->n_cmd], ' ');
	if (!data->cmd)
		ft_error(5);
	while (ft_strncmp("PATH=", envp[data->i], 5) != 0)
	{
		data->i++;
		if (envp[data->i] == NULL)
			ft_error(2);
	}
	data->path = ft_split(envp[data->i], ':');
	if (!data->path)
		ft_error(5);
	data->path[data->x] = \
	ft_substr(data->path[data->x], 5, ft_strlen(data->path[data->x]));
	if (!data->path[data->x])
		ft_error(5);
	data->cmd_exec = ft_strjoin("/", data->cmd[0]);
	if (!data->cmd_exec)
		ft_error(5);
}
void	ft_child_iter(char *argv[], char *envp[], int argc, t_pipex *data)
{
	int i;

	i = data->n_cmd;
	while (data->n_cmd < argc -2)
	{
		pipe(data->pipefd);
		data->n_cmd++;
		data->middle_pid = fork();
		//printf("%d\n", data->middle_pid);
		if (data->middle_pid == 0)
			child(argv, envp, data);
	}
	while(i < argc -2)
	{
		i++;
		wait(NULL);
	}
}

void	exec_cmd(char *argv[], char *envp[], t_pipex *data)
{
	get_path_nd_cmd(argv, envp, data);
	while (data->path[data->x])
	{
		if (data->x > 0)
			free(data->filename);
		data->filename = ft_strjoin(data->path[data->x], data->cmd_exec);
		if (!data->filename)
			ft_error(6);
		if ((execve(data->filename, data->cmd, NULL) == -1))
			data->x++;
		if (data->path[data->x] == NULL)
			ft_error(1);
	}
}
