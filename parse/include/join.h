/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agense <agense@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 14:36:02 by agense            #+#    #+#             */
/*   Updated: 2025/10/03 14:36:38 by agense           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOIN_H
# define JOIN_H

# include "expander.h"

// Join both dups to form the new out value.
// If failed, prints error msg and returns 0.
int	join_both_dups(t_handle_env *ref_hev, char **out_value);

// Join both dups and the env value to form the new out value.
// If failed, prints error msg and returns 0.
int	join_to_out_value(t_handle_env *ref_hev, char **out_value);

#endif