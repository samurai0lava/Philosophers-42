/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 09:46:58 by iouhssei          #+#    #+#             */
/*   Updated: 2023/12/19 09:47:06 by iouhssei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*free_null(char *content)
{
	free(content);
	return (NULL);
}

static char	*rest(char *str)
{
	char	*rest;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	rest = malloc((ft_strlen(str) - i + 1) * sizeof(char));
	if (!rest)
	{
		free(rest);
		return (NULL);
	}
	i++;
	while (str[i])
		rest[j++] = str[i++];
	rest[j] = '\0';
	free(str);
	return (rest);
}

static char	*read_line(int fd, char *content)
{
	char	*buff;
	int		bytesread;

	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	bytesread = 1;
	while (!ft_strchr(content, '\n') && bytesread != 0)
	{
		bytesread = read(fd, buff, BUFFER_SIZE);
		if (bytesread == -1)
		{
			free(content);
			free(buff);
			return (NULL);
		}
		buff[bytesread] = '\0';
		content = ft_strjoin(content, buff);
	}
	free(buff);
	if (content[0] == '\0' || content == NULL)
		return (free_null(content));
	return (content);
}

static char	*extract_line(char *content)
{
	char	*line;
	int		i;

	i = 0;
	if (!content)
		return (NULL);
	while (content[i] != '\n' && content[i] != '\0')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (content[i] != '\n' && content[i] != '\0')
	{
		line[i] = content[i];
		i++;
	}
	if (content[i] == '\n')
	{
		line[i] = content[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*content;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	content = read_line(fd, content);
	if (!content)
		return (NULL);
	line = extract_line(content);
	content = rest(content);
	return (line);
}
