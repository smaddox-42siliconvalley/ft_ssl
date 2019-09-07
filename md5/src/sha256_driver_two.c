/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_driver_two.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaddox <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 03:01:13 by smaddox           #+#    #+#             */
/*   Updated: 2019/09/07 09:38:04 by smaddox          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha256.h"

void	sha256_handle_file_two(t_file f, uint8_t flags)
{
	if (CHECK_Q(flags))
	{
		sha256_init(f.data, f.size);
		write(1, "\n", 1);
	}
	else if (CHECK_R(flags))
	{
		sha256_init(f.data, f.size);
		ft_printf(" %s\n", f.name);
	}
	else
	{
		ft_printf("sha256 (%s) = ", f.name);
		sha256_init(f.data, f.size);
		write(1, "\n", 1);
	}
	free(f.data);
}

void	sha256_driver_helper(int *i, int *ac, uint8_t *flags, char **av)
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
            sha256_string_handle(av[++(*i)], *flags);
        else if ((ft_strcmp(av[(*i)], "-p") == 0) && CHECK_S(*flags))
        {
            TOGGLE_P(*flags);
            sha256_handle_stdin(flags);
        }
        else
            sha256_handle_file(av[(*i)], flags);
	}
}
