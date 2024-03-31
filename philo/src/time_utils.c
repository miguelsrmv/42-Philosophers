/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 18:15:15 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/03/31 23:08:32 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Gets current time, in milliseconds
size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		write(2, "gettimeofday() error\n", 22);
		return (0);
	}
	return ((size_t)time.tv_sec * 1000 + (size_t)time.tv_usec / 1000);
}

// Gets time-difference between now and start_time, in milliseconds
size_t	get_time_diff(size_t start_time, size_t now)
{
	return (now - start_time);
}

// Re-worked usleep function for more precision
void	ft_usleep(size_t milliseconds)
{
	size_t	start;
	long	ellapsed_time;
	long	remaining_time;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
	{
		ellapsed_time = get_current_time() - start;
		remaining_time = milliseconds - ellapsed_time;
		if (remaining_time > 1000)
			usleep(ellapsed_time / 2);
		else
		{
			while ((get_current_time() - start) < milliseconds)
				;
		}
	}
}