#include "durex.h"

char	*ft_crypt(char *buff, off_t size)
{
	off_t	i = 0;

	while (i < size)
	{
		buff[i] -= 41;
		++i;
	}
	return (buff);
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
