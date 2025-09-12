/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agense <agense@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:07:21 by agense            #+#    #+#             */
/*   Updated: 2025/09/11 13:07:22 by agense           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIG_H
# define SIG_H

# include <signal.h>

extern volatile sig_atomic_t	g_exit_status;

// interactive_sig.c

// Initialize signals for interactive mode.
// If failed, prints error msg and returns 0.
int	init_interactive_sigaction(void);

// process_sig.c

// Initialize signals for parent process on fork.
// If failed, prints error msg and returns 0.
int	init_parent_sigaction(void);
// Initialize signals for child process on fork.
// If failed, prints error msg and returns 0.
int	init_child_sigaction(void);

#endif
