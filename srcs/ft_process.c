/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 15:33:50 by tnard             #+#    #+#             */
/*   Updated: 2022/01/05 15:33:50 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
* ft_w_is_space(char *str)
* desc : return the number of space in str
*/

static int ft_w_is_space(char *str)
{
	int x;

	x = 0;
	while (str[x] && str[x] == ' ')
		x++;
	return (x);
}

/*
* ft_word_len(char *str)
* desc : return the len of the word
*/

static int ft_word_len(char *str)
{
	int x;

	x = 0;
	while (str[x] && str[x] != ' ' && str[x] != '<' && str[x] != '>')
		x++;
	return (x);
}

/*
* ft_malloc_process(t_process **prev)
* desc : return the next of t_process malloced
* params : prev to add next malloced
*/

static void ft_malloc_process(t_process **prev)
{
	t_process *new;

	new = malloc(sizeof(t_process));
	if (!new)
		return;
	new->command = NULL;
	new->cmd_arg = NULL;
	new->inout_file = NULL;
	new->path = NULL;
	new->args = NULL;
	new->out_next = 0;
	new->out_prev = 0;
	new->input = NULL;
	new->in_prev = 0;
	new->in_next = 0;
	new->type = NULL;
	(*prev)->next = new;
}

/*
* ft_add_char(char *str, char c)
* desc : desc malloc a string and add a char at the end of it
* params : str to add c
*/

static char *ft_add_char(char *str, char c)
{
	char *new;
	int x;

	x = 0;
	ft_printf("on cherche le crash : %s\n", str);
	new = malloc(sizeof(char) * (ft_strlen(str) + 1));
	ft_printf("on cherche le crash\n");
	if (!new)
		return (NULL);
	while (str[x])
	{
		new[x] = str[x];
		x++;
	}
	new[x] = c;
	new[x + 1] = '\0';
	free(str);
	return (new);
}

/*
* int ft_quote(t_process **process, int x, int y, char **split)
* desc : parse the curent line after the <> and return the new process
* todo : free(process) if err ?
*/

int ft_quote(t_process **process, int x, int y, char **split)
{
	char	c;

	c = split[x][y];
	(*process)->type = malloc(sizeof(char));
	(*process)->type = ft_add_char((*process)->type, c);
	y += ft_w_is_space(split[x] + y + 1) + 1;
	if (ft_word_len(split[x] + y) != 0)
	{
		(*process)->inout_file = malloc(sizeof(char) * ft_word_len(split[x] + y) + 1);
		ft_strlcpy((*process)->inout_file, split[x] + y, ft_word_len(split[x] + y) + 1);
		ft_printf("(3) inout : %s\n", (*process)->inout_file);
		y += ft_word_len(split[x] + y) + 1;
		y += ft_w_is_space(split[x] + y);
		ft_printf("(4) str pos : %s\n", split[x] + y);
		if (!split[x][y] && !split[x + 1])
		{
			ft_printf("je sort la 1\n");
			return (-1);
		}
		while (split[x][y] == c)
		{
			ft_malloc_process(&(*process));
			(*process) = (*process)->next;
			if (ft_quote(&(*process), x, y, split) == -1)
			{
				ft_printf("je sort la 2\n");
				return (-1);
			}
			y += ft_quote(&(*process), x, y, split);
		}
	}
	return (-1);
}

/*
* ft_create_process(char *str, int *status)
* desc : parse the string and create all process
* params : str to parse and status to return
* todo : free(process) when error and some thing else
* todo : split of "|"
*/

t_process *ft_create_process(char *str, int *status)
{
	t_process *process;
	t_process *tmp;
	char **split;
	int x;
	int y;
	int i;
	char a;

	x = 0;
	a = 0;
	split = ft_split(str, '|');
	while (split[x])
	{
		(*status) = 0;
		ft_malloc_process(&process);
		process = process->next;
		if (x == 0)
			tmp = process;
		y = 0;
		y += ft_w_is_space(split[x]);
		if (!split[x][y])
			return (NULL);
		if (split[x][y] == '<' || split[x][y] == '>')
		{
			// cas speciaux (< file) / (> file) / (>> file)
		}
		else // init command
		{
			process->command = malloc(sizeof(char) * ft_word_len(split[x] + y) + 1);
			if (!process->command)
				return (NULL);
			ft_strlcpy(process->command, split[x] + y, ft_word_len(split[x] + y) + 1);
			ft_printf("(0) command : %s\n", process->command);
			y += ft_word_len(split[x] + y);
			y += ft_w_is_space(split[x] + y);
			// ft_printf("(1) str pos : %s\n", split[x] + y);
			if (x == -1 && (split[x][y] == '<' || split[x][y] == '>'))
			{
				// cas de l'output
				ft_printf("cas pas coder\n");
			}
			else
			{
				i = 0;
				if (process->command)
					process->cmd_arg = ft_strjoin(process->command, " ");
				while (split[x][y])
				{
					if (split[x][y] == '\'' || split[x][y] == '\"')
					{
						if (a == split[x][y] && i == 0)
							i++;
						else if (a == split[x][y])
							i--;
						else
						{
							a = split[x][y];
							i++;
						}
					}
					if (split[x][y] && (split[x][y] == '<' || split[x][y] == '>') && i == 0)
					{
						if (ft_quote(&process, x, y, split) == -2)
						{
							ft_printf("gg2\n");
							*status = 0;
							return (tmp);
						}
						else if (ft_quote(&process, x, y, split) != -1)
							y += ft_quote(&process, x, y, split);
						*status = -2;
					}
					else if (split[x][y] && process->command && (*status) != -2)
						process->cmd_arg = ft_add_char(process->cmd_arg, split[x][y]);
					y++;
				}
				ft_printf("(2) cmd_arg : %s\n", process->cmd_arg);
			}
		}
		x++;
	}
	(*status) = 1;
	return (tmp);
}