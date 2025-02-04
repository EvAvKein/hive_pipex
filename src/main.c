/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 14:29:52 by ekeinan           #+#    #+#             */
/*   Updated: 2025/02/04 13:20:49 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell shell;
	(void) argc;

	// shell.bin_paths = ;
	ft_printf(path_to_binary(envp, argv[1]));
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