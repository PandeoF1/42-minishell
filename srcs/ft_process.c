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
	new->inout = NULL;
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
		(*prev) = new;
}

/*
 * ft_len_next(char *str)
 * desc : count all char in str until next > <
 * params : str to count
 */

int	ft_len_quote(char *str)
{
	int		x;
	char	c;

	x = 0;
	while (str[x] && str[x] != ' ' && str[x] != '<' && str[x] != '>')
	{
		if (str[x] == '\'' || str[x] == '"')
		{
			c = str[x++];
			while (str[x] && str[x] != c)
				x++;
			if (str[x] && (str[x] != ' ' && str[x] != '<' && str[x] != '>'))
				x++;
		}
		else
			x++;
	}
	return (x);
}

int	ft_len_next(char *str)
{
	int		x;
	char	c;

	x = 0;
	//ft_printf("inside ft_len_next first char : .%c.\n", str[x]);
	while (str[x] && str[x] != ' ')
	{
		//ft_printf("a %d\n", x);
		if (str[x] == '\'' || str[x] == '"')
		{
			c = str[x++];
			while (str[x] && str[x] != c)
				x++;
		}
		else
			x++;
	}
	//ft_printf("quit ft_len_next\n");
	return (x);
}

/*
 * ft_create_inout(void)
 * desc : return a malloced struct of t_inout
 * params : void
 */

t_inout	*ft_create_inout(void)
{
	t_inout	*inout;

	inout = malloc(sizeof(t_inout));
	if (!inout)
		return (NULL);
	inout->type = 0;
	inout->file = NULL;
	inout->next = NULL;
	return (inout);
}

char	*ft_strndup(const char *s, size_t n)
{
	char			*res;
	unsigned int	i;

	i = 0;
	res = malloc(sizeof(char) * (n + 1));
	if (!res)
		return (NULL);
	if (res == NULL)
		return (NULL);
	while (i < n)
	{
		res[i] = s[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

void	ft_push_inout(t_inout **inout, t_inout *new)
{
	t_inout	*tmp;

	tmp = *inout;
	if (!tmp)
	{
		*inout = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

/*
 * int ft_quote(t_process **process, int x, int y, char **split)
 * desc : parse the curent line after the <> and return the new process
 * todo : free(process) if err ?
 */

int	ft_quote(t_process **process, int x, int *y, char **split)
{
	char	c;
	int		i;
	t_inout	*tmp;

	i = 0;
	c = split[x][(*y)];
	tmp = ft_create_inout();
	if (split[x][(*y) + 1] && (split[x][(*y) + 1] == c))
	{
		if (c == '<')
			tmp->type = 3;
		else if (c == '>')
			tmp->type = 4;
		(*y)++;
	}
	else
	{
		if (c == '<')
			tmp->type = 1;
		else if (c == '>')
			tmp->type = 2;
	}
	(*y) += ft_w_is_space(split[x] + (*y) + 1) + 1;
	tmp->file = ft_strndup(split[x] + (*y),
			ft_len_quote(split[x] + (*y)));
	(*y) += ft_len_next(split[x] + (*y));
	ft_push_inout(&(*process)->inout, tmp);
	return (-1);
}

char *ft_strnjoin(char *s1, char *s2, int n)
{
	int		i;
	int		j;
	char	*str;
	int		k;

	k = 0;
	j = ft_strlen(s1) + n + 1;
	str = (char *)malloc(sizeof(char) * j);
	if (!str)
		return (NULL);
	i = -1;
	while (++i < ft_strlen(s1))
		str[i] = s1[i];
	while (n-- && s2[k])
		str[i++] = s2[k++];
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
	t_process	*process;
	t_process	*tmp;
	char		**split;
	int			x;
	int			y;

	tmp = malloc(sizeof(t_process));
	x = 0;
	split = ft_splitd(str, '|');
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
		y += ft_w_is_space(split[x] + y);
		process->command = ft_strndup(split[x] + y, ft_word_len(split[x] + y));
		process->cmd_arg = ft_strdup(process->command);
		process->cmd_arg = ft_strnjoin(process->cmd_arg, " ", 1);
		y += ft_word_len(split[x] + y);
		while (split[x][y])
		{
			y += ft_w_is_space(split[x] + y);
			if (split[x][y] == '<' || split[x][y] == '>')
			{
				if (ft_quote(&process, x, &y, split) == -2)
				{
					(*status) = 0;
					ft_free_split(split);
					return (tmp);
				}
			}
			else if (split[x][y])
			{
				process->cmd_arg = ft_strnjoin(process->cmd_arg,
						split[x] + y, ft_len_quote(split[x] + y));
				process->cmd_arg = ft_strnjoin(process->cmd_arg, " ", 1);
				y += ft_len_quote(split[x] + y);
			}
		}
		if (split[x + 1])
			process->type = ft_strdup("|");
		x++;
	}
	ft_free_split(split);
	(*status) = 1;
	return (tmp);
}