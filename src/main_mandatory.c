/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_mandatory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 14:44:22 by ekeinan           #+#    #+#             */
/*   Updated: 2025/02/13 14:27:44 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static bool init_shell(t_shell *shell, int argc, char **argv, char **envp)
{
	char	**env;

	*shell = (t_shell){
		.argc = argc,
		.argv = argv,
		.envp = envp,
		.bin_paths = NULL,
		.inpipe_read = -1,
		.inpipe_write = -1,
		.outpipe_read = -1,
		.outpipe_write = -1
	};
	env = shell->envp;
	while (ft_strncmp(*env, "PATH=", 5))
		env++;
	if (!*env)
		return (!perr("pipex: PATH env not found\n"));
	if (!*(env + 5))
		return (!perr("pipex: PATH env empty\n"));
	shell->bin_paths = (*env + 5);
	if (if_either(pipe(&shell->inpipe_read), pipe(&shell->outpipe_read)))
		return (!pipex_arg_errno("pipe failure"));
	return (1);
}

static int	pipex(t_shell shell, char **argv)
{
	int	infile;
	int outfile;

	infile = open(argv[1], O_RDONLY);
	if (infile < 0)
		return (pipex_arg_errno(argv[1]));
	process_cmd(&shell, (t_cmd){.in_fd = infile, .out_fd = shell.outpipe_write,
		.str = argv[2]}, shell.outpipe_read);
	if (close(infile))
		return (pipex_arg_errno(argv[1]));
	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile < 0)
		return (pipex_arg_errno(argv[4]));
	process_cmd(&shell, (t_cmd){.in_fd = shell.outpipe_read, .out_fd = outfile,
		.str = argv[3]}, shell.outpipe_write);
	if (if_either(close(shell.outpipe_read), close(shell.outpipe_write)))
		return (pipex_arg_errno("pipe closing"));
	wait(NULL);
	wait(NULL);
	if (close(outfile))
		return (pipex_arg_errno(argv[4]));
	clean_exit(shell, 0);
	return (-1u+1);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell shell;

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
