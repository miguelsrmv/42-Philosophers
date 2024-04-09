/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   warning.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 00:51:53 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/04/09 21:44:50 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	warning(char **argv)
{
	int	number_of_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;

	number_of_philos = ft_atoi(argv[NUMBER_OF_PHILOSOPHERS]);
	time_to_die = ft_atoi(argv[TIME_TO_DIE]);
	time_to_eat = ft_atoi(argv[TIME_TO_EAT]);
	time_to_sleep = ft_atoi(argv[TIME_TO_SLEEP]);
	if (number_of_philos > 200)
		printf(PHILO_NO_MESSAGE);
	if (time_to_die < 60 || time_to_eat < 60 || time_to_sleep < 60)
		printf(TIME_ERROR_MESSAGE);
}
