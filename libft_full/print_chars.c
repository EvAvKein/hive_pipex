/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_chars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:09:25 by ekeinan           #+#    #+#             */
/*   Updated: 2024/11/29 12:55:32 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_char(char c, long long *print_count)
{
	increase_print_count(write(1, &c, 1), print_count);
}

void	print_str(char *s, long long *print_count)
{
	if (!s)
	{
		increase_print_count(write(1, "(null)", 6), print_count);
		return ;
	}
	increase_print_count(write(1, s, ft_strlen(s)), print_count);
}
