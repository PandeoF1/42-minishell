/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 10:48:16 by tnard             #+#    #+#             */
/*   Updated: 2022/01/03 10:48:16 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = -1;
	while (++i < n && src[i])
		dest[i] = src[i];
	while (i < n)
		dest[i++] = '\0';
	return (dest);
}

char	*ft_get_file(int fd, int size, int len)
{
	char	buf[2048];
	char	*value;
	char	*tmp;

	value = malloc(sizeof(char));
	if (!value)
		return (NULL);
	len = read(fd, buf, 2048);
	while (len > 0)
	{
		tmp = malloc((size + len + 1) * sizeof(char));
		if (!tmp)
			break ;
		tmp = ft_strncpy(tmp, value, size);
		free(value);
		ft_strncpy(tmp + size, buf, len);
		value = tmp;
		size += len;
		value[size] = '\0';
		len = 0;
	}
	if (len)
		free(value);
	return (value);
}
int	main(void)
{
	char	*tmp;

	while (1)
	{
		ft_putstr("$> ");
		tmp = ft_get_file(0, 0, 0);
		ft_printf("log : str = %s", tmp);
		if (ft_strncmp(tmp, "exit\n", ft_strlen(tmp)) == 0)
			break ;
		free(tmp);
	}
	if (tmp)
		free(tmp);
	return (0);
}
