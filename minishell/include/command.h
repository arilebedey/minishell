#ifndef COMMAND_H
# define COMMAND_H

typedef struct s_args
{
	char			*value;
	struct s_args	*next;
}		t_args;

typedef struct s_infile
{
	char			*value;
	int				heredoc_mode;
	struct s_infile	*next;
}		t_infile;

typedef struct s_outfile
{
	char				*value;
	int					append_mode;
	struct s_outfile	*next;
}		t_outfile;

typedef struct s_command
{
	t_args				*head_arg;
	t_infile			*head_infile;
	t_outfile			*head_outfile;
	struct s_command	*next;
}		t_command;

// command.c

// Returns a new command with all values init to 0/NULL.
// If failed, returns NULL pointer.
t_command	*init_cmd(void);
// Add a new arg to the args list.
// If failed, prints error msg and returns 0.
int			add_arg(t_args **ref_head_arg, char *value);
// Add a new infile to the infile list.
// If failed, prints error msg and returns 0.
int			add_infile(t_infile **ref_head_infile, char *value, int heredoc_mode);
// Add a new outfile to the infile list.
// If failed, prints error msg and returns 0.
int			add_outfile(t_outfile **ref_head_outfile, char *value, int append_mode);

// free_cmd.c

// Free the command linked list.
void	free_cmd_list(t_command **ref_head_cmd);

#endif
