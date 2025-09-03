#include "../../../include/env.h"
#include "../../include/expander.h"
#include "../../../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

static char	*take_env_key(char **ref_cursor);

int	handle_env_variables(char **out_value, t_env *head_env)
{
	char		*cursor;
	char		*dup_before_key;
	char		*dup_after_key;
	char		*key;
	const char	*env_value;
	char		*tmp_value;

	cursor = *out_value;
	while (*cursor)
	{
		if (*cursor == '$')
		{
			dup_before_key = ft_strndup(*out_value, cursor - *out_value);
			if (!dup_before_key)
				return (0);
			key = take_env_key(&cursor);
			if (!key)
				return (free(dup_before_key), 0);
			dup_after_key = ft_strdup(cursor);
			if (!dup_after_key)
				return (perror("strdup dupafterkey"), free(dup_before_key), 0);
			env_value = get_env_value(head_env, key);
			free(key);
			if (!env_value)
			{
				free(*out_value);
				*out_value = ft_strjoin(dup_before_key, dup_after_key);
				if (!*out_value)
					return (perror("strjoin0"), free(dup_before_key), free(dup_after_key), 0);
				cursor = *out_value + ft_strlen(dup_before_key);
				free(dup_before_key);
				free(dup_after_key);
				continue ;
			}
			tmp_value = ft_strjoin(dup_before_key, env_value);
			if (!tmp_value)
				return (perror("strjoin1"), free(dup_before_key), free(key), free(dup_after_key), 0);
			free(*out_value);
			*out_value = ft_strjoin(tmp_value, dup_after_key);
			free(tmp_value);
			if (!*out_value)
				return (perror("strjoin2"), free(dup_before_key), free(key), free(dup_after_key), 0);
			cursor = *out_value + ft_strlen(dup_before_key) + ft_strlen(env_value);
			free(dup_before_key);
			free(dup_after_key);
			if (!*out_value)
				return (perror("strjoin2"), 0);
		}
		else
			cursor++;
	}
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
	end = ft_strchr2(*ref_cursor, " $");
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
