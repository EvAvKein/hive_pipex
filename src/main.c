/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 14:29:52 by ekeinan           #+#    #+#             */
/*   Updated: 2025/02/05 22:33:48 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell shell;
	t_cmd	cmd;

	shell = (t_shell){
		.argc = argc,
		.argv = argv,
		.envp = envp,
		.bin_paths = NULL
	};

	init_bin_paths(&shell);
	
	// if (!shell.bin_paths)
	// Will it insta-error? Test reassigning $PATH?
	
	cmd = str_to_cmd(argv[1]);
	if (!cmd.mergedc)
	{
		ft_printf("No command\n");
		return (1);
	}
	ft_printf("%s\n", path_to_binary(&shell, argv[1]));
	run_cmd(&shell, cmd, 0);
	ft_printf("Process survived :D\n");
	// bool	here_doc_mode;
	// here_doc_mode = (argc == 5 && ft_strncmp(argv[0], "here_doc", 9));
	// if (!here_doc_mode && argc != 4)
	// 	return (1);
	// if (here_doc_mode)
	// 	return (here_doc(&argv[1]));
	// else
	//  return (run_command());
	//return (pipex(argc, argv, envp));
}