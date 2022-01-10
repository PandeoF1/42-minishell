/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaffroy <asaffroy@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 16:35:48 by asaffroy          #+#    #+#             */
/*   Updated: 2022/01/10 09:20:10 by asaffroy         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../ft_printf/ft_printf.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>

typedef struct s_data
{
	int		*fd;
	int		file1;
	int		file2;
	int		nb_cmd;
	int		ind;
	char	type_char;
	int		type_nb;
	int		*check;
	pid_t	*pid1;
	char	**tab_paths;
	char	***tab_args;
}	t_data;

void	ft_perror(char *str);
char	**ft_split_exec(char const *s, t_data *data, int a);

#endif