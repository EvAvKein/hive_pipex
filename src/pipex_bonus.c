/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:21:09 by ekeinan           #+#    #+#             */
/*   Updated: 2025/02/22 23:49:22 by ekeinan          ###   ########.fr       */
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
	if (close_until_negative((int[3]){shell->pipe_write, shell->prev_read, -1}))
		clean_exit(*shell, pipex_arg_errno(shell->argv[1]));	
}

void	heredoc_run_first_cmd(t_shell *shell)
{
	char	*line;

	line = NULL;
	while (1)
	{
		if (!set_next_line(STDIN_FILENO, &line))
			clean_exit(*shell, pipex_arg_errno(shell->argv[1]));
		if (!line)
			clean_exit(*shell, pipex_arg_errno(shell->argv[1]));
		if (!ft_strncmp(line, shell->argv[2], ft_strlen(shell->argv[2]) - 1)
			&& line[ft_strlen(shell->argv[2])] == '\n')
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
	// if (close_until_negative((int [3]){shell->pipe_write, shell->prev_read,
	// 		-1}))
	// 	clean_exit(*shell, pipex_arg_errno("pipe closing 1"));
	shell->prev_read = shell->pipe_read;
	shell->pipe_write = open(shell->argv[shell->argc - 1], open_oflags,
			0644);
	if (shell->pipe_write < 0)
		clean_exit(*shell, pipex_arg_errno(shell->argv[shell->argc - 1]));
	shell->pipe_read = -1;
	process_cmd(shell, shell->argv[shell->argc - 2]);
	if (close_until_negative((int [4]){shell->prev_read, shell->pipe_write,
			-1}))
		clean_exit(*shell, pipex_arg_errno("pipe closing 2"));
	pipes_bnegative(shell);
	while (shell->waits--)
		wait(NULL);
}
