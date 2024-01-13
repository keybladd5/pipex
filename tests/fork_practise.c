/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EXEC_SO_LONG.C                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polmarti <polmarti@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 18:03:32 by polmarti          #+#    #+#             */
/*   Updated: 2024/01/02 18:03:36 by polmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int	main(void)
{
	int id = fork();
	int n;
	int id_child;
	if (id == 0) //El 0 solo se asigna al proceso que se obtiene al llamar a la funcion fork
		n = 1;
	else
		n = 6;
	if (id != 0)
		id_child = wait(NULL); //una vez acabado el proceso hijo wait devuelve el PID del propio
	for(int i = n; i < n + 5; i++)
		printf("%d ", i);
	if (id == 0)
		printf("\nEl proceso hijo ha acabado\n");
	if (id != 0)
	{
		printf("\nChild pid = %d\n", id_child);
		printf("Parent pid = %d\n", getpid());
		printf("\nEl proceso padre ha acabado\n");
	}
	return (0);
}
