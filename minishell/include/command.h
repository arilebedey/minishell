#ifndef COMMAND_H
# define COMMAND_H

typedef struct s_command
{
	char				**args;
	char				*input_file;
	char				*output_file;
	int					append_mode;
	int					heredoc_mode;
	char				*heredoc_eof;
	struct s_command	*next;
}		t_command;

// free_cmd.c

// free the command element given and all next elements.
void	free_cmd_list(t_command *head_cmd);

#endif