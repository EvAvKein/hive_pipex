/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 14:44:22 by ekeinan           #+#    #+#             */
/*   Updated: 2025/02/22 23:17:50 by ekeinan          ###   ########.fr       */
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
		process_cmd(&shell, argv[i++]);
		repipe(&shell);
	}
	run_last_cmd_and_wait_all(&shell, O_WRONLY | O_CREAT | O_APPEND);
	return (clean_exit(shell, 0));
}

static int	pipex(t_shell shell, int argc, char **argv)
{
	int	i;

	pipex_run_first_cmd(&shell);
	i = 3;
	while (i < argc - 2)
	{
		repipe(&shell);
		process_cmd(&shell, argv[i++]);
	}
	run_last_cmd_and_wait_all(&shell, O_WRONLY | O_CREAT | O_TRUNC);
	return (clean_exit(shell, 0));
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
