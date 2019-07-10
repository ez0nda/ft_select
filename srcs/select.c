/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 16:43:19 by ezonda            #+#    #+#             */
/*   Updated: 2019/07/10 14:00:10 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

static int		check_selection(t_var *data)
{
	if (data->tab[data->pos] == 1)
		return (1);
	return (0);
}

static void		update_tab(t_var *data, int index)
{
	int i;

	i = index;
	while (data->args[i])
	{
		data->args[i] = data->args[i + 1];
		i++;
	}
	i = index;
	while (i <= data->nb_args)
	{
		data->tab[i] = data->tab[i + 1];
		i++;
	}
}

void			remove_arg(t_var *data)
{
	int		i;
	char	**tmp;

	i = data->pos;
	clear_display(data);
	if (data->nb_args == 1)
		exit(hide_cursor(1));
	if (check_selection(data))
		manage_selection(data);
	free(data->args[i]);
	update_tab(data, i);
	tmp = ft_tabdup(data->args);
	free_tab(data->args);
	data->args = ft_tabdup(tmp);
	free_tab(tmp);
	if (data->pos == data->nb_args)
		data->pos--;
	data->nb_args--;
	display(data);
}

int				manage_selection(t_var *data)
{
	if (data->tab[data->pos] == 1)
	{
		data->tab[data->pos] = 0;
		return (0);
	}
	data->tab[data->pos] = 1;
	return (0);
}

void			select_arg(t_var *data)
{
	clear_display(data);
	manage_selection(data);
	if (data->pos < data->nb_args)
		data->pos++;
	else
		data->pos = 1;
	display(data);
}
