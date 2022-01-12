/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 10:47:55 by tnard             #+#    #+#             */
/*   Updated: 2022/01/03 10:47:55 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include "../libft/libft.h"
# include "../ft_printf/ft_printf.h"
# include "pipex.h"

typedef struct s_process
{
	struct s_process	*next;
	char				*command;
	char				*cmd_arg;
	char				*path;
	char				*args;
	char				*in_file;
	char				*out_file;
	char				*inout_file;
	int					out_next;
	int					out_prev;
	char				*input;
	int					in_prev;
	int					in_next;
	char				*type;
}		t_process;

typedef struct s_check
{
	int	output;
	int	input;
}			t_check;

char		*ft_get_input(int fd, int size, int len);
void		ft_parse_command(char *str, char **env);
int			ft_check_quote(char *str);
int			ft_check_inout(char *str);
void		ft_free_split(char **split);
int			ft_check_inout_n(char *str);
char		**ft_splitd(char const *s, char c);
t_process	*ft_create_process(char *str, int *status);
void		ft_free(t_process **process);

#endif