/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaffroy <asaffroy@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 13:02:58 by asaffroy          #+#    #+#             */
/*   Updated: 2022/01/10 12:27:16 by asaffroy         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_is_charset(char str, char *charset, t_data *data, int a)
{
	int			x;

	x = 0;
	while (charset[x])
	{
		if (str == charset[x])
		{
			if (str == '\'' || str == '\"')
				data->check[a]++;
			return (1);
		}
		x++;
	}
	return (0);
}

static int	ft_wordlen2(char *str, char *charset, t_data *data, int a)
{
	int			i;
	int			y;

	if (data->check[a] == 1)
		y = 1;
	else
		y = 0;
	i = 0;
	while (str[i] && ((ft_is_charset(str[i], charset, data, a) == 0)
			|| (data->check[a] == 1 && y == 1)
			|| (data->check[a] == 1 && i > 0 && str[i - 1] != ' ')
			|| (data->check[a] == 2 && str[i + 1] && str[i + 1] != ' ')))
	{
		if (data->check[a] == 2)
			data->check[a] = 0;
		else
			i++;
	}
	if (data->check[a] == 1)
		data->check[a] = 0;
	return (i);
}

static int	ft_wordcount(char *str, char *charset, t_data *data, int a)
{
	int	i;
	int	j;
	int	x;

	j = 0;
	x = 0;
	while (str[x])
	{
		while (str[x] && ft_is_charset(str[x], charset, data, a) == 1
			&& data->check[a] != 1)
			x++;
		if (data->check[a] == 1)
			x++;
		i = ft_wordlen2(str + x, charset, data, a);
		if (str[x + i] && str[x + i] != ' ' && data->check[a] != 2)
			i += ft_wordcount(str + x + i, charset, data, a);
		x += i;
		if (i)
			j++;
	}
	return (j);
}

static char	*ft_strdupp(char *src, int j, t_data *data)
{
	char	*dst;
	int		i;
	int		nb_quote;
	int		dec;

	i = 0;
	nb_quote = 0;
	dec = 0;
	while (src[i] && i < j)
	{
		if (src[i] == '\'' || src[i] == '\"')
		{
			if (src[i] == data->type_char)
				nb_quote++;
		}
		i++;
	}
	j -= nb_quote;
	i = 0;
	dst = malloc((j + 1) * sizeof(char));
	if (!dst)
		return (0);
	while (src[i] && i < j)
	{
		if ((src[i] == '\'' || src[i] == '\"') && data->type_char != 0)
		{
			if (src[i] != data->type_char)
				dst[i - dec] = src[i];
			else
			{
				dec++;
				j++;
			}
		}
		else
		{
			if (src[i] != '\'' && src[i] != '\"')
				dst[i - dec] = src[i];
			else
			{
				dec++;
				j++;
			}
		}
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	**ft_split_exec(char const *s, t_data *data, int a)
{
	char		**dest;
	int			size;
	int			i;
	int			j;
	char		charset[4];

	charset[0] = '\'';
	charset[1] = '\"';
	charset[2] = ' ';
	charset[3] = '\0';
	i = 0;
	data->check[a] = 0;
	data->type_nb = 0;
	size = ft_wordcount((char *)s, charset, data, a);
	dest = malloc((size + 1) * sizeof(char *));
	if (!dest)
		return (0);
	data->check[a] = 0;
	while (i < size)
	{
		data->type_char = 0;
		if (data->check[a] > 1)
			data->check[a] = 0;
		while (ft_is_charset((char)*s, charset, data, a) && data->check[a] != 1)
			s++;
		if (data->check[a] == 1)
		{
			data->type_char = (char)*s;
			s++;
		}
		j = ft_wordlen2((char *)s, charset, data, a);
		dest[i] = ft_strdupp((char *)s, j, data);
		s += j;
		i++;
		if (data->check[a] == 2)
			s++;
	}
	dest[size] = 0;
	return (dest);
}
