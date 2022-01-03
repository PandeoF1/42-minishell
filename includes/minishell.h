/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 10:47:55 by tnard             #+#    #+#             */
/*   Updated: 2022/01/03 10:47:55 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include "../libft/libft.h"
# include "../ft_printf/ft_printf.h"

typedef struct s_process
{
	struct s_process	*next;
	char				*command;
	char				*path;
	char				*args;
	char				*output;
	char				*type;
}			t_process;

char		*ft_get_input(int fd, int size, int len);
t_process	*ft_parse_command(char *str, char **env);
int			ft_check_command(char *cmd, char **env);

#endif