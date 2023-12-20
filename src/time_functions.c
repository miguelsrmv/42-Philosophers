/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 10:37:15 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/12/20 21:58:05 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	get_current_time(void)
{
	struct timeval	start_time;
	struct timezone	time_zone;

	gettimeofday(&start_time, &time_zone);
	return(start_time.tv_sec * 10000);
}

long long	get_time_diff(long long start_time, long long end_time)
{
	long long	time_diff;

	time_diff = end_time - start_time;
	return (time_diff);
}
