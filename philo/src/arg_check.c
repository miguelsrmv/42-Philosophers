/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 09:33:22 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/04/24 16:12:50 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Checks for correct arg usage
/// Args must be positive INTs and cannot have non-digit characters
/// "Usage: ./philo [number_of_philosophers] [time_to_die]
/// [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]
/// (optional)"
t_ErrorCode	check_args(int argc, char **argv)
{
	if (is_argc_inadequate(argc)
		|| arg_has_non_digit_chars(argv)
		|| is_arg_larger_than_int(argv))
	{
		printf(ARG_MESSAGE);
		return (ARG_ERROR);
	}
	warning(argv);
	return (SUCCESS);
}

// Checks if argc is correct
bool	is_argc_inadequate(int argc)
{
	if (argc < 5 || argc > 6)
		return (true);
	return (false);
}

// Checks if there are non-digit chars in args
bool	arg_has_non_digit_chars(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		if (!ft_strlen(argv[i]))
			return (true);
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j++]))
				return (true);
		}
		i++;
	}
	return (false);
}

// Checks if all args are lower than INT_MAX
bool	is_arg_larger_than_int(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (ft_strlen(argv[i]) > 10)
			return (true);
		if (ft_atol(argv[i]) > INT_MAX)
			return (true);
		i++;
	}
	return (false);
}

// Special cases:
/// #1 If simulation ends with 0 meals taken	Simulation won't run
/// #2 If there are no philos					Simulation won't run
/// #3 If there is just 1 philo					One_philo_simulation
bool	is_special_case(int argc, char **argv)
{
	if (argc == 6
		&& (ft_atoi(argv[NUMBER_OF_TIMES_EACH_PHILOSOPHER_MUST_EAT]) == 0))
		return (true);
	else if (ft_atoi(argv[NUMBER_OF_PHILOSOPHERS]) == 0)
		return (true);
	else if (ft_atoi(argv[NUMBER_OF_PHILOSOPHERS]) == 1)
	{
		one_philo_simulation(ft_atoi(argv[TIME_TO_DIE]));
		return (true);
	}
	return (false);
}
