/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaffroy <asaffroy@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 11:15:22 by asaffroy          #+#    #+#             */
/*   Updated: 2022/01/19 18:32:08 by asaffroy         ###   ########lyon.fr   */
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

/*
*char	*ft_check_arg(char *cmd, char **env)
*cmd	command to search in /bin
*env	env of the shell
*error	not norminette
*do :	check if the command exist and if we have the rights to use it 
*/

char	*ft_check_arg(char *cmd, char *env)
{
	int			i;
	char		**tab;
	char		*try;

	if (!access(cmd, F_OK))
	{
		if (!access(cmd, R_OK))
			return (cmd);
		else
			ft_perror("\033[2K\r\033[0;31mError\033[0m : permission denied");
	}
	cmd = ft_strjoin("/", cmd);
	tab = ft_split(env, ':');
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
	ft_perror("command not found");
	return (0);
}

/*
*void	father_proc(t_data *data, char **argv, char **env)
*data	my struct with all data needed
*env	env of the shell
*argv	tab of args received at launch of prog
*do :	exec one of the cmd
*/

// void	father_proc(t_data *data, t_process *temp, char *env)
// {
// 	close (data->fd[1]);
// 	if (temp->output != NULL)
// 	{
// 		data->file2 = open(temp->input, O_RDWR | O_TRUNC | O_CREAT, 0644);
// 		if (data->file2 < 0)
// 			ft_perror("\033[2K\r\033[0;31mError\033[0m : outfile creation failed");
// 	}
// 	data->args_of_2 = ft_split(temp->cmd_arg, ' ');
// 	data->path_of_2 = ft_check_arg(temp->command, env);
// 	if (temp->output != NULL)
// 		if (dup2(data->file2, STDOUT_FILENO) == -1)
// 			ft_perror("dup2 n1 failed in father_proc");
// 	if (temp->input != NULL)
// 		if (dup2(data->fd[0], STDIN_FILENO) == -1)
// 			ft_perror("dup2 n2 failed in father_proc");
// 	close(data->fd[0]);
// 	if (temp->output != NULL)
// 		close(data->file2);
// 	if (execve(data->path_of_2, data->args_of_2, NULL) == -1)
// 		ft_perror("failed to exec in father_proc");
// }

/*
*void	child_proc(t_data *data, char **argv, char **env)
*data	my struct with all data needed
*env	env of the shell
*argv	tab of args received at launch of prog
*do :	exec one of the cmd
*/

// void	child_proc(t_data *data, t_process *temp, char *env)
// {
// 	close (data->fd[0]);
// 	if (temp->input != NULL)
// 	{
// 		data->file1 = open(temp->args, O_RDONLY);
// 		if (data->file1 < 0)
// 			ft_perror("\033[2K\r\033[0;31mError\033[0m : couldn't find infile");
// 	}
// 	data->args_of_1 = ft_split(temp->cmd_arg, ' ');
// 	data->path_of_1 = ft_check_arg(temp->command, env);
// 	if (temp->input != NULL)
// 		if (dup2(data->file1, STDIN_FILENO) == -1)
// 			ft_perror("dup2 n1 failed in child_proc");
// 	if (temp->output != NULL)
// 		if (dup2(data->fd[1], STDOUT_FILENO) == -1)
// 			ft_perror("dup2 n2 failed in child_proc");
// 	close(data->fd[1]);
// 	close(data->file1);
// 	if (execve(data->path_of_1, data->args_of_1, NULL) == -1)
// 		ft_perror("failed to exec in child_proc");
// }

void	create_pipes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_cmd - 1)
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
	while (i < 2 * (data->nb_cmd - 1))
	{
		close(data->fd[i]);
		i++;
	}
}

void	free_exec(t_data *data, int i)
{
	int			j;

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
	// if (data->tab_paths) need to be free
	// {
	// 	while (data->tab_paths[j] != NULL)
	// 	{
	// 		free(data->tab_paths[j]);
	// 		ft_printf("freed\n");
	// 		j++;
	// 	}
	// }
	// if (data->tab_paths) need to be free
	// 	free(data->tab_paths);
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
	// free(data->file);
}

