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
# include <limits.h>
# include "../libft/libft.h"
# include "../ft_printf/ft_printf.h"
# include "pipex.h"
# include "readline/history.h"
# include "readline/readline.h"

typedef struct s_inout
{
	int				type;
	int				red_prev;
	char			*file;
	struct s_inout	*next;
}			t_inout;

typedef struct s_process
{
	struct s_process	*next;
	struct s_inout		*inout;
	char				*command;
	char				*cmd_arg;
	int					out_next;
	int					in_prev;
	char				*type;
}		t_process;

typedef struct s_check
{
	int	output;
	int	input;
}			t_check;


// parsing and everything else
char		*ft_get_input(int fd, int size, int len);
void		ft_parse_command(char *str, char **env, char **penv);
int			ft_check_quote(char *str);
int			ft_check_process(t_process *process);
void		ft_free_split(char **split);
char		**ft_splitd(char const *s, char c);
t_process	*ft_create_process(int x, int y, char **split);
void		ft_free(t_process **process);
int			ft_execute_cmd(t_process *proc, char **env, char **penv);
char		*ft_penv(char *env, char *str, int x, int b);
char		*ft_strnjoin(char *s1, char *s2, int n);
char		*ft_strndup(const char *s, size_t n);
char		*ft_search_env(char *env, char *var);
char		*ft_strsub(char const *s, unsigned int start, size_t len);
int			ft_word_len(char *str);
int			ft_w_is_space(char *str);
int			ft_len_quote(char *str);
int			ft_word_len(char *str);
char		*ft_replace(char *str, char *tmp, int x, int y);
void		ft_quote(t_process **process, int x, int *y, char **split);
int			ft_w_is_eon(char *str);
t_inout		*ft_create_inout(void);
int			ft_strstrlen(char **str);
int			ft_is_command(char *str, char *cmd);

// built-in
int			ft_pwd(int fd);
int			ft_echo(char **args, int fd);
int			ft_env(char **env, int fd);
int			ft_export(t_data *data, char **arg, int fd);
void		ft_remove_env(char **tmp, char *arg);
void		ft_exit(t_process *temp);
int			ft_cd(t_data *data, int fd, char **path);
int			ft_unset(t_data *data, char **arg, int fd);

// built-in utils
void		ft_remove_env(char **tmp, char *arg);
char		*ft_remove_in(char *str, int a, int b);
int			ft_env_len(char *env);
int			ft_is_valid(char *str);

// executions
void		ft_perror(char *str);
int			ft_wordlen(char *str, t_data *data, int a);
int			ft_is_charset(char str, t_data *data, int a);
int			ft_wordcount(char *str, t_data *data, int a);
int			ft_strdupp_util2(t_data *data, int a, char *dst, char *src);
int			ft_strdupp_util3(t_data *data, int a, char *dst, char *src);
char		*ft_remove(char *str, int c);
char		**ft_dquote(char **split, int x, int y);
char		*ft_ddquote(char *split, int x);

#endif