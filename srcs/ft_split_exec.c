/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaffroy <asaffroy@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 13:02:58 by asaffroy          #+#    #+#             */
/*   Updated: 2022/01/06 16:22:42 by asaffroy         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_is_charset(char str, char *charset, t_data *data, int a)
{
	int	x;

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

static int	ft_wordlen(char *str, char *charset, t_data *data, int a)
{
	int	i;
	int	y;

	if (data->check[a] == 1)
		y = 1;
	else
		y = 0;
	i = 0;
	while (str[i] && ((ft_is_charset(str[i], charset, data, a) == 0)
			|| (data->check[a] == 1 && y == 1)))
		i++;
	if (data->check[a] == 1)
		data->check[a]=0;
	return (i);
}

static int	ft_wordcount(char *str, char *charset, t_data *data, int a)
{
	int	i;
	int	j;

	j = 0;
	while (*str)
	{
		while (*str && ft_is_charset(*str, charset, data, a) == 1
			&& data->check[a] != 1)
			str++;
		if (data->check[a] == 1)
			str++;
		i = ft_wordlen(str, charset, data, a);
		str += i;
		if (i)
			j++;
	}
	return (j);
}

static char	*ft_strdupp(char *src, int j)
{
	char	*dst;
	int		i;

	i = 0;
	dst = malloc((j + 1) * sizeof(char));
	if (!dst)
		return (0);
	while (i < j && src[i])
	{
		dst[i] = src[i];
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
	size = ft_wordcount((char *)s, charset, data, a);
	dest = malloc((size + 1) * sizeof(char *));
	if (!dest)
		return (0);
	data->check[a] = 0;
	while (i < size)
	{
		if (data->check[a] > 1)
			data->check[a] = 0;
		while (ft_is_charset((char)*s, charset, data, a) && data->check[a] != 1)
			s++;
		ft_printf("youhou n%d : %d\n", a, data->check[a]);
		if (data->check[a] == 1)
			s++;
		j = ft_wordlen((char *)s, charset, data, a);
		dest[i] = ft_strdupp((char *)s, j);
		ft_printf("\n");
		ft_printf("worldlen in n%d : %d\n", a, j);
		s += j;
		i++;
		if (data->check[a] == 2)
			s++;
		ft_printf("youhouloi n%d : %d\n", a, data->check[a]);
		ft_printf("\n");
	}
	dest[size] = 0;
	return (dest);
}
