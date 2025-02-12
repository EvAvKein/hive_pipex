/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_mandatory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 14:44:22 by ekeinan           #+#    #+#             */
/*   Updated: 2025/02/12 18:07:04 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static bool init_shell(t_shell *shell)
{
	char	**env;

	env = shell->envp;
	while (ft_strncmp(*env, "PATH=", 5))
		env++;
	if (!*env)
		return (!perr("PLACEHOLDER ERR: PATH env not found\n"));
	if (!*(env + 5))
		return (!perr("PLACEHOLDER ERR: PATH env empty\n"));
	shell->bin_paths = (*env + 5);
	if (pipe(&shell->outpipe_read))
		return (!perr("Pipe failure\n"));
	return (1);
}

static int	pipex(t_shell shell, char **argv)
{
	int	infile;
	int outfile;

	infile = open(argv[1], O_RDONLY);
	if (infile < 0)
		return (ft_dprintf(STDERR_FILENO, "pipex: %s", argv[1])
					&& perrno("", errno));
	process_cmd(&shell, (t_cmd){.in_fd = infile, .out_fd = shell.outpipe_write,
		.str = argv[2]}, shell.outpipe_read);
	close(infile);
	//if (access(argv[argc - 1], F_OK));
	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile < 0)
		return (ft_dprintf(STDERR_FILENO, "pipex: %s", argv[4])
					&& perrno("", errno));
	process_cmd(&shell, (t_cmd){.in_fd = shell.outpipe_read, .out_fd = outfile,
		.str = argv[3]}, shell.outpipe_write);
	close(shell.outpipe_read);
	close(shell.outpipe_write);
	wait(NULL);
	wait(NULL);
	close(outfile);
	clean_exit(shell, 0);
	return (-1u);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell shell;

	shell = (t_shell){
		.argc = argc,
		.argv = argv,
		.envp = envp,
		.bin_paths = NULL,
		.inpipe_read = -1,
		.inpipe_write = -1,
		.outpipe_read = -1,
		.outpipe_write = -1
	};
	if (!init_shell(&shell))
		return (1);
	if (argc != 5)
		ft_dprintf(STDERR_FILENO, "Pipex arguments:\n\
		<infile> <cmd1> <cmd2> <outfile> == < infile cmd1 | cmd2 > outfile");
	else
		pipex(shell, argv);
	return (1);
}
