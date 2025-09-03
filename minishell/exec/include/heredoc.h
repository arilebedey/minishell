#ifndef HEREDOC_H
# define HEREDOC_H

# include "../../include/command.h"

int		process_heredocs(t_command *head_cmd);
void	cleanup_heredocs(t_command *head_cmd);

// write.c
int		process_cmd_heredocs(t_command *cmd, int index);

// files.c
int		write_heredoc_to_fd(t_infile *infile, int fd);
char	*generate_heredoc_filename(int index);

#endif
