/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 10:07:37 by ezonda            #+#    #+#             */
/*   Updated: 2019/07/02 01:55:28 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

int		ft_putchar_v2(int c)
{
	write(0, &c, 1);
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
	ioctl(STDIN_FILENO, TIOCGWINSZ, &wind);
	data->nb_cols = wind.ws_col;
	data->nb_rows = 0;
}
