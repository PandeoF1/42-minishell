/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaffroy <asaffroy@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 11:15:22 by asaffroy          #+#    #+#             */
/*   Updated: 2022/01/26 15:24:45 by asaffroy         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
*int	find_path(char **env)
*env	env of the shell
*do :	find the line "PATH" in the env
*/

int	find_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
			return (i);
		i++;
	}
	return (i);
}

void	ft_built(int i, char **env, t_data *data, t_process *temp)
{
	if (!ft_strncmp(temp->command, "pwd", 3))
		ft_pwd(data->fd1[i]);
	if (!ft_strncmp(temp->command, "env", 3))
		ft_env(env, data->fd1[i]);
	if (!ft_strncmp(temp->command, "exit", 4))
		ft_exit(data->fd1[i]);
	if (!ft_strncmp(temp->command, "cd", 2))
		ft_cd(fd, data->tab_args[i]);
	if (!ft_strncmp(temp->command, "export", 6))
		ft_export(data, data->tab_args[i], data->fd1[i]);
}

/*
*char	*ft_check_arg(char *cmd, char **env)
*cmd	command to search in /bin
*env	env of the shell
*error	not norminette
*do :	check if the command exist and if we have the rights to use it 
*/

char	*ft_strxjoin(char *s1, char *s2, int n)
{
	int		i;
	int		j;
	char	*str;
	int		k;

	k = 0;
	j = ft_strlen(s2) + n + 1;
	str = (char *)malloc(sizeof(char) * j);
	if (!str)
		return (NULL);
	i = -1;
	while (++i < (int)ft_strlen(s1))
		str[i] = s1[i];
	while (n-- && s2[k])
		str[i++] = s2[k++];
	str[i] = '\0';
	free(s2);
	return (str);
}

char	*ft_check_arg(char *cmd, char **env)
{
	int			i;
	char		**tab;
	char		*try;

	try = NULL;
	cmd = ft_ddquote(cmd, 0);
	if (!access(cmd, F_OK))
	{
		if (ft_strlen(cmd) > 2 && cmd[0] == '.'
			&& cmd[1] == '/' && !access(cmd, X_OK))
			return (cmd);
		else
			if (ft_strchr(cmd, '/'))
				ft_perror("minishell: Permission denied");
	}
	if (ft_strchr(cmd, '/'))
		ft_perror("minishell: No such file or directory");
	cmd = ft_strxjoin("/", cmd, ft_strlen(cmd));
	i = find_path(env);
	//ft_printf("hugh : %s\n", env[1]);
	tab = ft_split(env[i] + 5, ':');
	i = 0;
	while (tab[i])
	{
		try = ft_strjoin(tab[i], cmd);
		if (!access(try, X_OK))
		{
			i = -1;
			while (tab[++i])
				free(tab[i]);
			free(tab);
			free(cmd);
			return (try);
		}
		i++;
	}
	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
	free(cmd);
	free(try);
	ft_perror("minishell: No such file or directory");
	return (0);
}

/*
*void	father_proc(t_data *data, char **argv, char **env)
*data	my struct with all data needed
*env	env of the shell
*argv	tab of args received at launch of prog
*do :	exec one of the cmd
*/

int	ft_malloc_struct(t_data *data, int	i)
{
	int	j;

	j = -1;
	data->fd = (int *)malloc(sizeof(int) * i * 2);
	if (!data->fd)
		return (0);
	data->check = (int *)malloc(sizeof(int) * i);
	if (!data->check)
		return (0);
	data->fd1 = malloc(sizeof(int) * i);
	if (!data->fd1)
		return (0);
	data->type_nb = (int *)malloc(sizeof(int) * i);
	if (!data->type_nb)
		return (0);
	data->i = (int *)malloc(sizeof(int) * i);
	if (!data->i)
		return (0);
	data->dec = malloc(sizeof(int) * i);
	if (!data->dec)
		return (0);
	data->type_char = malloc(sizeof(char) * i);
	if (!data->type_char)
		return (0);
	data->tab_args = malloc(sizeof(char **) * i);
	if (!data->tab_args)
		return (0);
	data->tab_paths = malloc(sizeof(char *) * i);
	if (!data->tab_paths)
		return (0);
	data->file = malloc(sizeof(int) * i);
	if (!data->file)
		return (0);
	data->charset[0] = '\'';
	data->charset[1] = '\"';
	data->charset[2] = ' ';
	data->charset[3] = '\0';
	data->nb_cmd = i;
	data->pid1 = malloc(sizeof(pid_t) * i);
	return (1);
}

