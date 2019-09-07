/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaddox <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 02:26:37 by smaddox           #+#    #+#             */
/*   Updated: 2019/09/07 02:26:41 by smaddox          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void     who_are_you_people(t_dis_table dispatch)
{
    int i;

    i = -1;
    ft_printf("\nStandard commands:\n");
	while (++i < TABLE_LENGTH)
        if (ft_strcmp(dispatch.table[i].designation, "Standard command") == 0)
            ft_printf("%s\n", dispatch.table[i].key);
    i = -1;
    ft_printf("\nMessage Digest commands:\n");
    while (++i < TABLE_LENGTH)
        if (ft_strcmp(dispatch.table[i].designation, "Message Digest command") == 0)
            ft_printf("%s\n", dispatch.table[i].key);
    i = -1;
    ft_printf("\nCipher commands:\n");
    while (++i < TABLE_LENGTH)
        if (ft_strcmp(dispatch.table[i].designation, "Cipher command") == 0)
            ft_printf("%s\n", dispatch.table[i].key);
}

static void     throw_error(int status, t_dis_table dispatch, char *str)
{
    int i;

    i = -1;
    if (status == 1)
        ft_printf("usage: ft_ssl command [command opts] [command args]\n");
    else if (status == 2)
    {
        ft_printf("ft_ssl: ERROR: '%s' is an invalid command\n", str);
        who_are_you_people(dispatch);
        ft_printf("\n");
    }
    return ;
}



int             main(int ac, char **av)
{
    int     i;
    int     throw_err;

    throw_err = 1;
    INIT_SSL_TABLE(dispatch);
    if (ac > 1)
    {
        throw_err = 2;
        i = -1;
        while (++i < TABLE_LENGTH)
        {
            if (ft_strcmp(dispatch.table[i].key, av[1]) == 0)
            {
                dispatch.table[i].func((ac - 2), (av += 2));
                throw_err = 0;
                break ;
            }
        }
    }
    if (throw_err != 0)
       throw_error(throw_err, dispatch, av[1]);
    return (0);
}

