/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 23:21:17 by ezonda            #+#    #+#             */
/*   Updated: 2019/06/28 23:22:18 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

void	signal_handler(int signal)
{
	static t_var *data;
	pid_t	pid;

	if (signal == SIGTSTP)
	{
		data = update_data(1, data);
		hide_cursor(1);
		exit_term(data);
	}
	else if (signal == SIGWINCH)
	{
		data = update_data(1, data);
		clear_display(data);
		check_winsize(data);
		display(data);
		check_winsize(data);
	}
	else
		exit(hide_cursor(1));
}
