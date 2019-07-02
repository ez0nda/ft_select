/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 23:26:44 by ezonda            #+#    #+#             */
/*   Updated: 2019/07/02 23:28:05 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

double	count_words(t_var *data)
{
	int i;
	int max_len;
	int words;

	i = 1;
	max_len = 0;
	while (data->args[i])
	{
		if (ft_strlen(data->args[i]) > max_len)
			max_len = ft_strlen(data->args[i]);
		i++;
	}
	max_len++;
	words = data->nb_cols / max_len;
	return (words);
}

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

void	exit_term(t_var *data)
{
	if (tcgetattr(0, &term) == -1)
		return ;
	term.c_lflag &= (~(ICANON | ECHO));
	if (tcsetattr(0, TCSANOW, &term) == -1)
		return ;
}

void	check_winsize(t_var *data)
{
	int i;
	int width;

	i = 1;
	data->char_count = 0;
	width = count_words(data);
	while (data->args[i])
	{
		data->char_count += ft_strlen(data->args[i]);
		i++;
	}
	ioctl(STDIN_FILENO, TIOCGWINSZ, &wind);
	data->nb_cols = wind.ws_col;
	data->nb_rows = data->nb_args / count_words(data) + 1;
}

void	set_termcanon(t_var *data)
{
	char buffer[256];

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
}
