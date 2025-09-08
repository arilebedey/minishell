#ifndef HEREDOC_H
# define HEREDOC_H

# include "../../include/command.h"

typedef struct s_heredoc_ctx
{
	t_infile			*infile;
	t_command			*head_cmd;
	char				*tmpname;
}						t_heredoc_ctx;

extern t_heredoc_ctx	*g_heredoc_ctx;

// process.c
int						process_infiles(t_command *head_cmd);
void					cleanup_infiles(t_command *head_cmd);

// process_heredocs.c
void					replace_first_heredoc_with_file(t_command *cmd,
							char *filename);
int						open_temp_infile(char **filename, int index);

// write_heredocs.c
int						write_heredocs_to_file(t_command *cmd, int fd,
							char *filename);
int						write_heredoc_to_fd(t_infile *infile, int fd,
							char *tmpname, t_command *head_cmd);
char					*generate_heredoc_filename(int index);

#endif
