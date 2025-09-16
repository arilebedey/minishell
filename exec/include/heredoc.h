/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebedev <alebedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 12:55:45 by alebedev          #+#    #+#             */
/*   Updated: 2025/09/15 14:29:12 by alebedev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# include "../../include/command.h"

// process.c
int		process_infiles(t_command *head_cmd);
void	cleanup_infiles(t_command *head_cmd);

// write_heredocs.c
int		write_heredoc_to_fd(t_infile *infile, int fd, char *tmpname,
			t_command *head_cmd);

// write_utils.c
int		open_temp_infile(char **filename, int index);
int		replace_heredoc_with_file(t_infile *in, char *filename);
void	heredoc_sigint(int signum);

#endif
