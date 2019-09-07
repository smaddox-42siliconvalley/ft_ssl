/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaddox <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 02:49:07 by smaddox           #+#    #+#             */
/*   Updated: 2019/09/07 05:15:42 by smaddox          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stdio.h>
#include "libft.h"

t_file	file_reader(char *f)
{
	int		fd;
	int		bytes;
	char	garbage;
	t_file	temp;

	ft_bzero(&temp, sizeof(temp));	
	temp.name = f;
	if ((fd = open(f, O_RDONLY)) < 0)
	{
		temp.error = -1;
		return(temp);
	}
	while ((bytes = read(fd, &garbage, 1)) > 0)
		temp.size++;
	temp.data = (uint8_t*)malloc(temp.size);
	close(fd);
	fd = open(f, O_RDONLY);
	read(fd, temp.data, temp.size);
	close(fd);
	return (temp);
}

t_file	stdin_reader(void)
{
	t_file	temp;
	uint8_t	*tmp;
	uint8_t	buf[2];

	ft_bzero(&buf, 2);
	ft_bzero(&temp, sizeof(t_file));
	temp.data = (uint8_t*)malloc(1);
	temp.data[0] = '\0';
	while (read(0, &buf, 1) > 0)
	{
		tmp = temp.data;
		temp.data = (uint8_t*)ft_strjoin((char*)temp.data, (char*)buf);
		temp.size++;
		free(tmp);
	}
	return(temp);
}





