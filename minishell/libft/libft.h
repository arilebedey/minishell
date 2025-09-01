/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agense <agense@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:02:13 by agense            #+#    #+#             */
/*   Updated: 2025/09/01 15:24:10 by agense           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

// Checks for an alphabetic character.
int			ft_isalpha(int c);
// Checks if c is a space or a backslash character (\n, \t, \v, \f, \r).
int 		ft_isspace(int c);
// Checks for a digit (0 through 9).
int			ft_isdigit(int c);
// Checks for an alphanumeric character
int			ft_isalnum(int c);
// Checks whether c is a 7-bit unsigned char value that fits into the ASCII
// character set
int			ft_isascii(int c);
// Checks for any printable character including space
int			ft_isprint(int c);
// Calculates the length of the string pointed to by s,
// excluding the terminating null byte ('\0').
size_t		ft_strlen(const char *s);
// Calculates the length of the string pointed to by s until '\0' or delim.
size_t	ft_strlen2(const char *s, const char delim);
// Fills the first n bytes of the memory area pointed to by s with the constant
// byte c.
void		*ft_memset(void *s, int c, size_t n);
// Erases the data in the n bytes of the memory starting at the location
// pointed to by s, by writing zeros (bytes containing '\0') to that area.
void		ft_bzero(void *s, size_t n);
// Copies n bytes from memory area src to memory area dest.
// The memory areas must not overlap.
// Use memmove if the memory areas do overlap.
void		*ft_memcpy(void *dest, const void *src, size_t n);
// Copies n bytes from memory area src to memory area dest.
// The memory areas may overlap: copying takes place as though
// the bytes in src are first copied into a temporary array that
// does not overlap src or dest, and the bytes are then copied
// from the temporary array to dest.
void		*ft_memmove(void *dest, const void *src, size_t n);
// Copy a NUL terminated string into a sized buffer.
// Returns src length.
size_t		ft_strlcpy(char *dest, const char *src, size_t dest_size);
// Appends the NUL-terminated string src to the end of dest.
// Append at most size - strlen(dest) - 1 bytes.
// NUL-terminating the result (except if size = 0
// or size of dest >= dest_size given)
// Returns the length of the string it tried to create.
size_t		ft_strlcat(char *dest, const char *src, size_t dest_size);
// If c is a lowercase letter, returns its uppercase equivalent.
// Otherwise, returns c.
int			ft_toupper(int c);
// If c is a uppercase letter, returns its lowercase equivalent.
// Otherwise, returns c.
int			ft_tolower(int c);
// Returns a pointer to the first occurence of the character c in the string s.
char		*ft_strchr(const char *s, int c);
// Returns a pointer to the first occurence of a character of delim in the string s.
// Returns NULL if none have been found.
char		*ft_strchr2(const char *s, const char *delim);
// Returns a pointer to the last occurence of the character c in the string s
char		*ft_strrchr(const char *s, int c);
// Compares the two strings s1 ans s2 and returns an integer indicating the
// result of the comparison as follows:
// 0 if s1 ans s2 are equal
// a negative value if s1 is less than s2
// a positive value if s1 is greater than s2
int			ft_strncmp(const char *s1, const char *s2, size_t n);
// Scans the initial n bytes of the memory area pointed to by s.
// Returns a pointer to the first occurence of c if c is in the n bytes,
// otherwise returns NULL.
// Both c and the bytes of the memory area pointed to by s are interpreted
// as unsigned char.
void		*ft_memchr(const void *s, int c, size_t n);
// Returns an integer less than, or greater than zero of the first
// byte of s1 which is respectively, to be less than, or be
// greater than the first different byte from s2.
// Each bytes are interpreted as unsigned char.
// Compare until n bytes, if n is NULL, return NULL
int			ft_memcmp(const void *s1, const void *s2, size_t n);
// Returns the first occurence of s2 in s1, where not more than n characters are
// searched. Characters that appear after '\0' are not searched.
// If s2 is an empty string, returns s1; if s2 occurs nowhere in s1,
// returns NULL; otherwise a pointer to the first character of the first
// occurence of s2 is returned.
char		*ft_strnstr(const char *s1, const char *s2, size_t n);
// Allocates memory for an array of n_elem elements of size bytes each and
// returns a pointer to the allocated memory.
// The memory is set to zero.
// If n_elem or size is 0, returns a unique pointer value that can later
// be successfully passed to free().
// Error if n_elem * size results to integer overflow
void		*ft_calloc(size_t n_elem, size_t size);
// Returns a pointer to a new string which is a duplicate of the string s.
// Memory for the new string is obtained with malloc, and can be freed
// with free().
// Returns NULL if insufficient memory was available.
char		*ft_strdup(const char *s);
// Returns a pointer to a new string which is a duplicate of s until n bytes.
// Returns NULL if insufficient memory was available.
char		*ft_strndup(const char *s, size_t n);
// Converts the initial portion of the string pointed to by s to int.
int			ft_atoi(const char *s);
// Returns a new string from the string s, starting at start index with a size
// of len.
char		*ft_substr(char const *s, unsigned int start, size_t len);
// Returns a new string which is the concatenation of s1 and s2.
char		*ft_strjoin(char const *s1, char const *s2);
// Returns a new string which is a copy of s1 without chars in the string set
// at start and end of s1.
char		*ft_strtrim(char const *s1, char const *set);
// Converts n to string.
char		*ft_itoa(int n);
// Converts the initial portion of the string pointed to by s to long long.
long long	ft_atoll(const char *s);
// Separate the string s with the character c and returns all these
// separated string in an array of string.
char		**ft_split(char const *s, char c);
// Returns a new string resulting from the application of f for all char in s.
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
// Apply f for each character in string s
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
// Write c in the file descriptor fd
void		ft_putchar_fd(char c, int fd);
// Write the string s in the file descriptor fd
void		ft_putstr_fd(char *s, int fd);
// Write the string s in the file descriptor fd followed by a newline.
void		ft_putendl_fd(char *s, int fd);
// Write the number n in the file descriptor fd.
void		ft_putnbr_fd(int n, int fd);
// Create a new list with content as first member
t_list		*ft_lstnew(void *content);
// Add a new element at the start of the list with lst as a pointer to
// the first element of the list.
void		ft_lstadd_front(t_list **lst, t_list *new);
// Add new element at the end of the list
// lst : pointer to the first element of the list
void		ft_lstadd_back(t_list **lst, t_list *new);
// Returns the number of elements of lthe list
int			ft_lstsize(t_list *lst);
// Returns the last element of the list
t_list		*ft_lstlast(t_list *lst);
// Delete content of the element with the del function then free the element.
// Does not touch next elements.
void		ft_lstdelone(t_list *lst, void (*del)(void *));
// Delete content of all elements with the del function then free the elements.
void		ft_lstclear(t_list **lst, void (*del)(void *));
// Iterate in the list and apply the f function on the content of each element.
void		ft_lstiter(t_list *lst, void (*f)(void *));
// Iterate on the list and apply the f function on the content of each element.
// Create a new list resulting from the successive applications of f.
// The del function is here to delete the content of an element if necessary.
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
// Prints the given string on stantard output
int			ft_printf(const char *format, ...);
// Returns a string containing the next line in the given fd
// Returns NULL if an error occured
char		*get_next_line(int fd);
// Reallocate memory at the size given
// Returns 0 if the allocation failed
// Returns 1 on success
int			ft_realloc(char **str_p, int malloc_size);
#endif