void	create_pipes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_cmd)
	{
		if (pipe(data->fd + 2 * i) < 0)
			ft_perror("fail , lets free\n");
		i++;
	}
}

void	close_pipes(t_data *data)
{
	int	i;

	i = 0;
	while (i < 2 * data->nb_cmd)
	{
		close(data->fd[i]);
		i++;
	}
}

void	free_exec(t_data *data, int i)
{
	int			j;

	i = 0;
	//temp = proc;
	j = 0;
	//while (++i && temp->next != NULL)
		//temp = temp->next;
	/*while (i > 0)
	{
		j = -1;
		if (temp->cmd_arg != NULL)
			free(temp->cmd_arg);
		if (temp->command != NULL)
			free(temp->command);
		if (temp->type != NULL)
			free(temp->type);
		free(temp);
		i--;
		temp = proc;
		while (++j < i - 1)
			temp = temp->next;
	}*/
	if (data->fd)
		free(data->fd);
	if (data->pid1)
		free(data->pid1);
	if (data->tab_args)
		free(data->tab_args);
	// if (data->tab_paths) //need to be free
	// {
	// 	while (data->tab_paths[j] != NULL)
	// 	{
	// 		free(data->tab_paths[j]);
	// 		ft_printf("freed\n");
	// 		j++;
	// 	}
	// }
	if (data->tab_paths) //need to be free
		free(data->tab_paths);
	if (data->check)
		free(data->check);
	if (data->type_char)
		free(data->type_char);
	if (data->type_nb)
		free(data->type_nb);
	if (data->i)
		free(data->i);
	if (data->dec)
		free(data->dec);
	// j = -1; need to be free
	// while (data->file[++j])
	// 	free(data->file[j]);
	free(data->file); // need to be free
}

void	pipe_proc(t_data *data, t_process *temp, char **env, int i)
{
	data->pid1[i] = fork();
	if (data->pid1[i] < 0)
		ft_perror("forking failed\n");
	if (data->pid1[i] == 0)
	{
		data->tab_args[i] = ft_dquote(ft_splitd(temp->cmd_arg, ' '), 0, 0);
		data->tab_paths[i] = ft_check_arg(temp->command, env);
		if (temp->in_prev != 0)
		{
			if (dup2(data->fd[2 * data->ind], STDIN_FILENO) == -1)
				ft_perror("dup2 n1 failed in pipe_proc");
		}
		if (temp->out_next != 0)
			if (dup2(data->fd[2 * (data->ind + 1) + 1], STDOUT_FILENO) == -1)
				ft_perror("dup2 n2 failed in pipe_proc");
		close_pipes(data);
		if (execve(data->tab_paths[i], data->tab_args[i], NULL) != 0)
			ft_perror("failed to exec in pipe_proc");
	}
}

void	one_proc(t_data *data, t_process *temp, char **env)
{
	data->pid1[0] = fork();
	if (data->pid1[0] < 0)
		ft_perror("forking failed\n");
	if (data->pid1[0] == 0)
	{
		close_pipes(data);
		data->fd1[i] = 1;
		data->tab_args[0] = ft_dquote(ft_splitd(temp->cmd_arg, ' '), 0, 0);
		data->tab_paths[0] = ft_check_arg(temp->command, env);
		ft_built(1, env, data, temp);
		if (execve(data->tab_paths[0], data->tab_args[0], env) == -1)
			ft_perror("failed to exec in one_proc");
	}
}

void	red2_proc(t_data *data, t_process *temp, char **env, int i)
{
	data->pid1[i] = fork();
	if (data->pid1[i] < 0)
		ft_perror("forking failed\n");
	if (data->pid1[i] == 0)
	{
		if (temp->out_next)
			data->fd[2 * (data->ind + 1) + 1] = open(ft_ddquote
					(data->inout->file, 0), O_RDWR | O_TRUNC | O_CREAT, 0644);
		else
			data->file[i] = open(ft_ddquote
					(data->inout->file, 0), O_RDWR | O_TRUNC | O_CREAT, 0644);
		if (data->fd[2 * (data->ind + 1) + 1] < 0)
			ft_perror("\033[2K\r\033[0;31mError\033[0m : file creation failed");
		if (temp->in_prev != 0 || data->inout->red_prev == 1)
		{
			if (dup2(data->fd[2 * data->ind], STDIN_FILENO) == -1)
				ft_perror("dup2 n1 failed in pipe_proc");
		}
		if (data->inout->next == NULL && temp->out_next)
		{
			if (dup2(data->fd[2 * (data->ind + 1) + 1], STDOUT_FILENO) == -1)
				ft_perror("dup2 n2 failed in red_proc");
		}
		else if (data->inout->next == NULL)
		{
			if (dup2(data->file[i], STDOUT_FILENO) == -1)
				ft_perror("dup2 n3 failed in red_proc");
		}
		close_pipes(data);
		if (!temp->out_next)
			close(data->file[i]);
		if (temp->command != NULL)
		{
			if (data->inout->next == NULL)
			{
				data->tab_args[i]
					= ft_dquote(ft_splitd(temp->cmd_arg, ' '), 0, 0);
				data->tab_paths[i] = ft_check_arg(temp->command, env);
				if (execve(data->tab_paths[i], data->tab_args[i], NULL) == -1)
					ft_perror("failed to exec in red_proc\n");
			}
		}
		exit(0);
	}
}

