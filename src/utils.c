/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:28:55 by ekeinan           #+#    #+#             */
/*   Updated: 2025/02/23 18:00:11 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_shell(t_shell *shell, int argc, char **argv, char **envp)
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
	if (pipe(&shell->pipe_read))
		exit(pipex_arg_errno("pipe failure"));
	env = shell->envp;
	while (env && *env && ft_strncmp(*env, "PATH=", 5))
		env++;
	if (!env || !*env || !*(env + 5))
		return ;
	shell->bin_paths = (*env + 5);
}

bool	cmd_is_empty_or_dir(char *cmd_str)
{
	int	dir_fd;

	if (!*cmd_str)
	{
		ft_dprintf(STDERR_FILENO, "pipex: : command not found\n");
		return (1);
	}
	dir_fd = open(cmd_str, O_DIRECTORY);
	if (dir_fd >= 0)
	{
		if (close(dir_fd))
			pipex_arg_errno(cmd_str);
		ft_dprintf(2, "pipex: %s: %s\n", cmd_str, strerror(21));
		return (1);
	}
	return (0);
}

void	repipe(t_shell *shell)
{
	int	err;

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
	shell->prev_read = shell->pipe_read;
	shell->pipe_read = -1;
	if (err)
	{
		close(shell->prev_read);
		clean_exit(*shell, pipex_arg_errno("pipe closure"));
	}
	if (pipe(&shell->pipe_read))
		clean_exit(*shell, pipex_arg_errno("pipe creation"));
}

void	unpipe(t_shell *shell)
{
	int	err;

	err = 0;
	if (shell->prev_read > -1)
		err = close(shell->prev_read);
	if (shell->pipe_write > -1)
		err = close(shell->pipe_write) || err;
	shell->prev_read = shell->pipe_read;
	shell->pipe_read = -1;
	shell->pipe_write = -1;
	if (err)
	{
		if (shell->prev_read > -1)
		{
			close(shell->prev_read);
			shell->prev_read = -1;
		}
		clean_exit(*shell, pipex_arg_errno("fd closure"));
	}
}

int	pipex_arg_errno(char *arg)
{
	ft_dprintf(STDERR_FILENO, "pipex: %s: %s\n", arg, strerror(errno));
	return (1);
}
