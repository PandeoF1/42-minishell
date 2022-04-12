/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 16:35:48 by asaffroy          #+#    #+#             */
/*   Updated: 2022/04/12 12:22:59 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../ft_printf/ft_printf.h"
# include "../libft/libft.h"
# include "minishell.h"
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>

typedef struct s_data
{
	int				*fd;
	int				*file;
	int				nb_cmd;
	int				ind;
	char			charset[4];
	int				exit;
	pid_t			*pid1;
	char			**tab_paths;
	char			***tab_args;
	char			**tab_env;
	int				j;
	int				status;
	char			*line;
	struct s_inout	*inout;
}	t_data;

#endif