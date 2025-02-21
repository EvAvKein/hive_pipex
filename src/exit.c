/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:25:58 by ekeinan           #+#    #+#             */
/*   Updated: 2025/02/21 12:18:25 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int close_both_unless_pipe(t_shell *shell, int fd1, int fd2)
{
	t_shell	sh;
	int		close_err;

	close_err = 0;
	sh = *shell;
	if (fd1 != sh.inpipe_read
			&& fd1 != sh.inpipe_write	
			&& fd1 != sh.outpipe_read
			&& fd1 != sh.outpipe_write)
		close_err = close(fd1);
	if (fd2 != sh.inpipe_read
			&& fd2 != sh.inpipe_write	
			&& fd2 != sh.outpipe_read
			&& fd2 != sh.outpipe_write)
	{
		if (close_err)
		{
			close(fd2);
			return (close_err);
		}
		return (close(fd2));
	}
	return (close_err);
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
