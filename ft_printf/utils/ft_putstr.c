/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 12:08:11 by tnard             #+#    #+#             */
/*   Updated: 2021/11/05 16:28:42 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_putstr(char *s)
{
	int	n;

	n = 0;
	if (s == NULL)
		n += ft_putstr("(null)");
	else
		while (s[n])
			ft_putchar(s[n++]);
	return (n);
}
