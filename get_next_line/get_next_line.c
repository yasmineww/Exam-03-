# include "get_next_line.h"
#include <stdio.h>

char *ft_strchr(char *line, int c)
{
	while (*line)
	{
		if (*line == (char)c)
			return ((char *)line);
		line++;
	}
	return (NULL);
}

void ft_strcpy(const char *buf, char *line)
{
	while (*buf)
	{
		*line = *buf;
		line++;
		buf++;
	}
	*line = '\0';
}

size_t	ft_strlen(const char *buf)
{
	size_t	 len;

	len = 0;
	while (*buf)
	{
		len++;
		buf++;
	}
	return (len);
}

char *ft_strdup(const char *buf)
{
	size_t	len = ft_strlen(buf) + 1; //changed this
	char	*line = malloc (len); //changed this

	if (!line)
		return (NULL);
	ft_strcpy(buf, line);
	return (line);
}

char *ft_strjoin(char *line, char *buf)
{
	size_t len1 = ft_strlen(line);
	size_t len2 = ft_strlen(buf);
	char	*join = malloc (len1 + len2 + 1);

	if (!line || !buf) // added this
		return (NULL);
	if (!join)
		return (NULL);
	ft_strcpy(line ,join);
	ft_strcpy(buf , (join + len1));
	free(line);
	return (join);
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*line;
	char		*newline;
	int			countread;
	int			to_copy;

	line = ft_strdup(buf);
	while (!(newline = ft_strchr(line, '\n')) && (countread = read(fd, buf, BUFFER_SIZE)))
	{
		buf[countread] = '\0';
		line = ft_strjoin(line, buf);
	}
	if (ft_strlen(line) == 0)
		return (free(line), NULL);

	if (newline != NULL)
	{
		to_copy = newline - line + 1;
		ft_strcpy(newline + 1, buf); // changed this
	}
	else
	{
		to_copy = ft_strlen(line);
		buf[0] = '\0';
	}
	line[to_copy] = '\0';
	return (line);
}

#include <fcntl.h>

int main (void)
{
	int fd = open("file", O_CREAT | O_RDWR);
	char *s;

	write(fd, "hello \n hey there jahahahahha \n", 32); //writing in the file
	close(fd);
	fd = open("file", O_RDONLY);
	s = get_next_line(fd);
	while (s != NULL)
	{
		printf("%s", s);
		free(s); //avoiding leaks
		s = get_next_line(fd); //incrementing, getting next_line
	}
	close (fd);
}