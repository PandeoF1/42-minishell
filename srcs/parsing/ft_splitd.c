/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 11:05:06 by tnard             #+#    #+#             */
/*   Updated: 2022/01/05 11:05:06 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_is_charsetd(char str, char *charset)
{
	while (*charset)
	{
		if (str == *charset)
			return (1);
		charset++;
	}
	return (0);
}

static int	ft_wordlend(char *str, char *charset)
{
	int		i;
	char	c;

	i = 0;
	c = '\0';
	while (str[i])
	{
		if (c == '\0' && (str[i] == '\'' || str[i] == '"'))
			c = str[i];
		else if (c == str[i])
			c = '\0';
		if (c == '\0' && ft_is_charsetd(str[i], charset))
			return (i);
		i++;
	}
	return (i);
}

static int	ft_wordcountd(char *str, char *charset)
{
	int		a;
	char	c;

	a = 1;
	c = '\0';
	while (*str)
	{
		if (c == '\0' && (*str == '\'' || *str == '\"'))
			c = *str;
		else if (c == *str)
			c = '\0';
		if (ft_is_charsetd(*str, charset)
			&& c == '\0' && ft_strlen(str + 1) > 0)
			a += 1;
		str++;
	}
	return (a);
}

static char	*ft_strduppd(char *src, int j)
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

/*
*	char	**ft_splitd(char const *s, char c)
*	desc : like a ft_split but work with quote
*/

char	**ft_splitd(char const *s, char c)
{
	char		**dest;
	int			size;
	int			j;
	int			i;
	char		charset[2];

	i = 0;
	charset[0] = c;
	charset[1] = '\0';
	size = ft_wordcountd((char *)s, charset);
	dest = malloc((size + 1) * sizeof(char *));
	if (!dest)
		return (0);
	while (i < size)
	{
		while (ft_is_charsetd((char)*s, charset))
			s++;
		j = ft_wordlend((char *)s, charset);
		dest[i] = ft_strduppd((char *)s, j);
		s += j;
		i++;
	}
	dest[size] = 0;
	return (dest);
}
