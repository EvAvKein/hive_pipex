/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:49:56 by ekeinan           #+#    #+#             */
/*   Updated: 2025/02/22 11:12:56 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "pipex.h"

void	pipex_run_first_cmd(t_shell *shell);
void	heredoc_run_first_cmd(t_shell *shell);
void	run_last_cmd_and_wait_all(t_shell *shell);
void	swap_pipes(t_shell *shell);

#endif