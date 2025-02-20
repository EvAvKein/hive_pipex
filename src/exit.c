/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:25:58 by ekeinan           #+#    #+#             */
/*   Updated: 2025/02/12 11:54:56 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int close_unless_pipe(t_shell *shell, int fd)
{
	t_shell	sh;

	sh = *shell;
	if (fd != sh.inpipe_read
			&& fd != sh.inpipe_write	
			&& fd != sh.outpipe_read
			&& fd != sh.outpipe_write)
		return (close(fd));
	return (0);
}

int	clean(t_shell shell)
{
	if (shell.inpipe_read > -1)
		close(shell.inpipe_read);
	if (shell.inpipe_write > -1)
		close(shell.inpipe_write);
	if (shell.outpipe_read > -1)
		close(shell.outpipe_read);
	if (shell.outpipe_write > -1)
		close(shell.outpipe_write);
	return (1);
}

int	clean_exit(t_shell shell, int exit_code)
{
	clean(shell);
	exit(exit_code);
	return (1);
}