void	pipe_proc(t_data *data, t_process *temp, char *env, int i)
{
	data->pid1[i] = fork();
	if (data->pid1[i] < 0)
		ft_perror("forking failed\n");
	if (data->pid1[i] == 0)
	{
		data->tab_args[i] = ft_splitd(temp->cmd_arg, ' ');
		data->tab_paths[i] = ft_check_arg(temp->command, env);
		if (temp->in_prev != 0)
		{
			if (dup2(data->fd[2 * data->ind - 2], STDIN_FILENO) == -1)
				ft_perror("dup2 n1 failed in pipe_proc");
		}
		if (temp->out_next != 0)
		{
			if (dup2(data->fd[2 * data->ind + 1], STDOUT_FILENO) == -1)
				ft_perror("dup2 n2 failed in pipe_proc");
		}
		close_pipes(data);
		if (execve(data->tab_paths[i], data->tab_args[i], NULL) != 0)
			ft_perror("failed to exec in pipe_proc");
	}
}

void	one_proc(t_data *data, t_process *temp, char *env)
{
	data->pid1[0] = fork();
	if (data->pid1[0] < 0)
		ft_perror("forking failed\n");
	if (data->pid1[0] == 0)
	{
		close_pipes(data);
		data->tab_args[0] = ft_dquote(ft_splitd(temp->cmd_arg, ' '), 0, 0);
		data->tab_paths[0] = ft_check_arg(temp->command, env);
		if (execve(data->tab_paths[0], data->tab_args[0], NULL) == -1)
			ft_perror("failed to exec in child_proc");
	}
}

void	red_proc(t_data *data, t_process *temp, char *env, int i)
{
	data->pid1[i] = fork();
	if (data->pid1[i] < 0)
		ft_perror("forking failed\n");
	if (data->pid1[i] == 0)
	{
		data->file[i] = open(data->inout->file,
				O_RDWR | O_TRUNC | O_CREAT, 0644);
		if (data->file[i] < 0)
			ft_perror("\033[2K\r\033[0;31mError\033[0m : file creation failed");
		if (temp->in_prev != 0)
		{
			data->fd1[i] = dup(data->fd[2 * data->ind - 2]);
			if (dup2(data->fd1[i], STDIN_FILENO) == -1)
				ft_perror("dup2 n1 failed in pipe_proc");
		}
		if (dup2(data->file[i], STDOUT_FILENO) == -1)
			ft_perror("dup2 n1 failed in red_proc");
		close_pipes(data);
		close(data->file[i]);
		if (temp->command != NULL)
		{
			data->tab_args[i] = ft_splitd(temp->cmd_arg, ' ');
			data->tab_paths[i] = ft_check_arg(temp->command, env);
			if (execve(data->tab_paths[i], data->tab_args[i], NULL) == -1)
				ft_perror("failed to exec in red_proc\n");
		}
		exit(0);
	}
}

void	red2_proc(t_data *data, t_process *temp, char *env, int i)
{
	data->pid1[i] = fork();
	if (data->pid1[i] < 0)
		ft_perror("forking failed\n");
	if (data->pid1[i] == 0)
	{
		data->file[i] = open(data->inout->file, O_RDWR);
		if (data->file[i] < 0)
			ft_perror("minishell: no such file or directory");
		if (dup2(data->file[i], STDIN_FILENO) == -1)
			ft_perror("dup2 n1 failed in red2_proc");
		close_pipes(data);
		close(data->file[i]);
		if (temp->command != NULL)
		{
			data->tab_args[i] = ft_splitd(temp->cmd_arg, ' ');
			data->tab_paths[i] = ft_check_arg(temp->command, env);
			if (execve(data->tab_paths[i], data->tab_args[i], NULL) == -1)
				ft_perror("failed to exec in red_proc\n");
		}
		exit (0);
	}
}

