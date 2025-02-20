/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:49:56 by ekeinan           #+#    #+#             */
/*   Updated: 2025/02/17 11:20:46 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "pipex.h"

bool	pipex_run_first_cmd(t_shell *shell);
bool	heredoc_run_first_cmd(t_shell *shell);
bool	run_last_cmd_and_wait_all(t_shell *shell, bool heredoc);
void	cycle_pipes(t_shell *shell);

#endif