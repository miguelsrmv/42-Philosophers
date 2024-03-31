/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:58:36 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/03/31 18:07:26 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_table			table;

	if (check_args(argc, argv) == ARG_ERROR)
		return (ARG_ERROR);
	if (argc == 6 && (ft_atoi(argv[5]) == 0))
		return (SUCCESS);
	if (init_table(&table, argc, argv) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	if (init_mutexes(&table) == MUTEX_ERROR)
		return (MUTEX_ERROR);
	if (init_threads(&table) == THREAD_ERROR)
		return (THREAD_ERROR);
	clean_data(&table);
	return (SUCCESS);
}
