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


int	main(int argc, char *argv[], char *envp[])
{
	if (argc != 5)
		return (1);
	int pipefd[2];
	pipe(pipefd);
	int pid1 = fork();
	if (pid1 == 0)
	{
		int fd = open(argv[1], O_RDONLY);
		dup2(fd, 0);
		close(fd);
		dup2(pipefd[1], 1);
		close(pipefd[1]);
		close(pipefd[0]);
		char *arg = ft_strjoin("/bin/", argv[2]);
		if ((execve(arg, argv+2, NULL) == -1))
			perror("ERROR en EXECVE hijo\n");
	}
	wait(NULL);
	int pid2 = fork();
	if (pid2 == 0)
	{
		int fd2 = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644); 
		dup2(fd2, 1);
		close(fd2);
		dup2(pipefd[0], 0);
		close(pipefd[0]);
		close(pipefd[1]);
		char *arg2 = ft_strjoin("/usr/bin/", argv[3]);
		if ((execve(arg2, argv+3, NULL) == -1))
			perror("ERROR en EXECVE padre\n");
	}
	close(pipefd[0]);
	close(pipefd[1]);
	exit(1);
}

/*Check this https://csnotes.medium.com/pipex-tutorial-42-project-4469f5dd5901*/

