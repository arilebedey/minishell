#ifndef LEXER_H
# define LEXER_H

#include "token.h"

// lexer_special.c

// Add a new token in token list which will depends on the special character.
// If failed, returns 0.
int	handle_special_character(const char **ref_line, t_token **ref_head_tk);

// lexer_word.c

// Search the current word in line and put it as value to a new T_WORD token
// which is then added to the token list.
// If failed, returns 0.
int	handle_word(const char **ref_line, t_token **ref_head_tk, \
	const char *delim);

#endif