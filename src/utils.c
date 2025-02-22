/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:28:55 by ekeinan           #+#    #+#             */
/*   Updated: 2025/02/22 23:44:51 by ekeinan          ###   ########.fr       */
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

bool	init_shell(t_shell *shell, int argc, char **argv, char **envp)
{
	char	**env;

	*shell = (t_shell){
		.argc = argc,
		.argv = argv,
		.envp = envp,
		.bin_paths = NULL,
		.waits = 0,
		.prev_read = -1,
		.pipe_read = -1,
		.pipe_write = -1
	};
	env = shell->envp;
	while (env && *env && ft_strncmp(*env, "PATH=", 5))
		env++;
	if (!env || !*env)
		return (!perr("pipex: PATH env not found\n"));
	if (!*(env + 5))
		return (!perr("pipex: PATH env empty\n"));
	shell->bin_paths = (*env + 5);
	if (pipe(&shell->pipe_read))
		return (!pipex_arg_errno("pipe failure"));
	return (1);
}

void	repipe(t_shell *shell)
{
	int err;

	err = 0;
	if  (shell->prev_read > -1)
		err = close(shell->prev_read);
	if  (shell->pipe_write > -1)
		err = close(shell->pipe_write) || err;
	shell->prev_read = shell->pipe_read;
	if (err)
	{
		close(shell->prev_read);
		clean_exit(*shell, pipex_arg_errno("pipe closure"));
	}
	if (pipe(&shell->pipe_read))
		clean_exit(*shell, pipex_arg_errno("pipe creation"));
}