/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 14:20:00 by tnard             #+#    #+#             */
/*   Updated: 2022/01/25 14:20:00 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_pwd(int fd)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	write(fd, pwd, ft_strlen(pwd));
	write(fd, "\n", 1);
	free(pwd);
	exit(0);
}
