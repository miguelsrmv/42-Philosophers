/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 09:33:22 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/03/31 23:51:56 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Checks for correct arg usage
t_ErrorCode	check_args(int argc, char **argv)
{
	if (is_argc_inadequate(argc) == true)
		return (ARG_ERROR);
	if (arg_has_non_digit_chars(argv) == true)
		return (ARG_ERROR);
	if (is_arg_larger_than_int(argv) == true)
		return (ARG_ERROR);
	return (SUCCESS);
}

// Checks if argc is correct
bool	is_argc_inadequate(int argc)
{
	if (argc < 5 || argc > 6)
	{
		ft_printf(ARG_MESSAGE);
		return (true);
	}
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
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j++]))
			{
				ft_printf(ARG_MESSAGE);
				return (true);
			}
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
/// #1 If simulation ends with 0 meals taken
/// #2 If there are no philos
bool	is_special_case(int argc, char **argv)
{
	if (argc == 6 && (ft_atoi(argv[5]) == 0))
		return (true);
	else if (ft_atoi(argv[1]) == 0)
		return (true);
	return (false);
}
