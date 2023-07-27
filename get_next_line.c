/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnaulak <lnaulak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 09:18:27 by lnaulak           #+#    #+#             */
/*   Updated: 2023/07/27 14:18:34 by lnaulak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*full_str;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	full_str = read_function(fd, full_str);
	if (!full_str)
		return (NULL);
	line = ft_getline(full_str);
	full_str = ft_getrest(full_str);
	return (line);
}

char	*read_function(int fd, char *str)
{
	char	*mal;
	int		i;

	i = 1;
	mal = malloc(sizeof(char) * BUFFER_SIZE + 1);
	while (ft_nline(str) == 0 && i != 0)
	{
		i = read(fd, mal, BUFFER_SIZE);
		if (i == -1)
		{
			free(mal);
			free(str);
			return (NULL);
		}
		mal[i] = '\0';
		str = ft_strjoin(str, mal);
	}
	free(mal);
	return (str);
}

char	*ft_getline(char *full_str)
{
	int		i;
	char	*line;

	i = 0;
	if (!full_str[i])
		return (NULL);
	while (full_str[i] && full_str[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (full_str[i] && full_str[i] != '\n')
	{
		line[i] = full_str[i];
		i++;
	}
	if (full_str[i] == '\n')
	{
		line[i] = full_str[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_getrest(char *full_str)
{
	int		i;
	int		j;
	char	*restof;

	i = 0;
	while (full_str[i] && full_str[i] != '\n')
		i++;
	if (!full_str[i])
	{
		free(full_str);
		return (NULL);
	}
	restof = (char *)malloc(sizeof(char) * (ft_strlen(full_str) - i + 1));
	i++;
	j = 0;
	while (full_str[i])
		restof[j++] = full_str[i++];
	restof[j] = '\0';
	free(full_str);
	return (restof);
}
/*
int main(void)
{
	for (int i = 0; i < 2; i++)
	{
		int fd = open("somerandomefile.txt", O_RDONLY);
		printf("%s", get_next_line(fd));
	}
	return 0;
}*/