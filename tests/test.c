/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polmarti <polmarti@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 19:38:16 by polmarti          #+#    #+#             */
/*   Updated: 2024/01/13 19:38:17 by polmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
	int fd[2];
	pid_t pidC;
	char buf[10];
	pipe(fd);
	pidC = fork();
	switch(pidC)
	{
		case 0:
			close(fd[0]);
			write(fd[1], "01234", 5);
			close(fd[1]);
			exit(0);
			break;
		case -1:
			break;
		default:
			close(fd[1]);
			read(fd[0], buf, sizeof(buf));
			printf("Padre lee %s\n", buf);
			close(fd[0]);
			break;
	}
	return (0);
}