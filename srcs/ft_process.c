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

static void	ft_malloc_process(t_process **prev)
{
	t_process	*new;

	new = malloc(sizeof(t_process));
	if (!new)
		return ;
	new->command = NULL;
	new->cmd_arg = NULL;
	new->in_file = NULL;
	new->out_file = NULL;
	new->inout_file = NULL;
	new->path = NULL;
	new->args = NULL;
	new->out_next = 0;
	new->out_prev = 0;
	new->input = NULL;
	new->in_prev = 0;
	new->in_next = 0;
	new->type = NULL;
	new->next = NULL;
	if (*prev)
		(*prev)->next = new;
	else
		(*prev)= new;
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
	////ft_printf("on cherche le crash : %s\n", str);
	new = malloc(sizeof(char) * (ft_strlen(str) + 1));
	////ft_printf("on cherche le crash\n");
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
 * ft_len_next(char *str)
 * desc : count all char in str until next > <
 * params : str to count
 */

int ft_len_next(char *str)
{
	int x;

	x = 0;
	while (str[x] && str[x] != '<' && str[x] != '>')
		x++;
	return (x);
}

/*
 * int ft_quote(t_process **process, int x, int y, char **split)
 * desc : parse the curent line after the <> and return the new process
 * todo : free(process) if err ?
 */

int	ft_quote(t_process **process, int x, int y, char **split)
{
	char	c;
	int		i;

	i = 0;
	c = split[x][y];
	if ((*process)->command != NULL)
	{
		ft_malloc_process(&(*process));
		(*process) = (*process)->next;
	}
	if (split[x][y + 1] && (split[x][y + 1] == c))
	{
		(*process)->type = malloc(sizeof(char) * 3);
		(*process)->type[0] = c;
		(*process)->type[1] = c;
		(*process)->type[2] = '\0';
		y++;
	}
	else
	{
		(*process)->type = malloc(sizeof(char) * 2);
		(*process)->type[0] = c;
		(*process)->type[1] = '\0';
	}
	y += ft_w_is_space(split[x] + y + 1) + 1;
	if (ft_word_len(split[x] + y) != 0)
	{
		(*process)->inout_file = malloc(sizeof(char) * ft_len_next(split[x] + y) + 1);
		ft_strlcpy((*process)->inout_file, split[x] + y, ft_len_next(split[x] + y) + 1);
		////ft_printf("(3) inout : %s\n", (*process)->inout_file);
		////ft_printf("(3.4) test : %s\n", split[x] + y);
		////ft_printf("(4) len : %d\n", ft_len_next(split[x] + y));
		y += ft_len_next(split[x] + y);
		/*y += ft_word_len(split[x] + y) + 1;
		y += ft_w_is_space(split[x] + y);*/
		////ft_printf("(4) str pos : %s\n", split[x] + y);
		if (!split[x][y] && !split[x + 1])
		{
			////ft_printf("je sort laa 1\n");
			return (-1);
		}
		while (split[x][y] == c)
		{
			ft_malloc_process(&(*process));
			(*process) = (*process)->next;
			i = ft_quote(&(*process), x, y, split);
			if (i == -1)
			{
				////ft_printf("je sort laa 2\n");
				return (-1);
			}
			y += i;
		}
	}
	else
		return (-2);
	return (-1);
}

char *ft_strnjoin(char *s1, char *s2, int n) // free s1
{
	int i;
	int j;
	char *str;
	int k;

	k = 0;
	j = ft_strlen(s1) + ft_strlen(s2) - (ft_strlen(s2) - n);
	if (!(str = (char *)malloc(sizeof(char) * (j + 1))))
		return (NULL);
	i = -1;
	while (++i < ft_strlen(s1))
		str[i] = s1[i];
	while (i <= j && s2[k])
	{
		str[i++] = s2[k++];
	}
	str[i] = '\0';
	free(s1);
	return (str);
}

/*
 * ft_create_process(char *str, int (*status))
 * desc : parse the string and create all process
 * params : str to parse and status to return
 * todo : free(process) when error and some thing else
 * todo : split of "|"
 */

t_process *ft_create_process(char *str, int *status)
{
	t_process *process;
	int	test;
	t_process *tmp;
	char **split;
	int x;
	int y;
	int i;
	char a;

	tmp = malloc(sizeof(t_process));
	x = 0;
	test = 0;
	a = 0;
	split = ft_split(str, '|');
	while (split[x])
	{
		(*status) = 0;
		if (x == 0)
		{
			ft_malloc_process(&tmp);
			process = tmp->next;
			free(tmp);
		}
		else
		{
			ft_malloc_process(&process);
			process = process->next;
		}
		if (x == 0)
			tmp = process;
		y = 0;
		y += ft_w_is_space(split[x]);
		if (!split[x][y] || ft_strlen(split[x]) == 0)
			return (NULL);
		if (split[x][y] == '<' || split[x][y] == '>')
		{
			// cas speciaux (< file) / (> file) / (>> file)
			(*status) = ft_quote(&process, x, y, split);
			if ((*status) == -2)
			{
				//ft_printf("gg1\n");
				(*status) = 0;
				ft_free_split(split);
				return (tmp);
			}
			else if ((*status) != -1)
				y += (*status);
			(*status) = -2;
		}
		else // init command
		{
			process->command = malloc(sizeof(char) * ft_word_len(split[x] + y) + 1);
			if (!process->command)
				return (NULL);
			ft_strlcpy(process->command, split[x] + y, ft_word_len(split[x] + y) + 1);
			////ft_printf("(0) command : %s\n", process->command);
			y += ft_word_len(split[x] + y);
			y += ft_w_is_space(split[x] + y);
			// ////ft_printf("(1) str pos : %s\n", split[x] + y);
			if (x == -1 && (split[x][y] == '<' || split[x][y] == '>'))
			{
				// cas de l'output
				////ft_printf("cas pas coder\n");
			}
			else
			{
				i = 0;
				if (process->command)
					process->cmd_arg = ft_strjoin(process->command, " ");
				while (split[x][y]) // stack smashing
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
						(*status) = ft_quote(&process, x, y, split);
						if ((*status) == -2)
						{
							//ft_printf("gg2\n");
							(*status) = 0;
							ft_free_split(split);
							return (tmp);
						}
						else if ((*status) != -1)
							y += (*status);
						(*status) = -2;
					}
					else if (split[x][y] && process->command && ((*status)) != -2)
					{ // process->cmd_arg = ft_add_char(process->cmd_arg, split[x][y]);
						process->cmd_arg = ft_strnjoin(process->cmd_arg, split[x] + y, ft_len_next(split[x] + y) - 1);
						////ft_printf("je copie : %d - %s\n", ft_len_next(split[x] + y), process->cmd_arg);
						y += ft_len_next(split[x] + y) - 1;
						////ft_printf("(2) str pos : %s\n", split[x] + y);
					}
					y++;
				}
				////ft_printf("(2) cmd_arg : %s\n", process->cmd_arg);
			}
		}
		x++;
	}
	//ft_printf("gg3\n");
	ft_free_split(split);
	(*status) = 1;
	return (tmp);
}
