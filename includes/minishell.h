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
# include <errno.h>  
# include <limits.h>
# include "../libft/libft.h"
# include "../ft_printf/ft_printf.h"
# include "pipex.h"
# include "readline/history.h"
# include "readline/readline.h"

int	g_exit;

typedef struct s_inout
{
	int				type;
	int				red_prev;
	char			*heredoc;
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
void		sig_quit(int sig);
void		action(int sig);
char		*ft_get_input(int fd, int size, int len);
void		ft_parse_command(char *str, char **env, char **penv, char *tmp);
int			ft_check_quote(char *str);
int			ft_check_process(t_process *process);
void		ft_free_split(char **split);
int			ft_free_split_r(char **split, int x);
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
int			ft_structlen(t_process *process);
void		ft_config_inout(t_inout *inout);
void		ft_clear_process(t_process *process);
void		ft_config_process(t_process *process, int x, int next, int inout);
int			ft_space(char *str);
int			ft_w_is_eon(char *str);
int			ft_is_env_char(char c);
int			ft_is_tild(char *str, int x);
void		ft_env_c(char *str, int x, int *c);
void		ft_env_return(char **str, int *x, int y);
int			ft_is_herdoc(char *str, char *cmd);
<<<<<<< HEAD
void		ft_heredoc_process(t_process *process);
void		ft_ffailed(char *str, int code, t_data *data);
=======
void		ft_heredoc_process(t_process *process, char *tmpa);
>>>>>>> 1da7584259af7d7a8c6385fb139aa6e78979e4cc

// built-in
int			ft_pwd(int fd);
int			ft_echo(char **args, int fd);
int			ft_env(t_data *data, int fd);
int			ft_export(t_data *data, char **arg);
void		ft_remove_env(char **tmp, char *arg, int x, int y);
int			ft_exit(t_process *temp, t_data *data);
void		ft_exit_error(int i, char **t, char ***splited, t_process *temp);
void		ft_check_exit(int i, char **t, char ***splited, t_process *temp);
void		ft_return_exit(char **t, char ***splited);
void		ft_llmax_plus(int i, char **t, char ***splited, t_process *temp);
void		ft_llmax(int i, char **t, char ***splited, t_process *temp);
void		ft_llmin(int i, char **t, char ***splited, t_process *temp);
long long	ft_atol(const char *str);
int			ft_cd(t_data *data, int fd, char **path);
int			ft_unset(t_data *data, char **arg, int fd);
int			ft_swap(char **a, char **b);
int			ft_split_len(char **splitd);
char		**ft_sort(char *env, int x, int y, int a);
void		ft_display_export(char **splitd, int x, int y, int a);
char		*ft_add_env(char **tmp, char *arg);
char		*ft_remove_in(char *str, int a, int b);
int			ft_built(int i, t_data *data, t_process *temp);
int			ft_built_one(int i, t_data *data, t_process *temp, char **splited);
int			ft_built_red(int i, t_data *data, t_process *temp);
int			ft_built_red2(int i, t_data *data, t_process *temp);

// built-in utils
char		*ft_remove_in(char *str, int a, int b);
int			ft_env_len(char *env);
int			ft_is_valid(char *str);

// execution
void		ft_perror(char *str, int code);
int			ft_wordlen(char *str, t_data *data, int a);
int			ft_is_charset(char str, t_data *data, int a);
int			ft_wordcount(char *str, t_data *data, int a);
int			ft_strdupp_util2(t_data *data, int a, char *dst, char *src);
int			ft_strdupp_util3(t_data *data, int a, char *dst, char *src);
char		*ft_remove(char **str, int c);
char		**ft_dquote(char **split, int x, int y);
char		*ft_ddquote(char *split, int x);
char		*ft_check_arg(char *cmd, char **env);
int			ft_malloc_struct(t_data *data, int i);
void		create_pipes(t_data *data);
void		close_pipes(t_data *data);
int			ft_execute_cmd(t_process *proc, char **env, char **penv);
int			ft_execute_cmd_2(t_process *temp, t_process *proc, t_inout *temp2);
int			ft_execute_cmd_3(t_process *temp, t_inout *temp2, int i);
void		ft_execute_cmd_4(t_data *data, t_process *temp, char **env, int i);
int			ft_execute_cmd_5(t_data *data, t_process *temp, char **env, int i);
int			ft_execute_cmd_6(t_data *data, t_process **temp, char **env, int i);
int			ft_execute_cmd_7(t_data *data, t_process **temp, char **env, int i);
void		ft_execute_cmd_8(t_data *data, t_inout *tmp);
void		ft_execute_cmd_9(t_data *data, t_process **temp, char **env, int i);
void		ft_execute_cmd_10(t_data *data, t_process *temp, char **env, int i);
int			ft_execute_cmd_11(t_process *temp, t_data *data, int i, char **env);
void		free_exec(t_data *data, int i);
int			ft_status(t_data *data);
char		*ft_readline(void);

// forks
void		one_proc(t_data *data, t_process *temp, char **env, char **splited);
void		pipe_proc(t_data *data, t_process *temp, char **env, int i);
void		pipe_proc_2(t_process *temp, t_data *data, int i, char **env);
void		red_proc(t_data *data, t_process *temp, char **env, int i);
void		red_proc_2(t_data *data, t_process *temp, char **env, int i);
void		red2_proc(t_data *data, t_process *temp, char **env, int i);
void		red2_proc_2(t_data *data, t_process *temp, char **env, int i);
void		red3_proc(t_data *data, t_process *temp, char **env, int i);
void		red3_proc_2(t_data *data, t_process *temp, char **env, int i);
void		red4_proc(t_data *data, t_process *temp, char **env, int i);
void		red4_proc_2(t_data *data, t_process *temp, char **env, int i);

#endif	