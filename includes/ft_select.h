/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 15:07:52 by ezonda            #+#    #+#             */
/*   Updated: 2019/07/06 04:29:50 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include "../libft/includes/libft.h"

# include <curses.h>
# include <termcap.h>
# include <termios.h>
# include <signal.h>
# include <sys/ioctl.h>

# define END "\x1b[0m"
# define BOLD "\x1b[1m"
# define YELLOW "\x1b[33m"
# define BLUE "\x1b[36m"
# define CYAN "\x1b[36m"
# define RED "\x1b[31m"

struct termios	term;
struct winsize	wind;;

typedef struct	s_var
{
	int pos;
	int nb_args;
	char **args;
	int *tab;
	int char_count;
	int wcount;
	int nb_cols;
	int nb_rows;
}				t_var;

t_var	*update_data(int mod, t_var *data);

void	display(t_var *data);

void	get_key(t_var *data);

void	remove_arg(t_var *data);
void	move_left(t_var *data);
void	move_right(t_var *data);
void	move_down(t_var *data);
void	move_up(t_var *data);

int		toggle_selection(t_var *data);
int		manage_selection(t_var *data);
void	select_arg(t_var *data);

void	signal_handler(void);

void	clear_display(t_var *data);
int		hide_cursor(int mod);
void	get_winsize(t_var *data);
void	set_termcanon(t_var *data);
double	count_words(t_var *data);

int		error(char *str);
int		ft_putchar_v2(int c);
void	free_tab(char **tab);
char	**ft_tabdup(char **tab);
void	init_data(t_var *data);

#endif
