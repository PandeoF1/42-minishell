/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_exec2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaffroy <asaffroy@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 15:05:03 by asaffroy          #+#    #+#             */
/*   Updated: 2022/01/12 15:20:12 by asaffroy         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_is_charset(char str, t_data *data, int a)
{
	int			x;

	x = 0;
	while (data->charset[x])
	{
		//ft_printf("%c\n", str);
		if (str == data->charset[x])
		{
			if (str == '\'' || str == '\"')
				data->check[a]++;
			return (1);
		}
		x++;
	}
	return (0);
}

int	ft_wordlen(char *str, t_data *data, int a)
{
	int			i;
	int			y;

	if (data->check[a] == 1)
		y = 1;
	else
		y = 0;
	i = 0;
	while (str[i] && ((ft_is_charset(str[i], data, a) == 0)
			|| (data->check[a] == 1 && y == 1)
			|| (data->type_char[a] != 0 && str[i] != data->type_char[a])
			|| (data->check[a] == 1 && i > 0 && str[i - 1] != ' ')
			|| (data->check[a] == 2 && str[i + 1] && str[i + 1] != ' ')))
	{
		y = 0;
		if (data->check[a] == 2)
			data->check[a] = 0;
		else
			i++;
	}
	if (data->check[a] == 1)
		data->check[a] = 0;
	return (i);
}

int	ft_wordcount(char *str, t_data *data, int a)
{
	int	i;
	int	j;
	int	x;

	j = 0;
	x = 0;
	while (str[x])
	{
		data->check[a] = 0;
		data->type_char[a] = 0;
		while (str[x] && ft_is_charset(str[x], data, a) == 1
			&& data->check[a] != 1)
			x++;
		if (data->check[a] == 1)
			data->type_char[a] = str[x++];
		i = ft_wordlen(str + x, data, a);
		x += i;
		if (str[x] == '\'' || str[x] == '\"')
			x++;
		if (i)
			j++;
	}
	return (j);
}

int	ft_strdupp_util3(t_data *data, int a, char *dst, char *src)
{
	int	j;

	j = 0;
	if (src[data->i[a]] == '\'' || src[data->i[a]] == '\"')
		j += ft_strdupp_util2(data, a, dst, src);
	else
	{
		if (src[data->i[a]] != '\'' && src[data->i[a]] != '\"')
			dst[data->i[a] - data->dec[a]] = src[data->i[a]];
		else
		{
			data->dec[a]++;
			j++;
		}
	}
	data->i[a]++;
	return (j);
}
