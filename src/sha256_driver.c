/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_driver.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaddox <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 02:55:53 by smaddox           #+#    #+#             */
/*   Updated: 2019/09/09 02:50:15 by smaddox          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha256.h"

void	sha256_string_handle(char *str, uint8_t flags)
{
	if (CHECK_Q(flags))
	{
		sha256_init((uint8_t*)str, ft_strlen(str));
		write(1, "\n", 1);
	}
	else if (CHECK_R(flags))
	{
		sha256_init((uint8_t*)str, ft_strlen(str));
		ft_printf(" \"%s\"\n", str);
	}
	else
	{
		ft_printf("SHA256 (\"%s\") = ", str);
		sha256_init((uint8_t*)str, ft_strlen(str));
		write(1, "\n", 1);
	}
}

void	sha256_handle_error(char *str, uint8_t flags)
{
	if (str[0] == '-' && CHECK_S(flags))
		ft_printf("ft_ssl: sha256: %s: invalid option\n", str);
	else
		ft_printf("ft_ssl: sha256: %s: No such file\n", str);
	return ;
}

void	sha256_handle_file(char *f, uint8_t *flags)
{
	t_file file;

	ft_bzero(&file, sizeof(t_file));
	file = file_reader(f);
	if (file.error == -1)
	{
		sha256_handle_error(f, *flags);
		return ;
	}
	(CHECK_S(*flags)) ? TOGGLE_S(*flags) : 0;
	sha256_handle_file_two(file, *flags);
	return ;
}

void	sha256_handle_stdin(uint8_t *flags)
{
	t_file f;

	f = stdin_reader();
	if (CHECK_P(*flags))
		ft_printf("%s", f.data);
	sha256_init(f.data, f.size);
	write(1, "\n", 1);
	free(f.data);
	return ;
}

int		sha256_driver(int ac, char **av)
{
	int		i;
	uint8_t	flags;

	i = -1;
	flags = 3;
	if (ac == 0)
		sha256_handle_stdin(&flags);
	TOGGLE_P(flags);
	sha256_driver_helper(&i, &ac, &flags, av);
	return (0);
}
