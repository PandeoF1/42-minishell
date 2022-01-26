/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaffroy <asaffroy@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 14:55:26 by asaffroy          #+#    #+#             */
/*   Updated: 2022/01/26 15:43:29 by asaffroy         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_cd(int fd, char **path)
{
	if (ft_strlen(*path) != 2)
		ft_perror("wrong number of args arguments");
	//ft_printf("%s\n", path[1]);
	chdir(path[1]);
	ft_pwd(fd);
	exit(0);
}
