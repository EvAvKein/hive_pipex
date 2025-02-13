/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:21:09 by ekeinan           #+#    #+#             */
/*   Updated: 2025/02/13 14:23:47 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

bool	run_first_cmd_heredoc(t_shell *shell)
{
	int	infile;

	infile = open(shell->argv[2], O_RDONLY);
	if (infile < 0)
		return (!pipex_arg_errno(shell->argv[1]));
	process_cmd(shell, (t_cmd){.in_fd = infile, .out_fd = shell->outpipe_write,
		.str = shell->argv[2]}, shell->outpipe_read);
	if (close(infile))
		return (!pipex_arg_errno(shell->argv[1]));
	return (1);
}
