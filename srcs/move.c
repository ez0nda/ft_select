/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 10:19:29 by ezonda            #+#    #+#             */
/*   Updated: 2019/07/10 13:55:50 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

void	move_left(t_var *data)
{
	clear_display(data);
	if (data->pos > 1)
		data->pos--;
	else
		data->pos = data->nb_args;
	display(data);
}

void	move_right(t_var *data)
{
	clear_display(data);
	if (data->pos < data->nb_args)
		data->pos++;
	else
		data->pos = 1;
	display(data);
}

void	move_up(t_var *data)
{
	int i;

	if (data->nb_rows == 1)
		return ;
	clear_display(data);
	i = count_words(data);
	if (data->pos - i > 0)
		data->pos -= i;
	else
	{
		while (data->pos + i <= data->nb_args)
			data->pos += i;
	}
	display(data);
}

void	move_down(t_var *data)
{
	int i;

	if (data->nb_rows == 1)
		return ;
	clear_display(data);
	i = count_words(data);
	if (data->pos + i <= data->nb_args)
		data->pos += i;
	else
	{
		while (data->pos > i)
			data->pos -= i;
	}
	display(data);
}
