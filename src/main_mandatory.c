/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_mandatory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 14:44:22 by ekeinan           #+#    #+#             */
/*   Updated: 2025/02/21 19:45:54 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static bool	init_shell(t_shell *shell, int argc, char **argv, char **envp)
{
	char	**env;

	*shell = (t_shell){
		.argc = argc,
		.argv = argv,
		.envp = envp,
		.bin_paths = NULL,
		.waits = 0,
		.inpipe_read = -1,
		.inpipe_write = -1,
		.outpipe_read = -1,
		.outpipe_write = -1
	};
	env = shell->envp;
	while (env && *env && ft_strncmp(*env, "PATH=", 5))
		env++;
	if (!env || !*env)
		return (!perr("pipex: PATH env not found\n"));
	if (!*(env + 5))
		return (!perr("pipex: PATH env empty\n"));
	shell->bin_paths = (*env + 5);
	if (pipe(&shell->outpipe_read))
		return (!pipex_arg_errno("pipe failure"));
	return (1);
}

static void	pipex(t_shell shell, char **argv)
{
	int	infile;
	int	outfile;

	infile = open(argv[1], O_RDONLY);
	if (infile < 0)
		pipex_arg_errno(argv[1]);
	else
	{
		process_cmd(&shell, (t_cmd){.in_fd = infile, .str = argv[2],
		.out_fd = shell.outpipe_write}, (int [2]){shell.outpipe_read, -1});
		if (close(infile))
			clean_exit(shell, pipex_arg_errno(argv[1]));
	}
	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile < 0)
		clean_exit(shell, pipex_arg_errno(argv[4]));
	process_cmd(&shell, (t_cmd){.in_fd = shell.outpipe_read, .out_fd = outfile,
		.str = argv[3]}, (int [2]){shell.outpipe_write, -1});
	if (close_until_negative((int [3]){shell.outpipe_read, shell.outpipe_write,
			-1}))
		clean_exit(shell, pipex_arg_errno("pipe closing"));
	while (shell.waits--)
		wait(NULL);
	if (close(outfile))
		clean_exit(shell, pipex_arg_errno(argv[4]));
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
