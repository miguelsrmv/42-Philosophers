/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_cases.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 22:05:50 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/03/31 23:04:20 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Special cases:
/// #1 If simulation ends with 0 meals taken
/// #2 If there are no philos
/// #3 If there is only one philo
bool	is_special_case(int argc, char **argv)
{
	if (argc == 6 && (ft_atoi(argv[5]) == 0))
		return (true);
	else if (ft_atoi(argv[1]) == 0)
		return (true);
	else if (ft_atoi(argv[1]) == 1)
	{
		one_philo_sim(ft_atoi(argv[2]));
		return (true);
	}
	return (false);
}

void	one_philo_sim(int time_to_die)
{
	printf("0	1 has taken a fork\n");
	ft_usleep(time_to_die);
	printf("%i	1 died\n", time_to_die);
}
