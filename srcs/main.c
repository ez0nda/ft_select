/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 15:16:59 by ezonda            #+#    #+#             */
/*   Updated: 2019/05/22 13:49:15 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

static void		hide_cursor(int mod)
{
	char *res;

	if (mod == 0)
	{
		if ((res = tgetstr("vi", NULL)) == NULL)
			return ;
		tputs(res, 0, ft_putchar_v2);
	}
	else
	{
		if ((res = tgetstr("ve", NULL)) == NULL)
			return ;
		tputs(res, 0, ft_putchar_v2);
	}
}

static int		return_selection(t_var *data)
{
	int i;

	i = 0;
	ft_printf("\n");
	if (!data->selected)
		return (0);
	while (data->selected[i])
		ft_printf("%s ", data->selected[i++]);
	return (0);
}

static void		get_arrow(t_var *data, char c)
{
	if (c == 65)
		ft_printf("UP\n");
	if (c == 66)
		ft_printf("DOWN\n");
	if (c == 67)
		move_right(data);
	if (c == 68)
		move_left(data);
}

static void		get_key(t_var *data)
{
	char buffer[6];
	char *tmp;

	while (1)
	{
		ft_bzero(buffer, 6);
		read(0, &buffer, sizeof(buffer));
		if (buffer[0] == 27 && buffer[1] == 0)
			exit(0);
		else if (buffer[0] == 27 && buffer[1] == 91)
		{
			if (buffer[2] == 51)
				remove_arg(data);
			else
				get_arrow(data, buffer[2]);
		}
		else if (buffer[0] == 32 && buffer[1] == 0)
			select_arg(data);
		else if (buffer[0] == 10 && buffer[1] == 0)
			break ;
		else if (buffer[0] == 127 && buffer[1] == 0)
			remove_arg(data);
	}
}

int				main(int ac, char **av, char **env)
{
	struct termios	term;
	char			buffer[256];
	t_var			data;

	signal(SIGINT, signal_handler);
	if (!getenv("TERM"))
		return (ft_printf("ft_select : environment not found\n"));
	data.args = ft_tabdup(av);
	init_data(&data);
	if (tgetent(buffer, getenv("TERM")) <= 0)
		return (ft_printf("ft_select : termcap database error\n"));
	if (tcgetattr(0, &term) == -1)
		return (-1);
	term.c_lflag &= (~(ICANON | ECHO));
	if (tcsetattr(0, TCSANOW, &term) == -1)
		return (-1);
	hide_cursor(0);
	clear_display(&data);
	default_display(&data);
	get_key(&data);
	hide_cursor(1);
	return (return_selection(&data));
}
