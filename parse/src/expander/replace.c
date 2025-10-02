/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agense <agense@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:11:06 by agense            #+#    #+#             */
/*   Updated: 2025/10/02 13:01:02 by agense           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/sig/sig.h"
#include "../../../include/env.h"
#include "../../include/expander.h"
#include "../../../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

static int	init_hev(t_handle_env *ref_hev, char **out_value, t_env *head_env);
static int	join_both_dups(t_handle_env *ref_hev, char **out_value);
static int	join_to_out_value(t_handle_env *ref_hev, char **out_value);
static char	*take_env_key(char **ref_cursor);

int	handle_env_variables(char **out_value, t_env *head_env)
{
	t_handle_env	hev;

	hev.env_v = NULL;
	hev.curs = *out_value;
	while (*hev.curs)
	{
		if (*hev.curs == '$')
		{
			if (!init_hev(&hev, out_value, head_env))
				return (0);
			if (!hev.env_v)
			{
				if (!join_both_dups(&hev, out_value))
					return (0);
				continue ;
			}
			if (!join_to_out_value(&hev, out_value))
				return (0);
		}
		else
			hev.curs++;
	}
	return (1);
}

// Init hev.
// If failed, prints error msg and returns 0.
static int	init_hev(t_handle_env *ref_hev, char **out_value, t_env *head_env)
{
	ref_hev->env_v = NULL;
	if (*(ref_hev->curs + 1) == '?')
	{
		ref_hev->env_v = ft_itoa(g_exit_status);
		if (!ref_hev->env_v)
			return (perror("itoa fail"), 0);
	}
	ref_hev->bk = ft_strndup(*out_value, ref_hev->curs - *out_value);
	if (!ref_hev->bk)
		return (0);
	ref_hev->key = take_env_key(&ref_hev->curs);
	if (!ref_hev->key)
		return (free(ref_hev->bk), 0);
	ref_hev->ak = ft_strdup(ref_hev->curs);
	if (!ref_hev->ak)
		return (perror("strdup dupafterkey"), free(ref_hev->bk), 0);
	if (!ref_hev->env_v)
		ref_hev->env_v = get_env_value(head_env, ref_hev->key);
	free(ref_hev->key);
	return (1);
}

// Join both dups to form the new out value.
// If failed, prints error msg and returns 0.
static int	join_both_dups(t_handle_env *ref_hev, char **out_value)
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

// Join both dups and the env value to form the new out value.
// If failed, prints error msg and returns 0.
static int	join_to_out_value(t_handle_env *ref_hev, char **out_value)
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
