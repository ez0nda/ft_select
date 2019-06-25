/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 15:16:59 by ezonda            #+#    #+#             */
/*   Updated: 2019/06/25 01:15:06 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

int		hide_cursor(int mod)
{
	char *res;

	if (mod == 0)
	{
		if ((res = tgetstr("vi", NULL)) == NULL)
			return (0);
		tputs(res, 0, ft_putchar_v2);
	}
	else
	{
		if ((res = tgetstr("ve", NULL)) == NULL)
			return (0);
		tputs(res, 0, ft_putchar_v2);
	}
	return (0);
}

static int		return_selection(t_var *data)
{
	int i;

	i = 0;
	ft_printf("\n");
	if (!data->selected)
		return (0);
//	while (data->selected[i])
//		ft_printf("%s ", data->selected[i++]);
	while (data->selected[i])
		ft_putstr_fd(data->selected[i++], 0);
	return (0);
}

static void		get_arrow(t_var *data, char c)
{
	if (c == 65)
		move_up(data);
	if (c == 66)
		move_down(data);
	if (c == 67)
		move_right(data);
	if (c == 68)
		move_left(data);
}

void	check_winsize(t_var *data)
{
	int i;

	i = 1;
	data->char_count = 0;
	while (data->args[i])
	{
		data->char_count += ft_strlen(data->args[i]);
		i++;
	}
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &wind);
	ft_printf("\ncount : %d\n", data->char_count + i);
	ft_printf("nb_cols : %d\n", wind.ws_col);
	data->nb_cols = wind.ws_col;
	data->nb_row = wind.ws_row;
	ft_printf("nb_row : %d\n", data->nb_row);
}

void	set_termcanon(t_var *data)
{
	char buffer[256];
	static int update;

	if (tgetent(buffer, getenv("TERM")) <= 0)
		return ;
	if (tcgetattr(0, &term) == -1)
		return ;
	term.c_lflag &= (~(ICANON | ECHO));
	if (tcsetattr(0, TCSANOW, &term) == -1)
		return ;
	hide_cursor(0);
	clear_display(data);
	check_winsize(data);
	display(data);
	ft_printf("\nUpdate %d\n", update++);
}

void			update_data(int mod, t_var *data)
{
	static t_var *data2;

	ft_printf("\nUPDATE\n");
	if (mod == 1 && data2 != NULL)
		get_key(data2);
	else
		data2 = data;
}

void		get_key(t_var *data)
{
	char buffer[6];
	char *res;

	while (1)
	{
		update_data(0, data);
		set_termcanon(data);
		ft_bzero(buffer, 6);
		read(0, &buffer, sizeof(buffer));
		if (buffer[0] == 27 && buffer[1] == 0)
			exit(hide_cursor(1));
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
//	struct termios	term;
	char			buffer[256];
	t_var			data;

	signal(SIGINT, signal_handler);
	signal(SIGWINCH, signal_handler);
	signal(SIGTSTP, signal_handler);
	ft_printf("here\n");
	if (!getenv("TERM"))
		return (ft_printf("ft_select : environment not found\n"));
	data.args = ft_tabdup(av);
	init_data(&data);
/*	if (tgetent(buffer, getenv("TERM")) <= 0)
		return (ft_printf("ft_select : termcap database error\n"));
	if (tcgetattr(0, &term) == -1)
		return (-1);
	term.c_lflag &= (~(ICANON | ECHO));
	if (tcsetattr(0, TCSANOW, &term) == -1)
		return (-1);
	hide_cursor(0);
	clear_display(&data);
	default_display(&data);*/
	get_key(&data);
	hide_cursor(1);
	return (return_selection(&data));
}
