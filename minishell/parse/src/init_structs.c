/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agense <agense@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:15:16 by agense            #+#    #+#             */
/*   Updated: 2025/09/11 13:15:17 by agense           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/command.h"
#include "../../include/error.h"
#include <stdlib.h>

t_infile	*init_infile(void)
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

t_outfile	*init_outfile(void)
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

t_args	*init_arg(void)
{
	t_args	*new_arg;

	new_arg = malloc(sizeof(t_args));
	if (!new_arg)
		return (NULL);
	new_arg->value = NULL;
	new_arg->next = NULL;
	return (new_arg);
}
