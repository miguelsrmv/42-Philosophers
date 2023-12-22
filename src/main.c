/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:58:36 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/12/22 19:42:38 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_args			arg;

	if (check_args(argc, argv) == ARG_ERROR)
		return (ARG_ERROR);
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
