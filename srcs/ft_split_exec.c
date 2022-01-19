/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaffroy <asaffroy@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 13:02:58 by asaffroy          #+#    #+#             */
/*   Updated: 2022/01/19 15:57:38 by asaffroy         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_wordlen2(char *str, t_data *data, int a)
{
	int			i;
	int			y;
	int			g;

	if (data->check[a] == 1)
		y = 1;
	else
		y = 0;
	i = 0;
	g = 0;
	while (str[i] && ((ft_is_charset(str[i], data, a) == 0)
			|| (data->check[a] == 1 && !data->type_char[a])
			|| (data->check[a] == 1 && str[i] != data->type_char[a])
			|| (data->type_char[a] != 0 && (str[i] == '\'' || str[i] == '\"'))
			|| (data->check[a] == 1 && i > 0 && str[i - 1] != ' ')))
	{
		if (data->check[a] == 1 && !data->type_char[a])
			data->type_char[a] = str[i];
		if (str[i] != data->type_char[a])
			g++;
		if (data->check[a] == 2)
		{
			data->type_char[a] = 0;
			data->check[a] = 0;
		}
		i++;
	}
	if (data->check[a] > 0)
		data->check[a] = 0;
	return (g);
}

int	ft_strdupp_util1(t_data *data, int a, int i, char *src)
{
	int	nb_quote;

	nb_quote = 0;
	if ((data->type_char[a] && src[i] == data->type_char[a])
		|| data->check[a] == 0)
	{
		if (data->type_char[a] && src[i] == data->type_char[a])
			data->check[a]++;
		if (data->check[a] == 0)
		{
			data->type_char[a] = src[i];
			data->check[a]++;
		}
		if (data->check[a] == 2)
			data->check[a] = 0;
		nb_quote++;
	}
	return (nb_quote);
}

int	ft_strdupp_util2(t_data *data, int a, char *dst, char *src)
{
	int	j;

	j = 0;
	if (src[data->i[a]] == '\'' || src[data->i[a]] == '\"')
	{
		if (data->type_char[a] && src[data->i[a]] == data->type_char[a])
			data->check[a]++;
		if (!data->check[a])
		{
			data->type_char[a] = src[data->i[a]];
			data->check[a]++;
		}
		if (data->check[a] == 2)
			data->check[a] = 0;
		if (src[data->i[a]] != data->type_char[a])
			dst[data->i[a] - data->dec[a]] = src[data->i[a]];
		else
		{
			data->dec[a]++;
			j++;
		}
	}
	return (j);
}

char	*ft_strdupp(char *src, int j, t_data *data, int a)
{
	char	*dst;

	data->i[a] = 0;
	data->dec[a] = 0;
	data->check[a] = 0;
	dst = malloc((j + 1) * sizeof(char));
	if (!dst)
		return (0);
	while (src[data->i[a]] && data->i[a] < j)
		j += ft_strdupp_util3(data, a, dst, src);
	dst[data->i[a] - data->dec[a]] = '\0';
	return (dst);
}

int	ft_split_exec2(t_data *data, char **s, int a)
{
	int			j;
	char		**temp;
	int			x;

	data->type_nb[a] = 0;
	data->type_char[a] = 0;
	if (data->check[a] > 0)
		data->check[a] = 0;
	while (ft_is_charset(**s, data, a) && data->check[a] != 1)
		(*s)++;
	x = 0;
	if (data->check[a] == 1)
		data->type_char[a] = *s[x++];
	while (ft_is_charset(*s[x], data, a) && (*s[x]) == data->type_char[a])
	{
		x++;
		data->check[a] = 1;
	}
	j = ft_wordlen2(*s + x, data, a);
	if (data->type_nb[a] == 1)
		data->check[a]++;
	return (j);
}

char	**ft_split_exec(char const *s, t_data *data, int a)
{
	char		**dest;
	int			size;
	int			i;
	int			j;

	i = 0;
	data->check[a] = 0;
	size = ft_wordcount((char *)s, data, a);
	ft_printf("size : %d\n", size);
	dest = malloc((size + 1) * sizeof(char *));
	if (!dest)
		return (0);
	data->check[a] = 0;
	while (i < size)
	{
		data->type_char[a] = 0;
		j = ft_split_exec2(data, (char **)&s, a);
		ft_printf("j : %d\n", j);
		dest[i] = ft_strdupp((char *)s, j, data, a);
		if (i == 0)
			s += j;
		else
			s += j + 1;
		i++;
		ft_printf("j : %c\n", *s);
		if (data->check[a] == 1)
			s += 1;
	}
	dest[size] = 0;
	return (dest);
}
