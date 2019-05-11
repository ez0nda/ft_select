/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 11:51:00 by ezonda            #+#    #+#             */
/*   Updated: 2019/05/11 13:06:54 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <term.h>
#include <termios.h>

int		main(void)
{
	int success;
	char buffer[4096];
	char *termtype;

	termtype = getenv("TERM");
	if (!termtype)
		printf("error\n");
	else
		printf("termtype: %s\n", termtype);
	success = tgetent(buffer, termtype);
	if (success < 0)
		printf("Could not ... termcap database\n");
	else if (success == 0)
		printf("Terminal type %s not defined\n", termtype);
	else
		printf("ok bro\n");
	return (0);
}