void	red_proc(t_data *data, t_process *temp, char **env, int i)
{
	data->pid1[i] = fork();
	if (data->pid1[i] < 0)
		ft_perror("forking failed\n");
	if (data->pid1[i] == 0)
	{
		data->file[i]
			= open(ft_ddquote(data->inout->file, 0), O_RDONLY);
		if (data->file[i] < 0)
			ft_perror("\033[2K\r\033[0;31mError\033[0m : file opening failed");
		if (data->inout->next == NULL)
			if (dup2(data->file[i], STDIN_FILENO) == -1)
				ft_perror("dup2 n1 failed in red2_proc");
		if (data->inout->next == NULL && temp->out_next)
			if (dup2(data->fd[2 * (data->ind + 1) + 1], STDOUT_FILENO) == -1)
				ft_perror("dup2 n1 failed in red_proc");
		close_pipes(data);
		close(data->file[i]);
		if (temp->command != NULL)
		{
			if (data->inout->next == NULL)
			{
				data->tab_args[i]
					= ft_dquote(ft_splitd(temp->cmd_arg, ' '), 0, 0);
				data->tab_paths[i] = ft_check_arg(temp->command, env);
				if (execve(data->tab_paths[i], data->tab_args[i], NULL) == -1)
					ft_perror("failed to exec in red2_proc\n");
			}
		}
		exit (0);
	}
}

void	red3_proc(t_data *data, t_process *temp, char **env, int i)
{
	data->pid1[i] = fork();
	if (data->pid1[i] < 0)
		ft_perror("forking failed\n");
	if (data->pid1[i] == 0)
	{
		if (dup2(data->fd[2 * (data->ind + 1) - 2], STDIN_FILENO) == -1)
			ft_perror("dup2 n1 failed in red3_proc");
		if (temp->out_next || (temp->inout->next
				&& temp->inout->next->type != 3))
			if (dup2(data->fd[2 * (data->ind + 1) + 1], STDOUT_FILENO) == -1)
				ft_perror("dup2 n1 failed in red_proc");
		close_pipes(data);
		if (temp->command != NULL && !data->inout->next)
		{
			data->tab_args[i]
				= ft_dquote(ft_splitd(temp->cmd_arg, ' '), 0, 0);
			data->tab_paths[i] = ft_check_arg(temp->command, env);
			if (execve(data->tab_paths[i], data->tab_args[i], NULL) == -1)
				ft_perror("failed to exec in red3_proc\n");
		}
		exit(0);
	}
}

void	red4_proc(t_data *data, t_process *temp, char **env, int i)
{
	data->pid1[i] = fork();
	if (data->pid1[i] < 0)
		ft_perror("forking failed\n");
	if (data->pid1[i] == 0)
	{
		data->file[i] = open(ft_ddquote(data->inout->file, 0),
				O_RDWR | O_APPEND | O_CREAT, 0644);
		if (data->file[i] < 0)
			ft_perror("\033[2K\r\033[0;31mError\033[0m : file creation failed");
		if (temp->in_prev != 0)
			if (dup2(data->fd[2 * data->ind - 2], STDIN_FILENO) == -1)
				ft_perror("dup2 n1 failed in pipe_proc");
		if (data->inout->next == NULL)
			if (dup2(data->file[i], STDOUT_FILENO) == -1)
				ft_perror("dup2 n1 failed in red_proc");
		close_pipes(data);
		close(data->file[i]);
		if (temp->command != NULL)
		{
			if (data->inout->next == NULL)
			{
				data->tab_args[i] = ft_dquote(ft_splitd(temp->cmd_arg, ' '), 0, 0);
				data->tab_paths[i] = ft_check_arg(temp->command, env);
				if (execve(data->tab_paths[i], data->tab_args[i], NULL) == -1)
					ft_perror("failed to exec in red_proc\n");
			}
		}
		exit(0);
	}
}

