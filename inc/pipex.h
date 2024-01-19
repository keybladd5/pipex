/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polmarti <polmarti@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:03:44 by polmarti          #+#    #+#             */
/*   Updated: 2024/01/15 11:03:46 by polmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "../libft/libft.h"
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/errno.h>

typedef struct s_pipex
{
	pid_t	pid1;
	pid_t	pid2;
	int		pipefd[2];
	int		fd;
	int		i;
	int		x;
	char	*filename;
	char	*cmd_exec;
	int		n_cmd;
	char	**cmd;
	char	**path;
	int		error_signal;
}	t_pipex;

void	ft_error(int type_error);

void	ft_init_struct(t_pipex *data);

void	get_path_nd_cmd(char *argv[], char *envp[], t_pipex *data);

void	exec_cmd(char *argv[], char *envp[], t_pipex *data);

void	exec_cmd(char *argv[], char *envp[], t_pipex *data);

#endif