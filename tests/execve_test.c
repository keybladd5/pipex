/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polmarti <polmarti@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 17:13:51 by polmarti          #+#    #+#             */
/*   Updated: 2024/01/09 17:13:53 by polmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include <libc.h>
#include "libft/libft.h"

int	main(int argc, char *argv[])
{

	char *arg = ft_strjoin("/bin/", argv[1]);
	if ((execve(arg, argv+1, NULL) == -1))
		ft_printf("ERROR\n");
	return (0);
}