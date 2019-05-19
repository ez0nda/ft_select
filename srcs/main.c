/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 15:16:59 by ezonda            #+#    #+#             */
/*   Updated: 2019/05/19 15:19:47 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

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

int		ft_putchar_v2(int c)
{
	write(1, &c, 1);
	return (c);
}

void	default_display(t_var *data)
{
	int i;
	char *res;

	i = 0;
	while (data->args[i])
		i++;
	if (i >= 2)
	{
		i = 2;
		if ((res = tgetstr("us", NULL)) == NULL)
			return ;
		tputs(res, 0, ft_putchar_v2);
		ft_printf("%s", data->args[data->pos]);
		if ((res = tgetstr("ue", NULL)) == NULL)
			return ;
		tputs(res, 0, ft_putchar_v2);
		while (data->args[i])
			ft_printf(" %s", data->args[i++]);
	}
}

void	clear_display(t_var *data)
{
	int i;
	char *res;

	i = 1;
	if ((res = tgetstr("cl", NULL)) == NULL)
		return ;
	tputs(res, 0, ft_putchar_v2);
}

void	select_arg(t_var *data)
{
	char *res;
	int i = 1;

	clear_display(data);
	while (data->args[i] && i < data->pos)
		ft_printf("%s ", data->args[i++]);
	if ((res = tgetstr("mr", NULL)) == NULL)
		return ;
	tputs(res, 0, ft_putchar_v2);
	ft_printf("%s", data->args[data->pos]);
	if ((res = tgetstr("me", NULL)) == NULL)
		return ;
	tputs(res, 0, ft_putchar_v2);
	i = data->pos + 1;
	while (data->args[i] && i <= data->nb_args)
		ft_printf(" %s", data->args[i++]);
}

void	remove_arg(t_var *data)
{
	int i;
	char *res;
	char **tmp;

	i = data->pos;
	clear_display(data);
	if (data->nb_args == 1)
		exit(0);
	free(data->args[i]);
	while (data->args[i])
	{
		data->args[i] = data->args[i + 1];
		i++;
	}
	tmp = ft_tabdup(data->args);
	free_tab(data->args);
	data->args = ft_tabdup(tmp);
	free_tab(tmp);
	data->nb_args--;
	i = 1;
	if (!data->args[data->pos])
		data->pos--;
	while (data->args[i] && i < data->pos)
		ft_printf("%s ", data->args[i++]);
	if ((res = tgetstr("us", NULL)) == NULL)
		return ;
	tputs(res, 0, ft_putchar_v2);
	ft_printf("%s", data->args[data->pos]);
	if ((res = tgetstr("ue", NULL)) == NULL)
		return ;
	tputs(res, 0, ft_putchar_v2);
	i = data->pos + 1;
	while (data->args[i] != NULL && i <= data->nb_args)
		ft_printf(" %s", data->args[i++]);
}

void	move_left(t_var *data)
{
	char *res;
	int i = 1;

	clear_display(data);
	if (data->pos > 1)
		data->pos--;
	else
		data->pos = data->nb_args;
	while (data->args[i] && i < data->pos)
		ft_printf("%s ", data->args[i++]);
	if ((res = tgetstr("us", NULL)) == NULL)
		return ;
	tputs(res, 0, ft_putchar_v2);
	ft_printf("%s", data->args[data->pos]);
	if ((res = tgetstr("ue", NULL)) == NULL)
		return ;
	tputs(res, 0, ft_putchar_v2);
	i = data->pos + 1;
	while (data->args[i] && i <= data->nb_args)
		ft_printf(" %s", data->args[i++]);
}

void	move_right(t_var *data)
{
	char *res;
	int i = 1;

	clear_display(data);
	if (data->pos < data->nb_args)
		data->pos++;
	else
		data->pos = 1;
	while (data->args[i] && i < data->pos)
		ft_printf("%s ", data->args[i++]);
	if ((res = tgetstr("us", NULL)) == NULL)
		return ;
	tputs(res, 0, ft_putchar_v2);
	ft_printf("%s", data->args[data->pos]);
	if ((res = tgetstr("ue", NULL)) == NULL)
		return ;
	tputs(res, 0, ft_putchar_v2);
	i = data->pos + 1;
	while (data->args[i] && i <= data->nb_args)
		ft_printf(" %s", data->args[i++]);
}

void	get_arrow(t_var *data, char c)
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

void	init_key(t_var *data)
{
	data->nb_args = 0;
	while (data->args[data->nb_args])
		data->nb_args++;
	data->nb_args--;
	data->pos = 1;
}

void	get_key(t_var *data)
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

int		main(int ac, char **av, char **env)
{
	struct termios term;
	char buffer[256];
	t_var data;

	if (!env)
		ft_printf("error: no env\n");
	data.args = ft_tabdup(av);
	init_key(&data);
	if (tgetent(buffer, getenv("TERM")) <= 0)
		ft_printf("termcap database error\n");
	if (tcgetattr(0, &term) == -1)
		return (-1);
	term.c_lflag &= (~(ICANON|ECHO));
	if (tcsetattr(0, TCSANOW, &term) == -1)
		return (-1);
	clear_display(&data);
	default_display(&data);
	get_key(&data);
	return (0);
}
