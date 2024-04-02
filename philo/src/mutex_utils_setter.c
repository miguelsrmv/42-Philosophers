/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils_setter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 22:41:10 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/04/03 00:22:44 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Sets mutex-protected bool to target value
void	set_bool(pthread_mutex_t *mutex, bool *target, bool value)
{
	pthread_mutex_lock(mutex);
	*target = value;
	pthread_mutex_unlock(mutex);
}

// Sets mutex-protected int to target value
void	set_int(pthread_mutex_t *mutex, int *target, int value)
{
	pthread_mutex_lock(mutex);
	*target = value;
	pthread_mutex_unlock(mutex);
}

// Sets mutex-protected size_t to target value
void	set_size_t(pthread_mutex_t *mutex, size_t *target, size_t value)
{
	pthread_mutex_lock(mutex);
	*target = value;
	pthread_mutex_unlock(mutex);
}
