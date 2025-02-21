/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:21:09 by ekeinan           #+#    #+#             */
/*   Updated: 2025/02/21 12:08:55 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

bool	pipex_run_first_cmd(t_shell *shell)
{
	int	infile;

	infile = open(shell->argv[1], O_RDONLY);
	if (infile < 0)
		return (!pipex_arg_errno(shell->argv[1]));
	process_cmd(shell, (t_cmd){.in_fd = infile, .out_fd = shell->inpipe_write,
		.str = shell->argv[2]},
		(int [4]){shell->inpipe_read, shell->outpipe_read, shell->outpipe_write,
			 -1});
	if (close(infile))
		return (!pipex_arg_errno(shell->argv[1]));
	return (1);
}

bool	heredoc_run_first_cmd(t_shell *shell)
{
	char	*line;

	line = NULL;
	while (1)
	{
		if (!set_next_line(STDIN_FILENO, &line))
			return (!pipex_arg_errno(shell->argv[1]));
		if (!line)
			return (!pipex_arg_errno(shell->argv[1]));
		if (!ft_strncmp(line, shell->argv[2], ft_strlen(shell->argv[2]) - 1)
			&& line[ft_strlen(shell->argv[2])] == '\n')
		{
			free(line);
			break ;
		}
		if (write(shell->outpipe_write, line, ft_strlen(line)) < 0)
			return (!pipex_arg_errno(shell->argv[1]));
		free(line);
	}
	process_cmd(shell, (t_cmd){.in_fd = shell->outpipe_read,
		.out_fd = shell->inpipe_write, .str = shell->argv[3]},
		(int [3]){shell->outpipe_write, shell->inpipe_read, -1});
	return (1);
}

bool	run_last_cmd_and_wait_all(t_shell *shell, bool heredoc)
{
	int	outfile;
	int	cmd_count;

	cmd_count = shell->argc - 3 - heredoc;
	outfile = open(shell->argv[shell->argc - 1], O_WRONLY | O_CREAT | O_TRUNC,
			0644);
	if (outfile < 0)
		return (!pipex_arg_errno(shell->argv[shell->argc - 1]));
	process_cmd(shell, (t_cmd){.in_fd = shell->inpipe_read, .out_fd = outfile,
		.str = shell->argv[cmd_count + 1 + heredoc]},
		(int [4]){shell->outpipe_write, shell->outpipe_read,
		shell->inpipe_write, -1});
	if (close_until_negative((int [5]){shell->inpipe_read, shell->inpipe_write,
			shell->outpipe_read, shell->outpipe_write, -1}))
		return (!pipex_arg_errno("pipe closing"));
	while (cmd_count--)
	{
		ft_dprintf(2, "Waiting cmd %i...\n", cmd_count + 1);
		wait(NULL);
		ft_dprintf(2, "Waited %i!\n", cmd_count + 1);
	}
	if (close(outfile))
		return (!pipex_arg_errno(shell->argv[shell->argc - 1]));
	return (1);
}
