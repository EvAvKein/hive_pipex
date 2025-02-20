/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:28:55 by ekeinan           #+#    #+#             */
/*   Updated: 2025/02/18 14:53:02 by ekeinan          ###   ########.fr       */
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

void	cycle_pipes(t_shell *shell)
{
	int		swap;

	swap = shell->inpipe_read;
	shell->inpipe_read = shell->outpipe_read;
	shell->outpipe_read = swap;
	swap = shell->inpipe_write;
	shell->inpipe_write = shell->outpipe_write;
	shell->outpipe_write = swap;
}

bool	if_either(int first, int second)
{
	return (first || second);
}

bool	close_until_negative(int *fds)
{
	bool	any_failed;

	any_failed = 0;
	while (*fds >= 0)
	{
		any_failed = (close(*fds) < 0) || any_failed;
		fds++;
	}
	return (any_failed);
}

bool	cmd_is_empty_or_dir(char *cmd_str)
{
	int	dir_fd;

	if (!*cmd_str)
	{
		ft_dprintf(STDERR_FILENO, "pipex: : command not found\n");
		return (1);
	}
	dir_fd = open(cmd_str, __O_DIRECTORY);
	if (dir_fd >= 0)
	{
		close(dir_fd);
		return (1);
	}
	return (0);
}
