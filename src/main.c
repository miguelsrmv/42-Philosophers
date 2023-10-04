/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:58:36 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/10/04 23:04:33 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine(void *arg)
{
	int	i;

	i = *(((t_args *)arg)->philo_id);
	sleep(3 * i);
	ft_printf("HELLO FROM PHILOSOPHER NUMBER %i!\n", i);
	// free (((t_args *)arg)->philo_id); is missing!
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_args			args;

	if (check_args(argc, argv) == ARG_ERROR)
		return (ARG_ERROR);
	init_args(&args, argc, argv);
	args.philo = (pthread_t *)malloc(sizeof(pthread_t) * args.number_of_philos);
	if (!args.philo)
		return (MALLOC_ERROR);
	if (create_threads(&args) == THREAD_ERROR)
		return (THREAD_ERROR);
	if (join_threads(&args) == THREAD_ERROR)
		return (THREAD_ERROR);
	pthread_mutex_destroy(&(args.print_mutex));
	free(args.philo);
	return (SUCCESS);
}
