#include "../../include/command.h"
#include "../../include/error.h"
#include "../include/token.h"
#include <stdio.h>
#include <stdlib.h>

// Returns a new arg initialized with each fields set to NULL.
// If failed, returns NULL pointer.
static t_args		*init_arg(void);
// Returns a new infile initialized with each fields set to NULL/0.
// If failed, returns NULL pointer.
static t_infile		*init_infile(void);
// Returns a new outfile initialized with each fields set to NULL/0.
// If failed, returns NULL pointer.
static t_outfile	*init_outfile(void);

t_command	*init_cmd(void)
{
	t_command	*new_cmd;

	new_cmd = malloc(sizeof(t_command));
	if (!new_cmd)
	{
		perror("command malloc");
		return (NULL);
	}
	new_cmd->head_arg = NULL;
	new_cmd->head_infile = NULL;
	new_cmd->head_outfile = NULL;
	new_cmd->next = NULL;
	return (new_cmd);
}

int	add_infile(t_infile **ref_head_infile, char *value, int heredoc_mode)
{
	t_infile	*curr_infile;

	if (!*ref_head_infile)
	{
		*ref_head_infile = init_infile();
		if (!*ref_head_infile)
			return (print_error("error: head_file malloc"), 0);
		(*ref_head_infile)->value = value;
		(*ref_head_infile)->heredoc_mode = heredoc_mode;
		return (1);
	}
	curr_infile = *ref_head_infile;
	while (curr_infile->next)
		curr_infile = curr_infile->next;
	curr_infile->next = init_infile();
	if (!curr_infile->next)
		return (print_error("error: curr_arg malloc"), 0);
	curr_infile->next->value = value;
	curr_infile->next->heredoc_mode = heredoc_mode;
	return (1);
}

int	add_outfile(t_outfile **ref_head_outfile, char *value, int append_mode)
{
	t_outfile	*curr_outfile;

	if (!*ref_head_outfile)
	{
		*ref_head_outfile = init_outfile();
		if (!*ref_head_outfile)
			return (print_error("error: head_file malloc"), 0);
		(*ref_head_outfile)->value = value;
		(*ref_head_outfile)->append_mode = append_mode;
		return (1);
	}
	curr_outfile = *ref_head_outfile;
	while (curr_outfile->next)
		curr_outfile = curr_outfile->next;
	curr_outfile->next = init_outfile();
	if (!curr_outfile->next)
		return (print_error("error: curr_arg malloc"), 0);
	curr_outfile->next->value = value;
	curr_outfile->next->append_mode = append_mode;
	return (1);
}

int	add_arg(t_args **ref_head_arg, char *value)
{
	t_args	*curr_arg;

	if (!*ref_head_arg)
	{
		*ref_head_arg = init_arg();
		if (!*ref_head_arg)
			return (print_error("error: head_arg malloc"), 0);
		(*ref_head_arg)->value = value;
		return (1);
	}
	curr_arg = *ref_head_arg;
	while (curr_arg->next)
		curr_arg = curr_arg->next;
	curr_arg->next = init_arg();
	if (!curr_arg->next)
		return (print_error("error: curr_arg malloc"), 0);
	curr_arg->next->value = value;
	return (1);
}

static t_infile	*init_infile(void)
{
	t_infile	*new_infile;

	new_infile = malloc(sizeof(t_infile));
	if (!new_infile)
		return (NULL);
	new_infile->value = NULL;
	new_infile->heredoc_mode = 0;
	new_infile->next = NULL;
	return (new_infile);
}

static t_outfile	*init_outfile(void)
{
	t_outfile	*new_outfile;

	new_outfile = malloc(sizeof(t_outfile));
	if (!new_outfile)
		return (NULL);
	new_outfile->value = NULL;
	new_outfile->append_mode = 0;
	new_outfile->next = NULL;
	return (new_outfile);
}

static t_args	*init_arg(void)
{
	t_args	*new_arg;

	new_arg = malloc(sizeof(t_args));
	if (!new_arg)
		return (NULL);
	new_arg->value = NULL;
	new_arg->next = NULL;
	return (new_arg);
}
