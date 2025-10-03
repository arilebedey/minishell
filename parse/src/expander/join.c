/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agense <agense@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 14:59:37 by agense            #+#    #+#             */
/*   Updated: 2025/10/03 14:59:38 by agense           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../libft/libft.h"
#include "../../../include/env.h"
#include "../../include/expander.h"
#include <stdio.h>
#include <stdlib.h>

int	join_both_dups(t_handle_env *ref_hev, char **out_value)
{
	free(*out_value);
	*out_value = ft_strjoin(ref_hev->bk, ref_hev->ak);
	if (!*out_value)
		return (perror("strjoin0"), free(ref_hev->bk), free(ref_hev->ak), 0);
	ref_hev->curs = *out_value + ft_strlen(ref_hev->bk);
	free(ref_hev->bk);
	free(ref_hev->ak);
	return (1);
}

int	join_to_out_value(t_handle_env *ref_hev, char **out_value)
{
	ref_hev->tmp_v = ft_strjoin(ref_hev->bk, ref_hev->env_v);
	if (!ref_hev->tmp_v)
		return (perror("strjoin1"), free(ref_hev->bk), free(ref_hev->ak), 0);
	free(*out_value);
	*out_value = ft_strjoin(ref_hev->tmp_v, ref_hev->ak);
	free(ref_hev->tmp_v);
	if (!*out_value)
		return (perror("strjoin2"), free(ref_hev->bk), free(ref_hev->ak), 0);
	ref_hev->curs = *out_value + ft_strlen(ref_hev->bk) \
		+ ft_strlen(ref_hev->env_v);
	free(ref_hev->bk);
	ref_hev->bk = NULL;
	free(ref_hev->ak);
	if (!*out_value)
		return (perror("strjoin2"), 0);
	return (1);
}
