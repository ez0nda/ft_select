/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 14:13:56 by ezonda            #+#    #+#             */
/*   Updated: 2019/07/06 04:50:11 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

static void		print_selected(t_var *data, int index)
{
	char *res;

	if (data->tab[index] == 1)
	{
		if ((res = tgetstr("mr", NULL)) == NULL)
			return ;
		tputs(res, 0, ft_putchar_v2);
		ft_putstr_fd(GREEN, STDIN_FILENO);
		ft_putstr_fd(data->args[index], STDIN_FILENO);
		ft_putstr_fd(END, STDIN_FILENO);
		if ((res = tgetstr("me", NULL)) == NULL)
			return ;
		tputs(res, 0, ft_putchar_v2);
	}
	else
		ft_putstr_fd(data->args[index], STDIN_FILENO);
}

static int		check_winsize(t_var *data)
{
	int max_col;

	max_col = count_words(data);
	if (max_col == 0 || wind.ws_row < data->nb_rows)
	{
		ft_putstr_fd(BOLD, STDIN_FILENO);
		ft_putstr_fd(RED, STDIN_FILENO);
		ft_putstr_fd("Window too small", STDIN_FILENO);
		ft_putstr_fd(END, STDIN_FILENO);
		return (0);
	}
	return (1);
}

static void		print_standard(t_var *data, int index, int mod)
{
	int max_col;

	max_col = count_words(data);
	if (data->wcount == max_col)
	{
		ft_putchar_fd('\n', STDIN_FILENO);
		data->wcount = 0;
	}
	if (mod == 0)
		return ;
	print_selected(data, index);
	ft_putchar_fd(' ', STDIN_FILENO);
	data->wcount++;
}

static void		print_position(t_var *data)
{
	char *res;

	if ((res = tgetstr("us", NULL)) == NULL)
		return ;
	tputs(res, 0, ft_putchar_v2);
	ft_putstr_fd(BOLD, STDIN_FILENO);
	print_selected(data, data->pos);
	ft_putstr_fd(END, STDIN_FILENO);
	if ((res = tgetstr("ue", NULL)) == NULL)
		return ;
	tputs(res, 0, ft_putchar_v2);
	ft_putchar_fd(32, STDIN_FILENO);
	data->wcount++;
}

void			display(t_var *data)
{
	int		i;
	int		max_col;

	i = 1;
	data->wcount = 0;
	max_col = count_words(data);
	if (!check_winsize(data))
		return ;
	while (data->args[i] && i < data->pos)
	{
		print_standard(data, i, 1);
		i++;
	}
	print_standard(data, i, 0);
	print_position(data);
	i = data->pos + 1;
	while (data->args[i] && i <= data->nb_args)
	{
		print_standard(data, i, 1);
		i++;
	}
}
