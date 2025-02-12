/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 14:44:22 by ekeinan           #+#    #+#             */
/*   Updated: 2025/02/12 16:32:54 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	here_doc(t_shell shell, int argc, char **argv)
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
	//if (access(argv[argc - 1], F_OK));
	outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile < 0)
		return (!perr("Outfile open error\n"));
	process_cmd(&shell, shell.outpipe_read, argv[i++], outfile);
	i -= 2;
	while (i--)
		wait(NULL);
	close(outfile);
	clean_exit(shell, 0);
}

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

void	pipex(t_shell shell, int argc, char **argv)
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
	//if (access(argv[argc - 1], F_OK));
	outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile < 0)
		return (!perr("Outfile open error\n"));
	process_cmd(&shell, shell.outpipe_read, argv[i++], outfile);
	i -= 2;
	while (i--)
		wait(NULL);
	close(outfile);
	clean_exit(shell, 0);
}

bool init_shell(t_shell *shell)
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
	if (pipe(&shell->inpipe_read) || pipe(&shell->outpipe_read))
		return (!perr("Pipe failure\n"));
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell shell;
	int status;

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
	if (argc >= 6 && !strncmp(argv[1], "here_doc", 9))
		here_doc(shell, argc, argv);
	else if (argc >= 5)
		pipex(shell, argc, argv);
	else
		ft_dprintf(STDERR_FILENO, "Pipex arguments:\n\
		<infile> <cmd1> <cmd2> <outfile> == < infile cmd1 | cmd2 > outfile\n\
		OR\n\
		here_doc <infile> <limiter> <cmd1> <cmd2> <appendfile> == \
		cmd1 << limiter | cmd2 >> appendfile\n\
		\n\
		(Two commands is the minimum, feel free to run more!)");
	return (WEXITSTATUS(status));
}