/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:21:09 by ekeinan           #+#    #+#             */
/*   Updated: 2025/02/23 20:57:25 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex_run_first_cmd(t_shell *shell)
{
	shell->prev_read = open(shell->argv[1], O_RDONLY);
	if (shell->prev_read < 0)
		pipex_arg_errno(shell->argv[1]);
	else
		process_cmd(shell, shell->argv[2]);
}

void	heredoc_run_first_cmd(t_shell *shell)
{
	char	*line;
	int		limiter_len;

	line = NULL;
	limiter_len = ft_strlen(shell->argv[2]);
	while (1)
	{
		if (!set_next_line(STDIN_FILENO, &line))
			clean_exit(*shell, pipex_arg_errno(shell->argv[1]));
		if (!line)
			clean_exit(*shell, pipex_arg_errno(shell->argv[1]));
		if (!ft_strncmp(line, shell->argv[2], limiter_len - 1)
			&& line[limiter_len] == '\n')
		{
			free(line);
			break ;
		}
		if (write(shell->pipe_write, line, ft_strlen(line)) < 0)
			clean_exit(*shell, pipex_arg_errno(shell->argv[1]));
		free(line);
	}
	repipe(shell);
	process_cmd(shell, shell->argv[3]);
}

void	run_last_cmd_and_wait_all(t_shell *shell, int open_oflags)
{
	shell->pipe_write = open(shell->argv[shell->argc - 1], open_oflags,
			0644);
	if (shell->pipe_write < 0)
		pipex_arg_errno(shell->argv[shell->argc - 1]);
	else
	{
		process_cmd(shell, shell->argv[shell->argc - 2]);
		if (close_all(shell))
			pipex_arg_errno("final pipe closure");
	}
	while (shell->waits--)
		wait(NULL);
}
