/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 10:43:13 by tnard             #+#    #+#             */
/*   Updated: 2021/11/12 13:24:53 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int				ft_printf(const char *str, ...);
int				ft_putnbr_base(unsigned int nbr, char *base);
int				ft_putnbr(int n);
int				ft_putstr(char *s);
int				ft_putchar(char c);
int				ft_putmemory(unsigned long long *t, char *table);
unsigned int	ft_putnbr_u(unsigned int n);

#endif