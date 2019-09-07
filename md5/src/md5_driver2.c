/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_driver2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaddox <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 16:07:30 by smaddox           #+#    #+#             */
/*   Updated: 2019/09/06 19:49:22 by smaddox          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "md5.h"

void	handle_file_two(t_file f, uint8_t flags)
{
	if (CHECK_Q(flags))
	{
		md5_init(f.data, f.size);
		write(1, "\n", 1);
	}
	else if (CHECK_R(flags))
	{
		md5_init(f.data, f.size);
		ft_printf(" \"%s\"\n", f.name);
	}
	else
	{
		ft_printf("MD5 (%s) = ", f.name);
		md5_init(f.data, f.size);
		write(1, "\n", 1);
	}
	free(f.data);
}

void	md5_fuck_norm(int *i, int *ac, uint8_t *flags, char **av)
{
	while (++(*i) < (*ac))
    {
        if ((ft_strcmp(av[(*i)], "-q") == 0) && !CHECK_Q(*flags) && CHECK_S(*flags))
        {
            TOGGLE_Q(*flags);
            (CHECK_R(*flags)) ? TOGGLE_R(*flags) : 0;
        }
        else if ((ft_strcmp(av[(*i)], "-r") == 0) &&
                !CHECK_Q(*flags) && CHECK_S(*flags) && !CHECK_R(*flags))
            TOGGLE_R(*flags);
        else if ((ft_strcmp(av[(*i)], "-s") == 0) && CHECK_S(*flags))
            string_handle(av[++(*i)], *flags);
        else if ((ft_strcmp(av[(*i)], "-p") == 0) && CHECK_S(*flags))
        {
            TOGGLE_P(*flags);
            handle_stdin(flags);
        }
        else
            handle_file(av[(*i)], flags);
	}
}
