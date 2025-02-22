/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:25:58 by ekeinan           #+#    #+#             */
/*   Updated: 2025/02/22 21:40:05 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	close_both_unless_pipe(t_shell *shell, int fd1, int fd2)
{
	t_shell	sh;
	int		close_err;

	close_err = 0;
	sh = *shell;
	if (fd1 != sh.prev_read
		&& fd1 != sh.pipe_read
		&& fd1 != sh.pipe_write)
		close_err = close(fd1);
	if (fd2 != sh.prev_read
		&& fd2 != sh.pipe_read
		&& fd2 != sh.pipe_write)
		return (close(fd2) || close_err);
	return (close_err);
}

void	pipes_bnegative(t_shell *shell)
{
	shell->prev_read = -1;
	shell->pipe_read = -1;
	shell->pipe_write = -1;
}

static void	clean(t_shell shell)
{
	if (shell.prev_read > -1 && close(shell.prev_read))
		pipex_arg_errno("exit cleanup");
	if (shell.pipe_write > -1 && close(shell.pipe_write))
		pipex_arg_errno("exit cleanup");
	if (shell.pipe_read > -1 && close(shell.pipe_read))
		pipex_arg_errno("exit cleanup");
}

int	clean_exit(t_shell shell, int exit_code)
{
	clean(shell);
	exit(exit_code);
	return (1);
}
