#ifndef HEREDOC_H
# define HEREDOC_H

# include "../../include/command.h"

// process.c
int		process_infiles(t_command *head_cmd);
void	cleanup_infiles(t_command *head_cmd);

// logic.c
void	replace_first_heredoc_with_file(t_command *cmd, char *filename);

// write_heredocs.c
int		open_temp_infile(char **filename, int index);
int		write_heredocs_to_file(t_command *cmd, int fd);
int		write_heredoc_to_fd(t_infile *infile, int fd);
char	*generate_heredoc_filename(int index);

#endif
