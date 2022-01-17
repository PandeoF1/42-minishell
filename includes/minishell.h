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
# include <stdlib.h>
# include <signal.h>
# include "../libft/libft.h"
# include "../ft_printf/ft_printf.h"
# include "pipex.h"

typedef struct s_inout
{
	int				type;
	char			*file;
	struct s_inout	*next;
}			t_inout;

typedef struct s_process
{
	struct s_process	*next;
	struct s_inout		*inout;
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
void		ft_parse_command(char *str, char *env);
int			ft_check_quote(char *str);
int			ft_check_inout(char *str);
void		ft_free_split(char **split);
int			ft_check_inout_n(char *str);
char		**ft_splitd(char const *s, char c);
t_process	*ft_create_process(char *str, int *status);
void		ft_free(t_process **process);
int			ft_execute_cmd(t_process *proc, char *env);
char		*ft_env(char *env, char *str);
char		*ft_strnjoin(char *s1, char *s2, int n);
char		*ft_strndup(const char *s, size_t n);

void		ft_perror(char *str);
char		**ft_split_exec(char const *s, t_data *data, int a);
int			ft_wordlen(char *str, t_data *data, int a);
int			ft_is_charset(char str, t_data *data, int a);
int			ft_wordcount(char *str, t_data *data, int a);
int			ft_strdupp_util2(t_data *data, int a, char *dst, char *src);
int			ft_strdupp_util3(t_data *data, int a, char *dst, char *src);

#endif