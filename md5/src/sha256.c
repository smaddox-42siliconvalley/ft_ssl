/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaddox <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 20:57:10 by smaddox           #+#    #+#             */
/*   Updated: 2019/09/05 19:56:12 by smaddox          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha256.h"

void	sha256_set_buffer(t_context *context, int o)
{
	if (o == 0)
	{
		context->buffer[0] += context->abcd[0];
		context->buffer[1] += context->abcd[1];
		context->buffer[2] += context->abcd[2];
		context->buffer[3] += context->abcd[3];
		context->buffer[4] += context->abcd[4];
		context->buffer[5] += context->abcd[5];
		context->buffer[6] += context->abcd[6];
		context->buffer[7] += context->abcd[7];
	}
	else if (o == 1)
	{
		context->buffer[0] = 0x6a09e667;
		context->buffer[1] = 0xbb67ae85;
		context->buffer[2] = 0x3c6ef372;
		context->buffer[3] = 0xa54ff53a;
		context->buffer[4] = 0x510e527f;
		context->buffer[5] = 0x9b05688c;
		context->buffer[6] = 0x1f83d9ab;
		context->buffer[7] = 0x5be0cd19;
	}
}

void	sha256_expand_chunk(uint32_t *chunk, uint32_t *w)
{
	int			i;

	i = -1;
	while (++i < 64)
	{
		if (i < 16)
			w[i] = SWP(chunk[i]);
		else if (i < 64)
			w[i] = OM1(w[i - 2]) + w[i - 7] + OM0(w[i - 15]) + w[i - 16];
	}
}

void	sha256_transform(t_context *context, uint32_t *chunk)
{
	uint32_t	w[64];
	uint32_t	t1;
	uint32_t	t2;
	int			i;

	sha256_expand_chunk(chunk, w);
	ft_memcpy(context->abcd, context->buffer, 32);
	i = -1;
	while (++i < 64)
	{
		t1 = context->abcd[7] + E1(context->abcd[4]) + CH(context->abcd[4],
				context->abcd[5], context->abcd[6]) + g_consts[i] + w[i];
		t2 = E0(context->abcd[0]) +
			MAJ(context->abcd[0], context->abcd[1], context->abcd[2]);
		context->abcd[7] = context->abcd[6];
		context->abcd[6] = context->abcd[5];
		context->abcd[5] = context->abcd[4];
		context->abcd[5] = context->abcd[4];
		context->abcd[4] = context->abcd[3] + t1;
		context->abcd[3] = context->abcd[2];
		context->abcd[2] = context->abcd[1];
		context->abcd[1] = context->abcd[0];
		context->abcd[0] = t1 + t2;
	}
	sha256_set_buffer(context, 0);
}

void	sha256_init(uint8_t *str, size_t len)
{
	t_context	context;
	uint8_t		*input;
	uint64_t	num_bits;
	int			padded_length;

	ft_bzero(&context, sizeof(t_context));
	sha256_set_buffer(&context, 1);
	num_bits = len * 8;
	padded_length = ((((len + 8) / 64) + 1) * 64) - 8;
	input = (uint8_t*)malloc(padded_length + 8);
	ft_bzero(input, padded_length + 8);
	ft_memcpy(input, str, len);
	input[len] = 0x80;
	num_bits = (num_bits >> 56) | ((num_bits & 0xFF000000000000) >> 40) |
		((num_bits & 0xFF0000000000 >> 24) | ((num_bits & 0xFF00000000) >> 8) |
		((num_bits & 0xFF000000) << 8) | ((num_bits & 0xFF0000) << 24) |
		(num_bits & 0xFF00) << 40) | (num_bits << 56);
	*((uint64_t*)(input + padded_length)) = num_bits;
	sha256_final(&context, input, padded_length);
	free(input);
}

void	sha256_final(t_context *context, uint8_t *input, int padded_length)
{
	int i;
	int j;

	j = 0;
	i = -64;
	while ((i += 64) < padded_length)
		sha256_transform(context, (uint32_t*)(input + i));
	i = -1;
	while (++i < 8)
	{
		context->buffer[i] = SWP(context->buffer[i]);
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
	while (++i < 32)
		ft_printf("%02x", context->digest[i]);
}
