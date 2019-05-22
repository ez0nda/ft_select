/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 10:07:37 by ezonda            #+#    #+#             */
/*   Updated: 2019/05/22 13:47:48 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

void	signal_handler(int signal)
{
	char *res;

	(void)signal;
	if ((res = tgetstr("ve", NULL)) == NULL)
		return ;
	tputs(res, 0, ft_putchar_v2);
	exit(0);
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
	data->selected = NULL;
	data->nb_args = 0;
	while (data->args[data->nb_args])
		data->nb_args++;
	data->nb_args--;
	data->pos = 1;
}
