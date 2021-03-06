/*
 * il_crypt.h - Implementation of useful cryptographic algorithms.
 *
 * Copyright (C) 2001  Southern Storm Software, Pty Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef	SHA256_H
#define	SHA256_H

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

//The size of SHA-256 hash values.
#define	SHA256_HASH_SIZE		32

//Context block for SHA-256.
typedef struct SHA256Context
{
   unsigned char input[64];
   unsigned int inputLen;
   unsigned int A, B, C, D, E, F, G, H;
   unsigned long totalLen[2];
     //simulated long long in which [0] is most significant
} SHA256Context;

//Initialize a SHA-256 context block.
void SHA256Init(SHA256Context *sha);

//Input more data into a SHA-256 context block.
void SHA256Data(SHA256Context *sha, const void *buffer, unsigned long len);

//Finalize a SHA-256 context block and output the hash.
void SHA256Finalize(SHA256Context *sha, unsigned char hash[SHA256_HASH_SIZE]);

//computes the SHA256 of the remainder of the stream f (but does not close it)
//Returns 0 on success, 1 on read error
int SHA256Stream(FILE *f, unsigned char hash[SHA256_HASH_SIZE]);

//computes the SHA256 of the file named filename
//Returns 0 if successful, -1 if file not found, or 1 if read error.
int SHA256File(const char *filename, unsigned char hash[SHA256_HASH_SIZE]);

#ifdef	__cplusplus
};
#endif

#endif	/* _IL_CRYPT_H */
