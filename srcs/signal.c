/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 23:21:17 by ezonda            #+#    #+#             */
/*   Updated: 2019/07/06 04:09:31 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

static void		signal_quit(int sig)
{
	t_var *data;

	(void)sig;
	data = update_data(1, data);
	;free_tab(data->args);
	hide_cursor(1);
	exit(EXIT_FAILURE);
}

static void		signal_inter(int sig)
{
	t_var *data;

	(void)sig;
	data = update_data(1, data);
	signal(SIGTSTP, SIG_DFL);
	ioctl(STDIN_FILENO, TIOCSTI, "\x1A");
	hide_cursor(1);
}

static void		signal_restart(int sig)
{
	t_var *data;

	(void)sig;
	data = update_data(1, data);
	hide_cursor(0);
	set_termcanon(data);
	signal(SIGTSTP, signal_inter);
}

static void		signal_resize(int sig)
{
	t_var *data;

	(void)sig;
	data = update_data(1, data);
	clear_display(data);
	get_winsize(data);
	display(data);
	get_winsize(data);
}

void			signal_handler(void)
{
	unsigned int sig;

	sig = 0;
	while (++sig < 32)
	{
		if (sig == SIGINT || sig == SIGQUIT || sig == SIGTERM)
			signal(sig, signal_quit);
		if (sig == SIGTSTP)
			signal(sig, signal_inter);
		if (sig == SIGCONT)
			signal(sig, signal_restart);
		if (sig == SIGWINCH)
			signal(sig, signal_resize);
	}
}
