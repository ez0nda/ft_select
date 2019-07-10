/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 15:16:59 by ezonda            #+#    #+#             */
/*   Updated: 2019/07/10 11:01:08 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

t_var			*update_data(int mod, t_var *data)
{
	static t_var *data2;

	if (mod == 0)
		data2 = data;
	return (data2);
}

static int		count_selection(t_var *data)
{
	int i;
	int count;

	i = 1;
	count = 0;
	while (i <= data->nb_args)
	{
		if (data->tab[i] == 1)
			count++;
		i++;
	}
	return (count);
}

static int		return_selection(t_var *data)
{
	int i;
	int count;
	int output;

	i = 1;
	output = 0;
	count = count_selection(data);
	clear_display(data);
	while (data->args[i])
	{
		if (data->tab[i] == 1)
		{
			output++;
			ft_putstr_fd(GREEN, STDIN_FILENO);
			ft_putstr_fd(data->args[i], STDOUT_FILENO);
			if (count > output)
				ft_putchar_fd(' ', STDOUT_FILENO);
			ft_putstr_fd(END, STDIN_FILENO);
		}
		i++;
	}
	free(data->tab);
	free_tab(data->args);
	return (hide_cursor(1));
}

int				main(int ac, char **av, char **env)
{
	t_var	data;

	if (!env || !*env)
		return (error("env"));
	if (ac < 2)
		return (error("usage"));
	signal_handler();
	data.args = ft_tabdup(av);
	init_data(&data);
	set_termcanon(&data);
	get_key(&data);
	return (return_selection(&data));
}
