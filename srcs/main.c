/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 15:16:59 by ezonda            #+#    #+#             */
/*   Updated: 2019/05/18 14:52:01 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

int		ft_putchar_v2(int c)
{
	write(1, &c, 1);
	return (c);
}

void	get_arrow(t_var *key, char c)
{
	if (c == 65)
	{
		key->up = 1;
		ft_printf("UP\n");
	}
	if (c == 66)
	{
		key->down = 1;
		ft_printf("DOWN\n");
	}
	if (c == 67)
	{
		key->right = 1;
		ft_printf("RIGHT\n");
	}
	if (c == 68)
	{
		key->left = 1;
		ft_printf("LEFT\n");
	}
}

void	init_key(t_var *key)
{
	key->up = 0;
	key->down = 0;
	key->left = 0;
	key->right = 0;
	key->space = 0;
	key->ret = 0;
	key->esc = 0;
	key->del = 0;
	key->undo = 0;
}

void	get_key(t_var *key)
{
	char buffer[6];
	char *tmp;

	ft_bzero(buffer, 6);
	read(0, &buffer, sizeof(buffer));
/*	ft_printf("%d  ", buffer[0]);
	ft_printf("%d  ", buffer[1]);
	ft_printf("%d  ", buffer[2]);
	ft_printf("%d  ", buffer[3]);
	ft_printf("%d  ", buffer[4]);
	ft_printf("%d\n", buffer[5]);*/
	if (buffer[0] == 27 && buffer[1] == 0)
	{
		key->esc = 1;
		ft_printf("ESC\n");;
		return ;
	}
	else if (buffer[0] == 27 && buffer[1] == 91)
	{
		if (buffer[2] == 51)
		{
			key->del = 1;
			ft_printf("DEL\n");
		}
		else
			get_arrow(key, buffer[2]);
	}
	else if (buffer[0] == 32 && buffer[1] == 0)
	{
		key->space = 1;
		ft_printf("SPACE\n");
	}
	else if (buffer[0] == 10 && buffer[1] == 0)
	{
		key->ret = 1;
		ft_printf("RETURN\n");
	}
	else if (buffer[0] == 127 && buffer[1] == 0)
	{
		key->undo = 1;
		ft_printf("UNDO\n");
	}
}

void	new_display(char **av, t_var *key)
{
	int i;
	char *res;

	i = 1;
	while (av[i])
	{
		if (key->space == 1)
		{
			if ((res = tgetstr("us", NULL)) == NULL)
				return ;
			tputs(res, 0, ft_putchar_v2);
			ft_printf("%s ", av[i]);
			if ((res = tgetstr("ue", NULL)) == NULL)
				return ;
			tputs(res, 0, ft_putchar_v2);
		}
		else
			ft_printf("%s ", av[i]);
		i++;
	}
}

void	display_args(char **av)
{
	int i;

	i = 1;
	while (av[i])
		ft_printf("%s ", av[i++]);
}

void	ft_select(char **av, t_var *key)
{
	char *res;

	get_key(key);
	new_display(av, key);
	if ((res = tgetstr("cl", NULL)) == NULL)
		return ;
	tputs(res, 0, ft_putchar_v2);
}

int		main(int ac, char **av, char **env)
{
	struct termios term;
	char buffer[256];
	t_var key;

	if (!env)
		ft_printf("error: no env\n");
	init_key(&key);
	if (tgetent(buffer, getenv("TERM")) <= 0)
		ft_printf("termcap database error\n");
	if (tcgetattr(0, &term) == -1)
		return (-1);
	term.c_lflag &= (~(ICANON|ECHO));
	if (tcsetattr(0, TCSANOW, &term) == -1)
		return (-1);
	display_args(av);
	while (1)
	{
		ft_select(av, &key);
		if (key.esc == 1 || key.ret == 1)
			break ;
	}
	return (0);
}
