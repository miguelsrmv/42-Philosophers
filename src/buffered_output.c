/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffered_output.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 09:41:26 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/12/22 19:42:23 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

enum e_ErrorCode	add_to_buffered_output(t_args *arg, char *string)
{
	t_list	*new_node;

	new_node = ft_lstnew((void *)string);
	if (!new_node)
		return (MALLOC_ERROR);
	if (!arg->output)
	{
		arg->output = new_node;
		arg->end = arg->output;
	}
	else
	{
		arg->end->next = new_node;
		arg->end = arg->end->next;
	}
	return (SUCCESS);
}
