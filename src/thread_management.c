/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:29:17 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/12/20 11:51:32 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	create_threads(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->number_of_philos)
	{
		if (pthread_create(&(args->threads[i++]), NULL, &routine, args) != 0)
			return (THREAD_ERROR);
	}
	return (SUCCESS);
}

int	join_threads(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->number_of_philos)
	{
		if (pthread_join(args->threads[i++], NULL) != 0)
			return (THREAD_ERROR);
	}
	return (SUCCESS);
}
