/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_driver.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaddox <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 01:05:46 by smaddox           #+#    #+#             */
/*   Updated: 2019/09/08 22:12:02 by smaddox          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"

void	string_handle(char *str, uint8_t flags)
{
	if (CHECK_Q(flags))
	{
		md5_init((uint8_t*)str, ft_strlen(str));
		write(1, "\n", 1);
	}
	else if (CHECK_R(flags))
	{
		md5_init((uint8_t*)str, ft_strlen(str));
		ft_printf(" \"%s\"\n", str);
	}
	else
	{
		ft_printf("MD5 (\"%s\") = ", str);
		md5_init((uint8_t*)str, ft_strlen(str));
		write(1, "\n", 1);
	}
}

void	handle_error(char *str, uint8_t flags)
{
	if (str[0] == '-' && CHECK_S(flags))
		ft_printf("ft_ssl: md5: %s: invalid option\n", str);
	else
		ft_printf("ft_ssl: md5: %s: No such file\n", str);
	return ;
}

void	handle_file(char *f, uint8_t *flags)
{
	t_file file;

	ft_bzero(&file, sizeof(t_file));
	file = file_reader(f);
	if (file.error == -1)
	{
		handle_error(f, *flags);
		return ;
	}
	(CHECK_S(*flags)) ? TOGGLE_S(*flags) : 0;
	handle_file_two(file, *flags);
	return ;
}

void	handle_stdin(uint8_t *flags)
{
	t_file f;

	f = stdin_reader();
	if (CHECK_P(*flags))
		ft_printf("%s", f.data);
	md5_init(f.data, f.size);
	write(1, "\n", 1);
	free(f.data);
	TOGGLE_P(*flags);
	return ;
}

int		md5_driver(int ac, char **av)
{
	int		i;
	uint8_t	flags;

	i = -1;
	flags = 3;
	if (ac == 0)
		handle_stdin(&flags);
	TOGGLE_P(flags);
	md5_driver_helper(&i, &ac, &flags, av);
	return (0);
}
