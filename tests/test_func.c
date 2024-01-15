/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polmarti <polmarti@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 18:39:48 by polmarti          #+#    #+#             */
/*   Updated: 2024/01/14 18:39:50 by polmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

void	exec_cmd(char *argv[], char *envp[])
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
	cmd = ft_split(argv[1], ' ');
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
		if (access(filename, X_OK) == -1 && path[x] == NULL)
		{
			perror("Error COMAND");
		}
	}
}

int main(int argc, char *argv[], char *envp[])
{
	if (argc != 2)
		return 1;
	//for (int i = 0; envp[i] != NULL; i++)
		//printf("%s\n", envp[i]);
	exec_cmd(argv, envp);
	return (0);
}