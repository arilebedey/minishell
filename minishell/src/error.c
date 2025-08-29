#include <unistd.h>
#include "../libft/libft.h"

void	print_error(const char *msg)
{
	write(2, msg, ft_strlen(msg));
}
