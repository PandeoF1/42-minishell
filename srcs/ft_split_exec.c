/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaffroy <asaffroy@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 13:02:58 by asaffroy          #+#    #+#             */
/*   Updated: 2022/01/13 09:13:59 by asaffroy         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strdupp_util1(t_data *data, int a, int i, char *src)
{
	int	nb_quote;

	nb_quote = 0;
	if (src[i] == data->type_char[a] || data->check[a] == 0)
	{
		if (src[i] == data->type_char[a])
			data->check[a]++;
		if (data->check[a] == 0)
			data->type_char[a] = src[i];
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
		if (src[data->i[a]] == data->type_char[a])
			data->check[a]++;
		if (data->check[a] == 0)
			data->type_char[a] = src[data->i[a]];
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
	char	temp;

	data->i[a] = 0;
	data->dec[a] = 0;
	temp = data->type_char[a];
	while (src[data->i[a]] && data->i[a] < j)
	{
		if (src[data->i[a]] == '\'' || src[data->i[a]] == '\"')
			j -= ft_strdupp_util1(data, a, data->i[a], src);
		data->i[a]++;
	}
	data->i[a] = 0;
	dst = malloc((j + 1) * sizeof(char));
	if (!dst)
		return (0);
	data->type_char[a] = temp;
	data->check[a] = 0;
	if (data->type_nb[a] == 1)
		data->check[a]++;
	while (src[data->i[a]] && data->i[a] < j)
		j += ft_strdupp_util3(data, a, dst, src);
	dst[data->i[a] - data->dec[a]] = '\0';
	return (dst);
}

int	ft_split_exec2(t_data *data, char **s, int a)
{
	int			j;

	data->type_nb[a] = 0;
	data->type_char[a] = 0;
	if (data->check[a] > 0)
		data->check[a] = 0;
	while (ft_is_charset(**s, data, a) && data->check[a] != 1)
	{
		(*s)++;
	}
	if (data->check[a] == 1)
	{
		data->type_nb[a] = 1;
		data->type_char[a] = **s;
		(*s)++;
	}
	j = ft_wordlen(*s, data, a);
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
	dest = malloc((size + 1) * sizeof(char *));
	if (!dest)
		return (0);
	data->check[a] = 0;
	while (i < size)
	{
		j = ft_split_exec2(data, (char **)&s, a);
		dest[i] = ft_strdupp((char *)s, j, data, a);
		s += j;
		i++;
		if (data->check[a] > 0)
			s++;
	}
	dest[size] = 0;
	return (dest);
}
