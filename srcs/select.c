/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 16:43:19 by ezonda            #+#    #+#             */
/*   Updated: 2019/07/01 22:51:17 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

int		remove_selection(t_var *data, int index)
{
	while (data->selected[index])
	{
		data->selected[index] = data->selected[index + 1];
		index++;
	}
	data->selected[index] = NULL;
	return (0);
}

int		manage_selection(t_var *data)
{
	int i;

	i = 0;
	while (data->selected[i])
	{
		if (!ft_strcmp(data->selected[i], data->args[data->pos]))
			return (remove_selection(data, i));
		i++;
	}
	data->selected[i++] = ft_strdup(data->args[data->pos]);
	data->selected[i] = NULL;
	return (0);
}

int		check_selection(t_var *data, char *str)
{
	int i;

	i = 0;
	if (!data->selected[0])
		return (0);
	while (data->selected[i])
	{
		if (!ft_strcmp(data->selected[i], str))
			return (1);
		i++;
	}
	return (0);
}

void	select_arg(t_var *data)
{
	clear_display(data);
	manage_selection(data);
	if (data->pos < data->nb_args)
		data->pos++;
	else
		data->pos = 1;
	display(data);
}
