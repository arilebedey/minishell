/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agense <agense@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:08:07 by agense            #+#    #+#             */
/*   Updated: 2025/09/11 13:08:08 by agense           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILD_H
# define BUILD_H

# include "../../include/command.h"

// build_handler.c

// Handle a single arg.
// If failed, prints error msg and returns 0.
int		handle_arg(t_token *curr_tk, t_command *curr_cmd);
// Handle infile and heredoc.
// If failed, prints error msg and returns 0.
int		handle_infile(t_token *curr_tk, t_infile **ref_head_infile);
// Handle outfile.
// If failed, prints error msg and returns 0.
int		handle_outfile(t_token *curr_tk, t_outfile **ref_head_outfile);
// Handle pipe. Creates new command.
// If failed, prints error msg and returns 0.
int		handle_pipe(t_token *curr_tk, t_command **ref_curr_cmd);

// build_error.c

// Should be called if parse error before return
// Returns 0
int		parse_exit(const char c, t_command *head_cmd);
// Prints parse error msg in stderr.
void	print_parse_error(const char c);

#endif