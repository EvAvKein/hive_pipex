/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 14:29:55 by ekeinan           #+#    #+#             */
/*   Updated: 2025/02/10 17:28:04 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdbool.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>
# include "../libft_full/libft_full.h"
# include "perrs.h"

typedef	struct	s_cmd
{
	int			mergedc;
	int			argc;
	char		**argv;
}					t_cmd;

typedef	struct	s_shell
{
	int		argc;
	char	**argv;
	char	**envp;
	char	*bin_paths;
	int		inpipe_read;
	int		inpipe_write;
	int		outpipe_read;
	int		outpipe_write;
}					t_shell;

int		pipex(t_shell shell, int argc, char **args);
int		here_doc(t_shell shell, int argc, char **argv);

void	process_cmd(t_shell *shell, int input_fd, char *str, int output_fd);
char	*path_to_binary(t_shell *shell, char *bin);

bool	is_operator(char *arg);
bool	free_str_arr(char **arr);

#endif