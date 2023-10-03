/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:58:36 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/10/03 12:00:21 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_global	create_global(t_args *args, pthread *philo, pthread_mutext_t *print_mutex)
{
	t_global global;

	global.args = args;
	global.philo = philo;
	global.print_mutex = print_mutex;
	return (global);
}
void	*routine(void *arg)
{
	int i;
	
	i = *(int *)(arg);
	pthread_mutex_lock(&print_mutex);
	ft_printf("HELLO FROM PHILOSOPHER NUMBER %i!\n", i);
	pthread_mutex_unlock(&print_mutex);
	return NULL;
}

int	main(int argc, char **argv)
{
	t_args			args;
	pthread_t*		philo;
	pthread_mutex_t print_mutex;
	t_global		global;

	if (check_args(argc, argv) == ARG_ERROR)
		return (ARG_ERROR);
	init_args(&args, argc, argv);
	philo = (pthread_t *)malloc(sizeof(pthread_t) * args.number_of_philosophers);
	if (!philo)
		return(MALLOC_ERROR);
	pthread_mutex_init(&print_mutex, NULL);
	global = create_global(&args, philo, &print_mutex);
	if (create_threads(&args, philo) == THREAD_ERROR)
		return (THREAD_ERROR);
	if (join_threads(&args, philo) == THREAD_ERROR)
		return (THREAD_ERROR);
	pthread_mutex_destroy(&print_mutex);
	free(philo);
	return (SUCCESS);
}
