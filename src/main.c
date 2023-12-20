/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:58:36 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/12/20 09:48:09 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_args			args;

	if (check_args(argc, argv) == ARG_ERROR)
		return (ARG_ERROR);
	if (init_args(&args, argc, argv) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	if (create_threads(&args) == THREAD_ERROR)
		return (THREAD_ERROR);
	if (join_threads(&args) == THREAD_ERROR)
		return (THREAD_ERROR);
	clear_args(&args);
	return (SUCCESS);
}
