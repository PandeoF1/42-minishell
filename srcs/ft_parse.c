/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 12:03:03 by tnard             #+#    #+#             */
/*   Updated: 2022/01/03 12:03:03 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


/*
* ft_space(str)
* desc : compare number of space with strlen
* params : string
*/

int	ft_space(char *str)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			x++;
		i++;
	}
	if (x == i - 1)
		return (0);
	return (1);
}

/*
* ft_parse_command(str)
* desc : parse the command and return the struct
* params : str to parse
*/

t_process	*ft_parse_command(char *str, char **env)
{
	t_process	*process;
	char		**split;
	int			x;

	x = 0;
	if (ft_strlen(str) == 1 || ft_space(str) == 0)
		return (NULL);
	str[ft_strlen(str) - 1] = '\0';
	if (ft_check_quote(str))
	{
		if (ft_check_inout(str) && ft_check_inout_n(str))
		{
		}
		else
			ft_printf("minishell: syntax error near unexpected token `newline'\n");
	}
	else
		ft_printf("minishell: syntax error with open quotes\n");
	return (NULL);
}
