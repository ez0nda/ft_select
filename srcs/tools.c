/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 10:07:37 by ezonda            #+#    #+#             */
/*   Updated: 2019/06/26 00:23:34 by ezonda           ###   ########.fr       */
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
		term.c_lflag &= (~(ICANON | ECHO));
//		signal(SIGTSTP, SIG_DFL);
		ioctl(0, TIOCSTI, &term);
	}
	else if (signal == SIGWINCH)
	{
//		ioctl(STDOUT_FILENO, TIOCGWINSZ, &wind);
		data = update_data(1, data);
		
//		ft_printf("\nlines : %d\n", wind.ws_row);
//		ft_printf("colums : %d\n", wind.ws_col);
		ft_printf("\nSIGWINCH\n");
//		update_data(1, NULL);
		clear_display(data);
		check_winsize(data);
		display(data);
	}
	else
		exit(hide_cursor(1));
}

int		ft_putchar_v2(int c)
{
	write(1, &c, 1);
	return (c);
}

void	free_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

char	**ft_tabdup(char **tab)
{
	int		i;
	char	**dest;

	i = 0;
	while (tab[i])
		i++;
	if (!(dest = (char**)malloc(sizeof(char*) * (i + 1))))
		return (NULL);
	i = 0;
	while (tab[i])
	{
		dest[i] = ft_strdup(tab[i]);
		i++;
	}
	dest[i] = NULL;
	return (dest);
}

void	init_data(t_var *data)
{
	data->nb_args = 0;
	while (data->args[data->nb_args])
		data->nb_args++;
	if (!(data->selected = (char**)malloc(sizeof(char*) * (data->nb_args + 1))))
		return ;
	data->selected[0] = NULL;
	data->nb_args--;
	data->pos = 1;
	data->char_count = 0;
	data->nb_cols = 0;
	data->nb_rows = 0;
}
