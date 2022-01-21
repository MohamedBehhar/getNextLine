/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbehhar <mbehhar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 09:44:58 by mbehhar           #+#    #+#             */
/*   Updated: 2021/11/14 15:31:50 by mbehhar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	free_ptr(void *ptr)
{
	if (ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}
}

void	res_update(char **res)
{
	char	*ret;
	size_t	start;
	size_t	len;

	start = 0;
	len = ft_strlen(*res);
	while ((*res)[start] != '\n' && (*res)[start] != '\0')
		start++;
	if ((*res)[start] == '\n')
		start++;
	if (len == start)
	{
		free(*res);
		*res = NULL;
	}
	ret = *res;
	*res = ft_substr(*res, start, (len - start));
	free_ptr(ret);
}

char	*get_the_line(char *res)
{
	char	*line;
	int		len;

	if (ft_strlen(res) == 0)
		return (NULL);
	len = 0;
	while (res[len] != '\n' && res[len] != '\0')
		len++;
	if (res[len] == '\n')
		len++;
	line = ft_substr(res, 0, len);
	return (line);
}

char	*ft_read(int fd, char *res, int n_byte)
{
	char	*buf;
	int		n;

	buf = (char *)malloc(sizeof(char) * n_byte + 1);
	if (buf == NULL)
		return (NULL);
	if (!res)
		res = ft_strdup("");
	n = 1;
	while ((n != 0) && (ft_strchr(res, '\n') == NULL))
	{
		n = read(fd, buf, n_byte);
		if (n == -1)
		{
			free_ptr(res);
			free_ptr(buf);
			return (NULL);
		}
		buf[n] = '\0';
		res = ft_strjoin(res, buf);
	}
	free_ptr(buf);
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*res;
	char		*line;
	int			n_byte;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	n_byte = 128;
	if (n_byte > BUFFER_SIZE)
		n_byte = BUFFER_SIZE;
	res = ft_read(fd, res, n_byte);
	if (res == NULL)
		return (NULL);
	line = get_the_line(res);
	res_update(&res);
	return (line);
}
