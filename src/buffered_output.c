/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffered_output.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 09:41:26 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/12/30 16:56:29 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

enum e_ErrorCode	add_to_buffered_output(t_args *arg, char *string)
{
	t_list	*new_node;

	new_node = ft_lstnew((void *)string);
	if (!new_node)
		return (MALLOC_ERROR);
	pthread_mutex_lock(&arg->linked_list_mutex);
	if (!arg->output)
	{
		arg->output = new_node;
		arg->output_end = new_node;
		arg->output_head = new_node;
	}
	else
	{
		arg->output_end->next = new_node;
		arg->output_end = arg->output_end->next;
	}
	pthread_mutex_unlock(&arg->linked_list_mutex);
	return (SUCCESS);
}
