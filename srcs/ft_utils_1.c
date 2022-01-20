/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 11:27:16 by tnard             #+#    #+#             */
/*   Updated: 2022/01/20 14:09:43 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strnjoin(char *s1, char *s2, int n)
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
	while (++i < (int)ft_strlen(s1))
		str[i] = s1[i];
	while (n-- && s2[k])
		str[i++] = s2[k++];
	str[i] = '\0';
	free(s1);
	return (str);
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

/*
 * ft_w_is_space(char *str)
 * desc : return the number of space in str
*/

int	ft_w_is_space(char *str)
{
	int	x;

	x = 0;
	while (str[x] && str[x] == ' ')
		x++;
	return (x);
}

/*
 * ft_word_len(char *str)
 * desc : return the len of the word
 */

int	ft_word_len(char *str)
{
	int	x;

	x = 0;
	while (str[x] && str[x] != ' ' && str[x] != '<' && str[x] != '>')
		x++;
	return (x);
}

/*
 * ft_len_next(char *str)
 * desc : count all char in str until next > < with quote format
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
