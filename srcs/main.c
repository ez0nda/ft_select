/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 15:16:59 by ezonda            #+#    #+#             */
/*   Updated: 2019/07/02 23:57:53 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

static int		return_selection(t_var *data)
{
	int i;
	char *res;

	i = 0;
//	exit_term(data);
	if (!data->selected)
		return (0);
	clear_display(data);
	while (data->selected[i])
	{
		ft_printf("%s", data->selected[i++]);
		if (data->selected[i] != NULL)
			ft_printf(" ");
	}
	free_tab(data->args);
	free_tab(data->selected);
	hide_cursor(1);
	return (0);
}

t_var		*update_data(int mod, t_var *data)
{
	static t_var *data2;

	if (mod == 0)
		data2 = data;
	return (data2);
}

int				main(int ac, char **av, char **env)
{
	t_var	data;

	if (!env || !*env)
		return (error("env"));
//	if (!isatty(0) || !isatty(1))
//		return (error("tty"));
	if (ac < 2)
		return (error("usage"));
	signal_handler();
	data.args = ft_tabdup(av);
	init_data(&data);
	set_termcanon(&data);
	get_key(&data);
	return (return_selection(&data));
}
