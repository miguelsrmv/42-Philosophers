/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:58:36 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/03/31 11:57:25 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_args			arg;

	if (check_args(argc, argv) == ARG_ERROR)
		return (ARG_ERROR);
	if (argc == 6 && )
	{
		if (ft_atoi(argv[5]) == 0)
			return (SUCCESS);
	}
	if (init_args(&arg, argc, argv) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	if (init_mutexes(&arg) == MUTEX_ERROR)
		return (MUTEX_ERROR);
	if (create_threads(&arg) == THREAD_ERROR)
		return (THREAD_ERROR);
	if (join_threads(&arg) == THREAD_ERROR)
		return (THREAD_ERROR);
	clear_args(&arg);
	return (SUCCESS);
}
