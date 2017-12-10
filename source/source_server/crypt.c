#include "durex.h"

char	*ft_crypt(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (NULL);
	while (str[i] != '\0')
	{
		/*str[i] += 5;*/
		i++;
	}
	return (str);
}

char	*ft_decrypt(char *str)
{
	int i = 0;

	if	(str == NULL)
		return (NULL);
	while (str[i] != '\0')
		i++;
	i--;
	while (i >= 0)
	{
		str[i] -= 5;
		i--;
	}
	return (str);
}
