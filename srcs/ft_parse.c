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
	split = ft_split(str, ' ');
	if (ft_check_command(split[0], env) == 1)
	{
		ft_printf("gg %s\n", split[0]);
		//process = ft_create_process(split[0], split, env);
		//ft_free_split(split);
		//return (process);
	}
	while (split[x])
		free(split[x++]);
	free(split);
	return (NULL);
}
