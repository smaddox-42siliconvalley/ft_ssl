/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaddox <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 20:29:55 by smaddox           #+#    #+#             */
/*   Updated: 2019/09/07 17:30:22 by smaddox          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SHA256_H
# define FT_SHA256_H

# include "ft_printf.h"
# include "utils.h"

# define ROT_R(x, y) (((x) >> (y)) | ((x) << (32-(y))))
# define CH(x, y, z) (((x) & (y)) ^ ((~x) & (z)))
# define MAJ(x, y, z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
# define SWP(x) ((x)>>24)|(((x)&0xFF0000)>>8)|(((x)&0xFF00)<<8)|((x)<<24)
# define E0(x) (ROT_R((x), 2) ^ (ROT_R((x), 13)) ^ (ROT_R((x), 22)))
# define E1(x) (ROT_R((x), 6) ^ (ROT_R((x), 11)) ^ (ROT_R((x), 25)))
# define OM0(x) ((ROT_R((x), 7)) ^ (ROT_R((x), 18)) ^ (x >> 3))
# define OM1(x) ((ROT_R((x), 17)) ^ (ROT_R((x), 19)) ^ (x >> 10))

typedef struct		s_context
{
	uint32_t		buffer[8];
	uint32_t		abcd[8];
	uint8_t			digest[32];
}					t_context;

void				sha256_init(uint8_t *input, size_t input_len);
void				sha256_final(t_context *context, uint8_t *input,
		int padded_length);
void				sha256_transform(t_context *context, uint32_t *chunk);
void				sha256_expand_chunk(uint32_t *chunk, uint32_t *w);
void				sha256_set_buffer(t_context *context, int o);
void				sha256_string_handle(char *str, uint8_t flags);
void				sha256_handle_error(char *str, uint8_t flags);
void				sha256_handle_file(char *f, uint8_t *flags);
void				sha256_handle_file_two(t_file f, uint8_t flags);
void				sha256_handle_stdin(uint8_t *flags);
int					sha256_driver(int ac, char **av);
void				sha256_driver_helper(int *i, int *ac,
		uint8_t *flags, char **av);

static uint32_t g_consts[64] =
{
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
	0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
	0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
	0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
	0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
	0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
	0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
	0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

#endif
