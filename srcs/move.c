/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 10:19:29 by ezonda            #+#    #+#             */
/*   Updated: 2019/06/20 13:09:13 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

void	remove_arg(t_var *data)
{
	int		i;
	char	*res;
	char	**tmp;

	i = data->pos;
	clear_display(data);
	if (data->nb_args == 1)
		exit(hide_cursor(1));
	free(data->args[i]);
	while (data->args[i])
	{
		data->args[i] = data->args[i + 1];
		i++;
	}
	tmp = ft_tabdup(data->args);
	free_tab(data->args);
	data->args = ft_tabdup(tmp);
	free_tab(tmp);
	if (data->pos == data->nb_args)
		data->pos--;
	data->nb_args--;
	display(data);
}

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

void	move_down(t_var *data)
{
	
}
