#include "get_next_line.h"

char	*ft_strjoin(char *s1, const char *s2)
{
	size_t len1 = ft_strlen(s1);
	size_t len2 = ft_strlen(s2);
	char *join;

	join = malloc (len1 + len2 + 1);
	if (!s1 || !s2)
		return NULL;
	if (!join)
		return NULL;
	ft_strcpy(join, s1);
	ft_strcpy((join + len1), s2);
	free(s1);
	return (join);
}

char	*ft_strchr(char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

void	ft_strcpy(const char *src, char *dst)
{
	while (*src)
	{
		*dst = *src;
		dst++;
		src++;
	}
	*dst = '\0';
}

size_t	ft_strlen(const char *src)
{
	size_t count;

	count = 0;
	while (*src)
	{
		count++;
		src++;
	}
	return (count);
}


char	*ft_strdup(const char *src)
{
	size_t	len;
	char	*dst;

	len = ft_strlen(src) + 1;
	dst = malloc(len);
	if (dst)
		return (NULL);
	ft_strcpy(src, dst);
	return (dst);
}

char	*get_next_line(int fd)
{
	static char buf[BUFFER_SIZE + 1];
	char	*line;
	char	*newline;
	int		countread;
	int		to_copy;

	line = ft_strdup(buf);
	while (!(newline = ft_strchr(line, '\n')) && (countread = read(fd, buf, BUFFER_SIZE)))
	{
		buf [countread] = '\0';
		line = ft_strjoin(line, buf);
	}
	if (ft_strlen(line) == 0)
        return (free(line), NULL);

    if (newline != NULL)
    {
        to_copy = newline - line + 1;
        ft_strcpy(buf, newline + 1);
    }
    else
    {
        to_copy = ft_strlen(line);
        buf[0] = '\0';
    }
    line[to_copy] = '\0';
    return (line);
}
