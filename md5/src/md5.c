/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaddox <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 20:03:37 by smaddox           #+#    #+#             */
/*   Updated: 2019/09/05 20:24:01 by smaddox          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"

void		md5_init(uint8_t *str, size_t len)
{
	t_contxt	context;
	uint8_t		*input;
	uint32_t	num_bits;
	int			padded_length;

	ft_bzero(&context, sizeof(t_contxt));
	context.buffer[0] = 0x67452301;
	context.buffer[1] = 0xefcdab89;
	context.buffer[2] = 0x98badcfe;
	context.buffer[3] = 0x10325476;
	num_bits = len * 8;
	padded_length = ((((len + 8) / 64) + 1) * 64) - 8;
	input = (uint8_t*)malloc(padded_length + 8);
	ft_bzero(input, padded_length + 8);
	ft_memcpy(input, str, len);
	input[len] = 0x80;
	ft_memcpy(input + padded_length, &num_bits, 4);
	md5_final(&context, input, padded_length);
	free(input);
}

void		md5_final(t_contxt *context, uint8_t *input, int padded_length)
{
	int i;
	int j;

	j = 0;
	i = -64;
	while ((i += 64) < padded_length)
		md5_transform(context, (uint32_t *)(input + i));
	i = -1;
	while (++i < 4)
	{
		context->digest[j] =
			(uint8_t)(context->buffer[i] & 0xFF);
		context->digest[j + 1] =
			(uint8_t)((context->buffer[i] >> 8) & 0xFF);
		context->digest[j + 2] =
			(uint8_t)((context->buffer[i] >> 16) & 0xFF);
		context->digest[j + 3] =
			(uint8_t)((context->buffer[i] >> 24) & 0xFF);
		j += 4;
	}
	i = -1;
	while (++i < 16)
		ft_printf("%02x", context->digest[i]);
}

uint32_t	md5_crunch(t_contxt *context, int i)
{
	uint32_t n;

	if (i < 16)
		n = (context->abcd[1] & context->abcd[2]) |
			((~context->abcd[1]) & context->abcd[3]);
	else if (i < 32)
		n = (context->abcd[3] & context->abcd[1]) |
			((~context->abcd[3]) & context->abcd[2]);
	else if (i < 48)
		n = context->abcd[1] ^ context->abcd[2] ^ context->abcd[3];
	else
		n = context->abcd[2] ^ (context->abcd[1] | (~context->abcd[3]));
	return (n);
}

void		md5_transform(t_contxt *context, uint32_t *chunk)
{
	int			i;
	uint32_t	n;
	uint32_t	temp;

	context->abcd[0] = context->buffer[0];
	context->abcd[1] = context->buffer[1];
	context->abcd[2] = context->buffer[2];
	context->abcd[3] = context->buffer[3];
	i = -1;
	while (++i < 64)
	{
		n = md5_crunch(context, i);
		temp = context->abcd[3];
		context->abcd[3] = context->abcd[2];
		context->abcd[2] = context->abcd[1];
		context->abcd[1] = context->abcd[1] +
			ROT_L((context->abcd[0] + n + g_constants[i] + chunk[g_c[i]]),
					g_shifts[i]);
		context->abcd[0] = temp;
	}
	context->buffer[0] += context->abcd[0];
	context->buffer[1] += context->abcd[1];
	context->buffer[2] += context->abcd[2];
	context->buffer[3] += context->abcd[3];
}
