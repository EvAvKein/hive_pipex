/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 17:16:39 by ekeinan           #+#    #+#             */
/*   Updated: 2024/11/29 12:55:40 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_uppercase_hex(unsigned long long n, long long *print_count)
{
	char	chr;

	if (n > 15)
	{
		print_uppercase_hex(n / 16, print_count);
		if (*print_count < 0)
			return ;
		n %= 16;
	}
	if (n < 10)
		chr = (n % 10) + '0';
	else
		chr = (n % 10) + 'A';
	increase_print_count(write(1, &chr, 1), print_count);
}

void	print_lowercase_hex(unsigned long long n, long long *print_count)
{
	char	chr;

	if (n > 15)
	{
		print_lowercase_hex(n / 16, print_count);
		if (*print_count < 0)
			return ;
		n %= 16;
	}
	if (n < 10)
		chr = (n % 10) + '0';
	else
		chr = (n % 10) + 'a';
	increase_print_count(write(1, &chr, 1), print_count);
}
