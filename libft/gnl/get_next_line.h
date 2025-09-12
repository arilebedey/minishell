/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agense <agense@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 11:35:35 by agense            #+#    #+#             */
/*   Updated: 2025/06/30 15:05:23 by agense           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stddef.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

// Returns a pointer to the first occurence of the character c in the string s.
char	*ft_strchr_edit(const char *s, int c, size_t stash_len);
// Returns a new string which is the concatenation of s1 and s2.
char	*ft_strjoin_edit(char const *s1, char const *s2);
// Allocates memory for an array of n_elem elements of size bytes each and
// returns a pointer to the allocated memory.
// The memory is set to zero.
// If n_elem or size is 0, returns a unique pointer value that can later
// be successfully passed to free().
// Error if n_elem * size results to integer overflow
void	*ft_calloc_edit(size_t n_elem, size_t size);
// like og ft_strlen but stop at first char c (0 for og ft_strlen)
size_t	ft_strlen_edit(const char *s, char c);
char	*get_next_line(int fd);
#endif
