/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinsecho <jinsecho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:11:35 by jinsecho          #+#    #+#             */
/*   Updated: 2024/03/27 21:57:07 by jinsecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*backup_free(char **backup, char *tmp)
{
	if (*backup == NULL)
		return (NULL);
	free(*backup);
	*backup = tmp;
	return (*backup);
}

char	*gnl_strdup(char *string)
{
	char	*ptr_arr;
	int		len;
	int		i;

	i = 0;
	len = 0;
	if (string == NULL)
		return (NULL);
	while (string[len])
		len++;
	ptr_arr = (char *)malloc(sizeof(char) * (len + 1));
	if (ptr_arr == NULL)
		return (backup_free(&string, NULL));
	while (i < len)
	{
		ptr_arr[i] = string[i];
		i++;
	}
	ptr_arr[i] = 0;
	return (ptr_arr);
}

char	*new_line_check(char **backup)
{
	char	*tmp;
	char	*pl;
	int		i;

	i = 0;
	if (!*backup || !**backup)
		return (backup_free(backup, NULL));
	if (gnl_strchr(*backup, '\n'))
	{
		while ((*backup)[i] && (*backup)[i] != '\n')
			i++;
		pl = gnl_substr(*backup, 0, i + 1);
		tmp = gnl_strdup(&((*backup)[i + 1]));
		if (tmp == NULL)
			return (NULL);
		*backup = backup_free(backup, tmp);
		return (pl);
	}
	pl = gnl_strdup(*backup);
	if (*backup != NULL)
		*backup = backup_free(backup, NULL);
	return (pl);
}

char	*nl_find(char **backup)
{
	char	*tmp;
	char	*pl;
	int		i;

	i = 0;
	while ((*backup)[i] && (*backup)[i] != '\n')
		i++;
	pl = gnl_substr(*backup, 0, i + 1);
	if (pl == NULL)
		return (NULL);
	tmp = gnl_strdup(&((*backup)[i + 1]));
	if (tmp == NULL)
		return (backup_free(backup, NULL));
	*backup = backup_free(backup, tmp);
	return (pl);
}

char	*get_next_line(int fd)
{
	static char	*backup;
	char		*pl;
	char		buf[BUFFER_SIZE + 1];
	int			wc;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	wc = read(fd, buf, BUFFER_SIZE);
	if (wc == 0)
		return (new_line_check(&backup));
	if (backup == NULL)
		backup = gnl_strdup("");
	while (wc > 0)
	{
		buf[wc] = 0;
		backup = gnl_strjoin(backup, buf);
		if (gnl_strchr(backup, '\n'))
			return (nl_find(&backup));
		wc = read(fd, buf, BUFFER_SIZE);
	}
	if (wc == -1)
		return (backup_free(&backup, NULL));
	pl = gnl_strdup(backup);
	backup = backup_free(&backup, NULL);
	return (pl);
}
