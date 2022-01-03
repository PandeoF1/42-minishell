/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putmemory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 16:31:13 by tnard             #+#    #+#             */
/*   Updated: 2021/11/12 13:24:51 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static int	ft_check_base(char *base, char c)
{
	int	n;
	int	i;

	i = 0;
	n = 0;
	while (base[n])
		if (base[n++] == c)
			i++;
	if (i >= 2)
		return (0);
	return (1);
}

static unsigned long long	ft_strprint(unsigned long long n,
	char *base, unsigned int size)
{
	int	t;

	t = 0;
	if (n > size - 1)
	{
		t += ft_strprint(n / size, base, size);
		n %= size;
	}
	ft_putchar(base[n]);
	t++;
	return (t);
}

int	ft_putmemory(unsigned long long *nbr, char *base)
{
	int	n;
	int	t;

	t = 0;
	n = -1;
	while (base[++n])
		if ((base[n] == '-' || base[n] == '+' || !ft_check_base(base, base[n])))
			return (t);
	if (n < 2)
		return (t);
	t += ft_putstr("0x");
	if ((long)nbr < 0)
		nbr[0] = -nbr[0];
	t += ft_strprint(nbr[0], base, n);
	return (t);
}
