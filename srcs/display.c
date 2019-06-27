/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 14:13:56 by ezonda            #+#    #+#             */
/*   Updated: 2019/06/27 22:34:01 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

void			clear_display(t_var *data)
{
	char	*res;

	if ((res = tgetstr("cl", NULL)) == NULL)
		return ;
	tputs(res, 0, ft_putchar_v2);
}

void			default_display(t_var *data)
{
	int		i;
	char	*res;

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

static void		print_args(t_var *data, int index)
{
	char *res;

	if (check_selection(data, data->args[index]))
	{
		if ((res = tgetstr("mr", NULL)) == NULL)
			return ;
		tputs(res, 0, ft_putchar_v2);
		ft_printf("%s", data->args[index]);
		if ((res = tgetstr("me", NULL)) == NULL)
			return ;
		tputs(res, 0, ft_putchar_v2);
	}
	else
		ft_printf("%s", data->args[index]);
}

void			display(t_var *data)
{
	int		i;
	char	*res;
	int width;
	int count;

	i = 1;
	count = 0;
	width = count_words(data);
	if (width == 0 || wind.ws_row < data->nb_rows)
	{
		ft_printf("Window too small");
		return ;
	}
	while (data->args[i] && i < data->pos)
	{
		if (count == width)
		{
			ft_printf("\n");
			count = 0;;
		}
		print_args(data, i);
		ft_printf(" ");
		i++;
		count++;
	}
	if (count == width)
	{
		ft_printf("\n");
		count = 0;;
	}
	count++;
	if ((res = tgetstr("us", NULL)) == NULL)
		return ;
	tputs(res, 0, ft_putchar_v2);
	print_args(data, data->pos);
	if ((res = tgetstr("ue", NULL)) == NULL)
		return ;
	tputs(res, 0, ft_putchar_v2);
	ft_printf(" ");
	i = data->pos + 1;
	while (data->args[i] && i <= data->nb_args)
	{
		if (count == width)
		{
			ft_printf("\n");
			count = 0;;
		}
		print_args(data, i);
		ft_printf(" ");
		i++;
		count++;
	}
}
