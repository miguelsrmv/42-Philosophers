/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:29:17 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/12/21 19:10:23 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	create_threads(t_args *arg)
{
	int	i;

	i = 0;
	while (i < arg->number_of_philos)
	{
		if (pthread_create(&(arg->threads[i++]), NULL, &routine, arg) != 0)
		{
			clear_args(arg);
			return (THREAD_ERROR);
		}
	}
	return (SUCCESS);
}

int	join_threads(t_args *arg)
{
	int	i;

	i = 0;
	while (i < arg->number_of_philos)
	{
		if (pthread_join(arg->threads[i++], NULL) != 0)
		{
			clear_args(arg);
			return (THREAD_ERROR);
		}
	}
	return (SUCCESS);
}
