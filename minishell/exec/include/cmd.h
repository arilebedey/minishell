/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebedev <alebedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 12:55:40 by alebedev          #+#    #+#             */
/*   Updated: 2025/09/11 13:06:55 by alebedev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

# include "../../include/command.h"
# include "../../include/env.h"

// get_cmd.c
char	*resolve_cmd(char *cmd, t_env *head_env);

// exec_pipeline.c
int		exec_pipeline(t_command *cmd, t_env *head_env);

#endif
