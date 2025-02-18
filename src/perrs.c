/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perrs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 17:37:51 by ekeinan           #+#    #+#             */
/*   Updated: 2025/02/18 10:37:34 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	perr_titled(char *text)
{
	write(STDERR_FILENO, "Error\n", 6);
	perr(text);
	return (1);
}

int	perr(char *text)
{
	write(STDERR_FILENO, text, ft_strlen(text));
	return (1);
}

int	pipex_arg_errno(char *arg)
{
	ft_dprintf(STDERR_FILENO, "pipex: %s: %s\n", arg, strerror(errno));
	return (1);
}
