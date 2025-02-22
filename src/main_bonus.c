/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 14:44:22 by ekeinan           #+#    #+#             */
/*   Updated: 2025/02/22 11:12:56 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	here_doc(t_shell shell, int argc, char **argv)
{
	int	i;

	heredoc_run_first_cmd(&shell);
	i = 4;
	while (i < argc - 2)
	{
		process_cmd(&shell, (t_cmd){.in_fd = shell.inpipe_read,
			.out_fd = shell.outpipe_write, .str = argv[i++]},
			(int [3]){shell.inpipe_write, shell.outpipe_read, -1});
		swap_pipes(&shell);
	}
	run_last_cmd_and_wait_all(&shell);
	return (clean_exit(shell, 0));
}

static int	pipex(t_shell shell, int argc, char **argv)
{
	int	i;

	pipex_run_first_cmd(&shell);
	i = 3;
	while (i < argc - 2)
	{
		process_cmd(&shell, (t_cmd){.in_fd = shell.inpipe_read,
			.out_fd = shell.outpipe_write, .str = argv[i++]},
			(int [3]){shell.inpipe_write, shell.outpipe_read, -1});
		swap_pipes(&shell);
	}
	run_last_cmd_and_wait_all(&shell);
	return (clean_exit(shell, 0));
}

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
	if (pipe(&shell->inpipe_read) || pipe(&shell->outpipe_read))
		return (!pipex_arg_errno("pipe failure"));
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	if (!init_shell(&shell, argc, argv, envp))
		return (1);
	if (argc >= 6 && !ft_strncmp(argv[1], "here_doc", 9))
		here_doc(shell, argc, argv);
	else if (argc >= 5)
		pipex(shell, argc, argv);
	else
	{
		ft_dprintf(STDERR_FILENO, "Pipex arguments:\n\
<infile> <cmd1> <cmd2> <outfile> == < infile cmd1 | cmd2 > outfile\n\
OR\nhere_doc <limiter> <cmd1> <cmd2> <appendfile> == \
cmd1 << limiter | cmd2 >> appendfile\n\n\
(Two commands is the minimum, feel free to run more!)\n");
		clean_exit(shell, 1);
	}
	return (1);
}
