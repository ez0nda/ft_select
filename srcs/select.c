/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 16:43:19 by ezonda            #+#    #+#             */
/*   Updated: 2019/07/06 03:20:28 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

int		toggle_selection(t_var *data)
{
	if (data->tab[data->pos] == 1)
		return (1);
	return (0);
}

int		manage_selection(t_var *data)
{
	if (data->tab[data->pos] == 1)
	{
		data->tab[data->pos] = 0;
		return (0);
	}
	data->tab[data->pos] = 1;
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
