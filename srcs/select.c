/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 10:16:12 by ezonda            #+#    #+#             */
/*   Updated: 2019/05/22 15:15:08 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

static void		remove_selection(t_var *data, int index)
{
	char **tmp;

	free(data->selected[index]);
	while (data->selected[index])
	{
		data->selected[index] = data->selected[index + 1];
		index++;
	}
	data->selected[index] = NULL;
	tmp = ft_tabdup(data->selected);
	free_tab(data->selected);
	data->selected = ft_tabdup(tmp);
	if (data->pos < data->nb_args)
		data->pos++;
	else
		data->pos = 1;
}

static void		add_to_selection(t_var *data)
{
	static int	i;
	int			j;

	j = 0;
	if (!data->selected)
		data->selected = (char**)malloc(sizeof(char*) * (data->nb_args + 1));
	while (data->selected && data->selected[j])
	{
		if (!ft_strcmp(data->selected[j], data->args[data->pos]))
		{
			remove_selection(data, j);
			i -= 1;
			return ;
		}
		j++;
	}
	data->selected[i++] = ft_strdup(data->args[data->pos]);
	data->selected[i] = NULL;
	if (data->pos < data->nb_args)
		data->pos++;
	else
		data->pos = 1;
}

int				check_selection(t_var *data, char *str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (!data->selected)
		return (0);
	while (data->selected[i])
	{
		if (!ft_strcmp(data->selected[i], str))
			return (1);
		i++;
	}
	return (0);
}

void			select_arg(t_var *data)
{
	char *res;

	clear_display(data);
	add_to_selection(data);
	display(data);
}
