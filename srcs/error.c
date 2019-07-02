/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 22:26:33 by ezonda            #+#    #+#             */
/*   Updated: 2019/07/02 23:02:56 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

int		error(char *str)
{
	if (!ft_strcmp(str, "env"))
		ft_putendl_fd("ft_select : environment not found", STDERR_FILENO);
	if (!ft_strcmp(str, "usage"))
		ft_putendl_fd("usage: ./ft_select [file ...]", STDERR_FILENO);
	if (!ft_strcmp(str, "tty"))
		ft_putendl_fd("file descriptor is not a tty", STDERR_FILENO);
	return (0);
}
