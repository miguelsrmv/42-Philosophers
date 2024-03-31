/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 17:48:12 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/12/29 18:15:35 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_help(t_args *arg, int thread_id, int epoch_time, char *string)
{
	pthread_mutex_lock(&arg->print_mutex);
	ft_printf("Philo %i (%i): %s\n", thread_id + 1,
		get_time_diff(epoch_time, get_current_time()), string);
	pthread_mutex_unlock(&arg->print_mutex);
}
