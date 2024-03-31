/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 16:07:26 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/03/31 16:19:14 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_philo(t_philos philo)
{
	printf(
		"Philo number %i will first get fork number %i and then fork number %i\n",
		philo.philo_id,
		philo.first_fork->fork_id,
		philo.second_fork->fork_id
		);
}
