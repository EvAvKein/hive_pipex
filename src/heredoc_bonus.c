/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:21:09 by ekeinan           #+#    #+#             */
/*   Updated: 2025/02/17 14:42:14 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	heredoc_handle_line(t_shell *shell, char *line, char **limiter_found)
{
	*limiter_found = ft_strnstr(line, shell->argv[2], ft_strlen(line));
	if (limiter_found)
		**limiter_found = '\0';
	write(shell->outpipe_write, line, ft_strlen(line));
	free(line);
}

bool	heredoc_run_first_cmd(t_shell *shell)
{
	int		infile;
	char	*line;
	char	*limiter_found;

	line = NULL;
	limiter_found = NULL;
	infile = open(shell->argv[2], O_RDONLY);
	if (infile < 0)
		return (!pipex_arg_errno(shell->argv[1]));
	while (1)
	{
		if (!set_next_line(infile, &line))
			return (!pipex_arg_errno(shell->argv[1]));
		if (line)
			heredoc_handle_line(shell, line, &limiter_found);
		if (limiter_found || !line)
			break ;
	}
	if (close(infile))
		return (!pipex_arg_errno(shell->argv[1]));
	process_cmd(shell, (t_cmd){.in_fd = shell->outpipe_read,
		.out_fd = shell->inpipe_write, .str = shell->argv[3]},
		(int [3]){shell->outpipe_write, shell->inpipe_read, -1});
	return (1);
}

bool	heredoc_run_last_cmd_and_wait_all(t_shell *shell, bool heredoc)
{
	int	outfile;
	int	cmd_count;

	cmd_count = shell->argc - 3 - heredoc;
	outfile = open(shell->argv[cmd_count + 2], O_WRONLY | O_CREAT | O_TRUNC,
			0644);
	if (outfile < 0)
		return (!pipex_arg_errno(shell->argv[cmd_count + 2]));
	process_cmd(shell, (t_cmd){.in_fd = shell->outpipe_read, .out_fd = outfile,
		.str = shell->argv[cmd_count + 1]},
		(int [4]){shell->outpipe_write, shell->inpipe_read,
		shell->inpipe_write, -1});
	if (close_until_negative((int [5]){shell->inpipe_read, shell->inpipe_write,
			shell->outpipe_read, shell->outpipe_write, -1}))
		return (!pipex_arg_errno("pipe closing"));
	while (cmd_count--)
		wait(NULL);
	if (close(outfile))
		return (!pipex_arg_errno(shell->argv[shell->argc - 1]));
	return (1);
}
