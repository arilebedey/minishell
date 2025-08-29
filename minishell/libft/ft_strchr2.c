#include <malloc.h>

char	*ft_strchr2(const char *s, const char *delim)
{
	int	i;
	int	j;

	i = -1;
	while (s[++i])
	{
		j = -1;
		while (delim[++j])
		{
			if (s[i] == delim[j])
				return ((char *)(s + i));
		}
	}
	return (NULL);
}
