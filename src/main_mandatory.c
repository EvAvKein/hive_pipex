/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_mandatory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 14:44:22 by ekeinan           #+#    #+#             */
/*   Updated: 2025/02/22 23:31:09 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	pipex(t_shell shell, char **argv)
{
	shell.prev_read = open(argv[1], O_RDONLY);
	if (shell.prev_read < 0)
		pipex_arg_errno(argv[1]);
	else
		process_cmd(&shell, argv[2]);
	if (close_until_negative((int[3]){shell.pipe_write, shell.prev_read, -1}))
		clean_exit(shell, pipex_arg_errno(argv[1]));
	shell.prev_read = shell.pipe_read;
	shell.pipe_write = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (shell.pipe_write < 0)
		clean_exit(shell, pipex_arg_errno(argv[4]));
	shell.pipe_read = -1;
	process_cmd(&shell, argv[3]);
	if (close_until_negative((int [3]){shell.prev_read, shell.pipe_write, -1}))
		clean_exit(shell, pipex_arg_errno("final pipe closures"));
	pipes_bnegative(&shell);
	while (shell.waits--)
		wait(NULL);
	clean_exit(shell, 0);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	if (!init_shell(&shell, argc, argv, envp))
		return (1);
	if (argc != 5)
	{
		ft_dprintf(STDERR_FILENO, "Pipex arguments:\n\
<infile> <cmd1> <cmd2> <outfile> = `< infile cmd1 | cmd2 > outfile`\n");
		clean_exit(shell, 1);
	}
	pipex(shell, argv);
	return (0);
}
