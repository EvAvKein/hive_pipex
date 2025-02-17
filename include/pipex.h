/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 14:29:55 by ekeinan           #+#    #+#             */
/*   Updated: 2025/02/17 14:09:56 by ekeinan          ###   ########.fr       */
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

typedef struct s_cmd
{
	int		in_fd;
	int		out_fd;
	char	*str;
}			t_cmd;

typedef struct s_shell
{
	int		argc;
	char	**argv;
	char	**envp;
	char	*bin_paths;
	int		inpipe_read;
	int		inpipe_write;
	int		outpipe_read;
	int		outpipe_write;
}			t_shell;

void	process_cmd(t_shell *shell, t_cmd cmd, int *two_remaining_fds);
char	*path_to_binary(t_shell *shell, char *bin);

bool	run_first_cmd(t_shell *shell);
bool	run_last_cmd_and_wait_all(t_shell *shell);

bool	free_str_arr(char **arr);
bool	if_either(int first, int second);
bool	close_until_negative(int *fds);

int		clean(t_shell shell);
int		clean_exit(t_shell shell, int exit_code);

#endif