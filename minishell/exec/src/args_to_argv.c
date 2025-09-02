#include "../../include/command.h"
#include "../../libft/libft.h"
#include <stdlib.h>

char	**args_to_argv(t_args *head_arg)
{
	int		count;
	t_args	*curr;
	char	**argv;
	int		i;

	count = 0;
	curr = head_arg;
	while (curr)
	{
		count++;
		curr = curr->next;
	}
	argv = malloc(sizeof(char *) * (count + 1));
	if (!argv)
		return (NULL);
	i = 0;
	curr = head_arg;
	while (curr)
	{
		argv[i] = ft_strdup(curr->value);
		if (!argv[i])
			return (NULL);
		i++;
		curr = curr->next;
	}
	argv[i] = NULL;
	return (argv);
}

void	free_argv(char **argv)
{
	int	i;

	if (!argv)
		return ;
	i = 0;
	while (argv[i])
		free(argv[i++]);
	free(argv);
}
