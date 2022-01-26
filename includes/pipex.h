/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaffroy <asaffroy@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 16:35:48 by asaffroy          #+#    #+#             */
/*   Updated: 2022/01/26 15:15:52 by asaffroy         ###   ########lyon.fr   */
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
	int				**fd1;
	int				*file;
	int				nb_cmd;
	int				ind;
	int				*i;
	int				*dec;
	char			*type_char;
	char			charset[4];
	int				*type_nb;
	int				*check;
	pid_t			*pid1;
	char			**tab_paths;
	char			***tab_args;\
	char			**tab_env;
	struct s_inout	*inout;
}	t_data;

#endif