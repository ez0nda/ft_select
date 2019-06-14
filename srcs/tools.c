/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 10:07:37 by ezonda            #+#    #+#             */
/*   Updated: 2019/06/14 13:34:34 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

void	signal_handler(int signal)
{
//	pid_t pid;
	(void)signal;
//	ft_printf("\nsig : %d\n", signal);
//	if (signal == 18)
//		kill(pid, SIGTSTP);
//	else
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
}
