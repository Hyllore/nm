/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/30 11:55:39 by droly             #+#    #+#             */
/*   Updated: 2016/04/29 15:18:49 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_put_in_str(int i, int i2, char **line, char *str)
{
	while ((*line)[i] != '\n')
		i++;
	(*line)[i] = '\0';
	i++;
	while ((*line)[i] != '\0')
	{
		i++;
		i2++;
	}
	i = 0;
	while ((*line)[i] != '\0')
		i++;
	i++;
	str = ft_strnew(i2);
	i2 = 0;
	while ((*line)[i] != '\0')
	{
		str[i2] = (*line)[i];
		i++;
		i2++;
	}
	str[i2] = '\0';
	return (str);
}

char			*ft_treat(char **line, int ret, char *tmp)
{
	char		*tmp2;

	tmp[ret] = '\0';
	tmp2 = ft_strnew(ft_strlen(*line) + ft_strlen(tmp));
	tmp2 = ft_strcpy(tmp2, *line);
	free(*line);
	*line = ft_strnew(ft_strlen(tmp2) + ft_strlen(tmp));
	*line = ft_strjoin(tmp2, tmp);
	free(tmp2);
	free(tmp);
	return (*line);
}

int				ft_str_is_null(int ret, int fd, char **str, char **line)
{
	char		*tmp;

	while (ft_strchr(*line, 10) == NULL && ret > 0)
	{
		tmp = ft_strnew(BUFF_SIZE);
		ret = read(fd, tmp, BUFF_SIZE);
		*line = ft_treat(line, ret, tmp);
	}
	if (ft_strchr(*line, 10) != NULL)
	{
		*str = ft_put_in_str(0, 0, line, *str);
		return (1);
	}
	if (ft_strchr(*line, 10) == NULL && ret == 0 && *line[0] != '\0')
		ret = 1;
	return (ret);
}

int				get_next_line(int const fd, char **line)
{
	static char	*str[100];
	int			ret;

	ret = 0;
	if (fd > 256 || fd < 0 || !line)
		return (-1);
	if (str[fd] == NULL)
	{
		*line = ft_strnew(BUFF_SIZE);
		ret = read(fd, *line, BUFF_SIZE);
		(*line)[ret] = '\0';
		ret = ft_str_is_null(ret, fd, &str[fd], line);
		return (ret);
	}
	if (str[fd] != NULL)
	{
		*line = ft_strnew(BUFF_SIZE + ft_strlen(str[fd]));
		ret = read(fd, *line, BUFF_SIZE);
		*line = ft_strjoin(str[fd], *line);
		(*line)[ret + ft_strlen(str[fd])] = '\0';
		free(str[fd]);
		str[fd] = NULL;
		ret = ft_str_is_null(ret, fd, &str[fd], line);
	}
	return (ret);
}
