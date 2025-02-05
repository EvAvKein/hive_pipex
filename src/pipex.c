/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 14:44:22 by ekeinan           #+#    #+#             */
/*   Updated: 2025/02/03 20:40:37y ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	pipex(int argc, char **argv, char **envp)
{
	(void)	argc;
	(void)	argv;
	(void)	envp;
	// int		i;
	// int		infile;
	// t_cmd	cmd;
	// // int		outfile;
	// // pid_t	pid;
	
	// infile = open(argv[0], O_RDONLY);
	// if (infile < -1)
	// {
	// 	write(1, "No such file or directory\n", 27);
	// 	return (1);
	// }
	// // MINISHELL: Would need to check second arg
	// i = 2;
	// while (i < argc)
	// {
	// 	cmd = args_to_cmd(argc - i, &argv[i]);
	// 	if (!cmd.argc)
	// 	{
	// 		close(infile);
	// 		exit(0);
	// 	}
	// 	run_cmd(cmd.argc, cmd.argv, envp, 0); // REPLACE WITH DUPED FD?
		


	// }

	exit(0);
}
