/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:25:58 by ekeinan           #+#    #+#             */
/*   Updated: 2025/02/23 20:41:18 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

bool	free_str_arr(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	return (1);
}

bool	close_all(t_shell *shell)
{
	bool	err;

	err = 0;
	if (shell->prev_read > -1)
	{
		err = close(shell->prev_read);
		shell->prev_read = -1;
	}
	if (shell->pipe_write > -1)
	{
		err = close(shell->pipe_write) || err;
		shell->pipe_write = -1;
	}
	if (shell->pipe_read > -1)
	{
		err = close(shell->pipe_read) || err;
		shell->pipe_read = -1;
	}
	return (err);
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
