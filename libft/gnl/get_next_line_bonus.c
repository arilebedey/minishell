/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agense <agense@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 11:34:11 by agense            #+#    #+#             */
/*   Updated: 2025/09/02 21:11:34 by alebedev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

// Copy a NUL terminated string into a sized buffer.
// Not the og function btw
static int	ft_strlcpy(char *dest, const char *src, size_t dest_size)
{
	size_t	i;
	size_t	src_len;

	if (!dest)
		return (0);
	src_len = ft_strlen_edit(src, 0);
	if (!dest_size)
		return (1);
	i = 0;
	while (i < dest_size - 1 && i < src_len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (1);
}

// Concatenate buf in stash (pointed by p_stash)
static void	conc_buf(char **p_stash, char *buf)
{
	char	*stock_stash;
	size_t	stash_len;

	stash_len = ft_strlen_edit(*p_stash, 0);
	if (*p_stash)
	{
		stock_stash = ft_calloc_edit(stash_len + 1, sizeof(char));
		if (!stock_stash)
			return ;
		ft_strlcpy(stock_stash, *p_stash, stash_len + 1);
	}
	else
	{
		stock_stash = ft_calloc_edit(1, 1);
		if (!stock_stash)
			return ;
	}
	free(*p_stash);
	*p_stash = ft_strjoin_edit(stock_stash, buf);
	free(stock_stash);
}

// Returns the first line in stash
// A line is a string terminated by '\n' followed by '\0'
static char	*get_line_in_stash(char **p_stash, size_t stash_len)
{
	char	*line;
	char	*buf_scrap;
	size_t	stash_len_after_nl;
	size_t	stash_len_until_first_nl;
	size_t	buf_scrap_len;

	if (!(*p_stash))
		return (NULL);
	stash_len_until_first_nl = ft_strlen_edit(*p_stash, '\n');
	stash_len_after_nl = ft_strlen_edit(ft_strchr_edit(*p_stash, '\n',
				stash_len) + 1, 0);
	line = ft_calloc_edit(stash_len_until_first_nl + 2, sizeof(char));
	if (!ft_strlcpy(line, *p_stash, stash_len_until_first_nl + 2))
		return (free(line), line = NULL, NULL);
	buf_scrap = ft_calloc_edit(stash_len_after_nl + 1, sizeof(char));
	if (!ft_strlcpy(buf_scrap, ft_strchr_edit(*p_stash, '\n', stash_len) + 1,
			stash_len_after_nl + 1))
		return (free(line), line = NULL, NULL);
	free(*p_stash);
	buf_scrap_len = ft_strlen_edit(buf_scrap, 0);
	*p_stash = ft_calloc_edit(buf_scrap_len + 1, sizeof(char));
	ft_strlcpy(*p_stash, buf_scrap, buf_scrap_len + 1);
	free(buf_scrap);
	return (line);
}

static char	*get_stash(char *cp_stash)
{
	if (!(cp_stash[0]))
	{
		free(cp_stash);
		return (NULL);
	}
	return (cp_stash);
}

char	*get_next_line(int fd)
{
	static char	*st[1024];
	char		*cp_st;
	char		*buf;
	int			byte_read;

	while (!ft_strchr_edit(st[fd], '\n', ft_strlen_edit(st[fd], 0)))
	{
		buf = ft_calloc_edit(BUFFER_SIZE + 1, sizeof(char));
		if (!buf)
			return (NULL);
		byte_read = read(fd, buf, BUFFER_SIZE);
		if (byte_read == -1)
			return (free(buf), free(st[fd]), st[fd] = NULL, NULL);
		if (byte_read == 0)
		{
			cp_st = ft_calloc_edit(ft_strlen_edit(st[fd], 0) + 1, sizeof(char));
			if (!cp_st)
				return (NULL);
			ft_strlcpy(cp_st, st[fd], ft_strlen_edit(st[fd], 0) + 1);
			return (free(st[fd]), st[fd] = NULL, free(buf), get_stash(cp_st));
		}
		conc_buf(&st[fd], buf);
		free(buf);
	}
	return (get_line_in_stash(&st[fd], ft_strlen_edit(st[fd], 0)));
}
