/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_fork.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polmarti <polmarti@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 19:04:01 by polmarti          #+#    #+#             */
/*   Updated: 2024/01/03 19:04:04 by polmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <errno.h>

int	main()
{
	int id1 = fork();
	int id2 = fork();
	if (id1 == 0)
	{
		if (id2 == 0)
			printf("Process child by child(y) process\n"); //4
		else 
			printf("Process child(x) \n"); //3
	}
	else 
	{
		if (id2 == 0)
			printf("Process second child(z)\n");//2 
		else
			printf("Parent process\n"); //1 primer proceso
	}
	printf("im end now and ill be my next child\n\n");
	return (0);
}