int ft_malloc_struct(t_data *data, int	i)
{
	int	j;

	j = -1;
	data->fd = (int *)malloc(sizeof(int) * i * 2);
	if (!data->fd)
		return (0);
	data->check = (int *)malloc(sizeof(int) * i);
	if (!data->check)
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
	data->fd1 = malloc(sizeof(int) * i);
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

int	ft_execute_cmd(t_process *proc, char *env)
{
	t_data		data;
	int			i;
	t_process	*temp;
	t_inout		*temp2;
	int			j;
	int			check;
	int			status;

	temp = proc;
	temp2 = temp->inout;
	i = 0;
	if (temp->next != NULL)
		i = 1;
	while (temp->inout != 0)
	{
		i++;
		temp->inout = temp->inout->next;
	}
	temp->inout = temp2;
	while (temp->next != NULL)
	{
		temp = temp->next;
		if (!temp->inout)
			i++;
		temp2 = temp->inout;
		while (temp->inout != 0)
		{
			i++;
			temp->inout = temp->inout->next;
		}
		temp->inout = temp2;
	}
	temp = proc;
	if (i == 0 && temp->inout == 0)
	{
		i++;
		j = -1;
	}
	if (!ft_malloc_struct(&data, i))
		ft_perror("malloc failed\n");
	create_pipes(&data);
	if (i == 1 && temp->inout == 0 && j == -1)
	{
		one_proc(&data, temp, env);
		j = 0;
	}
	else
	{
		i--;
		j = i;
		data.ind = 0;
		while (i >= 0)
		{
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
				red_proc(&data, temp, env, i);
				data.inout = data.inout->next;
				i--;
			}
			while (i >= 0 && data.inout != 0 && data.inout->type == 1)
			{
				red2_proc(&data, temp, env, i);
				data.inout = data.inout->next;
				i--;
			}
			if (temp && temp->inout)
				temp = temp->next;
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
/*
int	main(void)
{
	t_process	*temp;
	char		*env;

	env = getenv("PATH");
	temp = malloc(sizeof(t_process));
	temp->command = ft_strdup("cat");
	temp->cmd_arg = ft_strdup("cat ../t");
	temp->path = 0;
	temp->args = 0;
	temp->out_next = 0;
	temp->input = 0;
	temp->out_file = ft_strdup("b");
	temp->type = ft_strdup(">");
	temp->in_prev = 0;
	//temp->next = NULL;
	temp->next = malloc(sizeof(t_process));
	temp->next->command = NULL;
	temp->next->cmd_arg = NULL;
	temp->next->path = 0;
	temp->next->args = 0;
	temp->next->out_next = 1;
	temp->next->input = 0;
	temp->next-> type = 0;
	temp->out_file = 0;
	temp->next->in_prev = 1;
	temp->next->next = NULL;
	// temp->next->next = malloc(sizeof(t_process));
	// temp->next->next->command = ft_strdup("grep");
	// temp->next->next->cmd_arg = ft_strdup("grep e");
	// temp->next->next->path = 0;
	// temp->next->next->args = 0;
	// temp->next->next->out_next = 1;
	// temp->next->next->input = 0;
	// temp->next->next-> type = ft_strdup("|");
	// temp->next->next->in_prev = 1;
	// temp->next->next->next = malloc(sizeof(t_process));
	// temp->next->next->next->command = ft_strdup("grep");
	// temp->next->next->next->cmd_arg = ft_strdup("grep j");
	// temp->next->next->next->path = 0;
	// temp->next->next->next->args = 0;
	// temp->next->next->next->out_next = 1;
	// temp->next->next->next->input = 0;
	// temp->next->next->next-> type = ft_strdup("|");
	// temp->next->next->next->in_prev = 1;
	// //temp->next->next->next->next = NULL;
	// temp->next->next->next->next = malloc(sizeof(t_process));
	// temp->next->next->next->next->command = ft_strdup("mkdir");
	// temp->next->next->next->next->cmd_arg = ft_strdup("mkdir \"te'st\" \"lb\"hv\"ur\" gythb yb hu hbuyb'j'ub 'hh'");
	// temp->next->next->next->next->path = 0;
	// temp->next->next->next->next->args = 0;
	// temp->next->next->next->next->out_next = 0;
	// temp->next->next->next->next->input = 0;
	// temp->next->next->next->next-> type = 0;
	// temp->next->next->next->next->in_prev = 1;
	// temp->next->next->next->next->next = NULL;
	ft_execute_cmd(temp, env);
}
*/
