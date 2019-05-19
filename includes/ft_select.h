/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 15:07:52 by ezonda            #+#    #+#             */
/*   Updated: 2019/05/19 13:29:52 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include "../libft/includes/libft.h"

# include <curses.h>
# include <termcap.h>
# include <termios.h>

typedef struct	s_var
{
	int pos;
	int nb_args;
	char **args;
}				t_var;

#endif
