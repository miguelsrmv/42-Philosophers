/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 09:33:22 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/10/04 23:04:52 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_args(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
	{
		ft_printf(ARG_MESSAGE);
		return (ARG_ERROR);
	}
	i = 1;
	while (argv[i] && *argv[i] != 0)
	{
		if (!ft_isdigit(*argv[i++]))
		{
			ft_printf(ARG_MESSAGE);
			return (ARG_ERROR);
		}
	}
	return (SUCCESS);
}

void	init_args(t_args *args, int argc, char **argv)
{
	args->number_of_philos = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		args->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		args->number_of_times_each_philosopher_must_eat = 0;
	pthread_mutex_init(&(args->print_mutex), NULL);
}

// Helper function, delete at end
void	print_args(t_args *args)
{
	ft_printf("1. Number of Philosophers: %i\n", args->number_of_philos);
	ft_printf("2. Time to die: %i\n", args->time_to_die);
	ft_printf("3. Time_to_eat: %i\n", args->time_to_eat);
	ft_printf("4. Time_to_sleep: %i\n", args->time_to_sleep);
	ft_printf("5. Number of times each philosopher must eat: ");
	ft_printf("%i\n\n\n", args->number_of_times_each_philosopher_must_eat);
}
