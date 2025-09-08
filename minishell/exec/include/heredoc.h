#ifndef HEREDOC_H
# define HEREDOC_H

# include "../../include/command.h"

// process.c
int		process_infiles(t_command *head_cmd);
void	cleanup_infiles(t_command *head_cmd);

// write_heredocs.c
int		write_heredocs_to_file(t_command *cmd, int fd, char *filename);
int		write_heredoc_to_fd(t_infile *infile, int fd, char *tmpname,
			t_command *head_cmd);

// write_utils.c
int		open_temp_infile(char **filename, int index);
int		replace_heredoc_with_file(t_infile *in, char *filename);

#endif
