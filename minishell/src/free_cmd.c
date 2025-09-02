#include "../include/command.h"
#include <malloc.h>

static void	free_cmd_element(t_command *current_cmd);
static void	free_cmd_args(t_args *curr_arg);
static void	free_cmd_infiles(t_infile *curr_infile);
static void	free_cmd_outfiles(t_outfile *curr_outfile);

void	free_cmd_list(t_command *head_cmd)
{
	if (!head_cmd)
		return ;
	if (head_cmd->next)
		free_cmd_list(head_cmd->next);
	free_cmd_element(head_cmd);
	head_cmd = NULL;
}

// Free all values of the command given.
// Does not free the command itself.
// Does not touch next elements.
static void	free_cmd_element(t_command *current_cmd)
{
	if (!current_cmd)
		return ;
	free_cmd_args(current_cmd->head_arg);
	free_cmd_infiles(current_cmd->head_infile);
	free_cmd_outfiles(current_cmd->head_outfile);
	free(current_cmd);
}

// Free all infiles starting at curr_file
static void	free_cmd_infiles(t_infile *curr_infile)
{
	if (!curr_infile)
		return ;
	if (curr_infile->next)
		free_cmd_infiles(curr_infile->next);
	free(curr_infile->value);
	free(curr_infile);
}

// Free all outfiles starting at curr_outfile
static void	free_cmd_outfiles(t_outfile *curr_outfile)
{
	if (!curr_outfile)
		return ;
	if (curr_outfile->next)
		free_cmd_outfiles(curr_outfile->next);
	free(curr_outfile->value);
	free(curr_outfile);

}
// Free all args starting at curr_arg
static void	free_cmd_args(t_args *curr_arg)
{
	if (!curr_arg)
		return ;
	if (curr_arg->next)
		free_cmd_args(curr_arg->next);
	free(curr_arg->value);
	free(curr_arg);
}