int	ft_execute_cmd(t_process *proc, char **env, char **penv)
{
	t_data		data;
	int			i;
	t_process	*temp;
	t_inout		*temp2;
	int			j;
	int			status;
	t_inout		*tmp;
	char		*line;

	data.tab_env = penv;
	temp = proc;
	if (!ft_strncmp(temp->command, "exit", 4))
		ft_exit(1);
	temp2 = temp->inout;
	if (!temp2 || (temp2 && temp2->type == 3))
		i = 1;
	else
		i = 0;
	while (temp2)
	{
		if (temp2 && temp2->type != 3)
			i++;
		temp2 = temp2->next;
	}
	while (temp->next != NULL)
	{
		temp = temp->next;
		temp2 = temp->inout;
		if (temp2)
		{
			while (temp2)
			{
				if (temp2 && temp2->type != 3)
				{
					i++;
					temp2 = temp2->next;
				}
				if (temp2 && temp2->type == 3)
				{
					i++;
					while (temp2 && temp2->type == 3)
						temp2 = temp2->next;
				}
			}
		}
		else
			if (temp)
				i++;
	}
	temp = proc;
	if (!ft_malloc_struct(&data, i))
		ft_perror("malloc failed\n");
	create_pipes(&data);
	if (i == 1 && temp->inout == 0)
	{
		one_proc(&data, temp, env);
		j = 0;
	}
	else
	{
		i--;
		j = i;
		//ft_printf("I : %d\n", i);
		data.ind = 0;
		data.inout = NULL;
		while (i >= 0)
		{
			if (!data.inout)
				data.inout = temp->inout;
			while (i >= 0 && (!data.inout))
			{
				pipe_proc(&data, temp, env, i);
				temp = temp->next;
				data.ind++;
				i--;
				if (temp)
					data.inout = temp->inout;
			}
			while (i >= 0 && data.inout != 0 && data.inout->type == 2)
			{
				red2_proc(&data, temp, env, i);
				data.inout = data.inout->next;
				i--;
			}
			while (i >= 0 && data.inout != 0 && data.inout->type == 1)
			{
				red_proc(&data, temp, env, i);
				data.inout = data.inout->next;
				i--;
			}
			if (i >= 0 && data.inout != 0 && data.inout->type == 3)
			{
				tmp = data.inout;
				line = NULL;
				close(data.fd[2 * data.ind + 1]);
				if (pipe(data.fd + 2 * data.ind) < 0)
					ft_perror("nooope");
				while (data.inout->next != NULL && data.inout->next->type == 3)
					data.inout = data.inout->next;
				if (!ft_strncmp(tmp->file, data.inout->file, ft_strlen(tmp->file)))
				{
					line = readline("heredoc> ");
					if (ft_strncmp(line, data.inout->file, ft_strlen(line)))
					{
						write(data.fd[2 * data.ind + 1], line, ft_strlen(line));
						write(data.fd[2 * data.ind + 1], "\n", 1);
					}
				}
				while (ft_strncmp(tmp->file, data.inout->file, ft_strlen(tmp->file)))
				{
					line = readline("heredoc> ");
					if (!ft_strncmp(line, tmp->file, ft_strlen(line))
						&& tmp->next && tmp->next->type == 3)
						tmp = tmp->next;
					if (ft_strncmp(tmp->file, data.inout->file, ft_strlen(tmp->file)))
						free(line);
				}
				while (ft_strncmp(line, data.inout->file, ft_strlen(line)))
				{
					if (line)
						free (line);
					line = readline("heredoc> ");
					if (ft_strncmp(line, data.inout->file, ft_strlen(line)))
					{
						write(data.fd[2 * data.ind + 1], line, ft_strlen(line));
						write(data.fd[2 * data.ind + 1], "\n", 1);
					}
				}
				free(line);
				red3_proc(&data, temp, env, i);
				data.inout = data.inout->next;
				i--;
			}
			if (i >= 0 && data.inout != 0 && data.inout->type == 4)
			{
				red4_proc(&data, temp, env, i);
				data.inout = data.inout->next;
				i--;
			}
			if (temp && temp->inout && !data.inout)
			{
				temp = temp->next;
				data.ind++;//be carefull
			}
		}
	}
	i = j;
	close_pipes(&data);
	while (j >= 0)
	{
		waitpid(data.pid1[j], &status, 0);
		j--;
	}
	free_exec(&data, i);
	return (0);
}
