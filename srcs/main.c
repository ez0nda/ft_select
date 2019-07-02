/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 15:16:59 by ezonda            #+#    #+#             */
/*   Updated: 2019/07/02 02:33:32 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

static int		return_selection(t_var *data)
{
	int i;
	char *res;

	i = 0;
	ft_printf("\n");
	if (!data->selected)
		return (0);
	exit_term(data);
	if ((res = tgetstr("ho", NULL)) == NULL)
		return (0);
	tputs(res, 0, ft_putchar_v2);
	while (data->selected[i])
	{
		ft_printf("%s", data->selected[i++]);
		if (data->selected[i] != NULL)
			ft_printf(" ");
	}
	hide_cursor(1);
	exit(0);
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
		return (ft_printf("ft_select : environnement not found\n"));
	signal_handler();
	data.args = ft_tabdup(av);
	init_data(&data);
	set_termcanon(&data);
	get_key(&data);
	return (return_selection(&data));
}
