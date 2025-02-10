/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 14:44:22 by ekeinan           #+#    #+#             */
/*   Updated: 2025/02/10 21:40:01 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	cycle_pipes(t_shell *shell)
{
	int		swap;

	swap = shell->inpipe_read;
	shell->inpipe_read = shell->outpipe_read;
	shell->outpipe_read = swap;
	swap = shell->inpipe_write;
	shell->inpipe_write = shell->outpipe_write;
	shell->outpipe_write = swap;
}

int	pipex(t_shell shell, int argc, char **argv)
{
	int	infile;
	int	i;
	int outfile;	

	i = 2;
	infile = open(argv[1], O_RDONLY);
	if (infile < 0)
		return (!perr("Infile open error\n"));
	process_cmd(&shell, infile, argv[i++], shell.outpipe_write);
	close(infile);
	while (i < argc - 2)
	{
		cycle_pipes(&shell);
		process_cmd(&shell, shell.inpipe_read, argv[i++], shell.outpipe_write);
	}
	outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile < 0)
		return (!perr("Outfile open error\n"));
	process_cmd(&shell, shell.outpipe_read, argv[i++], outfile);
	i -= 2;
	while (i--)
		wait(NULL);
	close(outfile);
	close(shell.inpipe_read);
	close(shell.inpipe_write);
	close(shell.outpipe_read);
	close(shell.outpipe_write);
	exit(0);
	return (-1u);
}
