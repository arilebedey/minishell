/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agense <agense@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:11:06 by agense            #+#    #+#             */
/*   Updated: 2025/10/03 14:58:52 by agense           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/sig/sig.h"
#include "../../../include/env.h"
#include "../../include/expander.h"
#include "../../include/join.h"
#include "../../../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

static int	init_hev(t_handle_env *ref_hev, char **out_value, t_env *head_env);
static int	init_for_exit_status(t_handle_env *ref_hev);
static char	*take_env_key(char **ref_cursor);
static int	replace(t_handle_env *ref_hev, char **out_value, t_env *head_env);

int	handle_env_variables(char **out_value, t_env *head_env)
{
	t_handle_env	hev;

	hev.curs = *out_value;
	while (*hev.curs)
	{
		hev.env_v = NULL;
		hev.key = NULL;
		if (*hev.curs == '$')
		{
			if (!replace(&hev, out_value, head_env))
				return (0);
		}
		else
			hev.curs++;
		if (hev.is_exit_status)
			free(hev.env_v);
	}
	return (1);
}

// Replace the key by the appropriate value.
// Return 2 if no value have been found.
// If failed, prints error msg and returns 0.
static int	replace(t_handle_env *ref_hev, char **out_value, t_env *head_env)
{
	if (!init_hev(ref_hev, out_value, head_env))
	{
		if (ref_hev->is_exit_status)
			free(ref_hev->env_v);
		return (0);
	}
	if (!ref_hev->env_v)
	{
		if (!join_both_dups(ref_hev, out_value))
			return (0);
		return (1);
	}
	if (!join_to_out_value(ref_hev, out_value))
	{
		if (ref_hev->is_exit_status)
			free(ref_hev->env_v);
		return (0);
	}
	return (1);
}

// Init hev.
// If failed, prints error msg and returns 0.
static int	init_hev(t_handle_env *ref_hev, char **out_value, t_env *head_env)
{
	ref_hev->is_exit_status = 0;
	if (*(ref_hev->curs + 1) == '?')
	{
		if (!init_for_exit_status(ref_hev))
			return (0);
	}
	ref_hev->bk = ft_strndup(*out_value, ref_hev->curs - *out_value);
	if (!ref_hev->bk)
		return (0);
	if (!ref_hev->key)
		ref_hev->key = take_env_key(&ref_hev->curs);
	else
		ref_hev->curs += 2;
	if (!ref_hev->key)
		return (free(ref_hev->bk), 0);
	ref_hev->ak = ft_strdup(ref_hev->curs);
	if (!ref_hev->ak)
		return (perror("strdup dupafterkey"), free(ref_hev->bk), 0);
	if (!ref_hev->is_exit_status)
		ref_hev->env_v = get_env_value(head_env, ref_hev->key);
	return (free(ref_hev->key), 1);
}

// Init in case of ?
// If failed, prints error msg and returns 0.
static int	init_for_exit_status(t_handle_env *ref_hev)
{
	ref_hev->env_v = ft_itoa(g_exit_status);
	if (!ref_hev->env_v)
		return (perror("itoa fail"), 0);
	ref_hev->key = ft_strdup("?");
	if (!ref_hev->key)
		return (perror("key strdup fail"), free(ref_hev->env_v), 0);
	ref_hev->is_exit_status = 1;
	return (1);
}

// Returns the key starting at cursor pointer.
// The cursor is set at one byte after the last key byte.
// If failed, prints error msg and returns a NULL pointer.
static char	*take_env_key(char **ref_cursor)
{
	char		*end;
	char		*key;
	ptrdiff_t	len_key;

	*ref_cursor += 1;
	end = ft_strchr2(*ref_cursor, " $\'");
	if (!end)
	{
		key = ft_strdup(*ref_cursor);
		if (!key)
			return (perror("strdup_env_key"), NULL);
		*ref_cursor += ft_strlen(key);
		return (key);
	}
	len_key = end - *ref_cursor;
	key = ft_strndup(*ref_cursor, len_key);
	*ref_cursor += len_key;
	if (!key)
		return (perror("strndup_env_key"), NULL);
	return (key);
}
