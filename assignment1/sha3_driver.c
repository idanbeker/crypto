/* This file gets replaced with our own driver when we grade your submission.
 * You can do what you want here, but it will be discarded when grading.
 */
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sha3.h"

//Test input:
unsigned char test1[200] = {0};
unsigned char test2[200] = {
							0xE7, 0xDD ,0xE1 ,0x40 ,0x79 ,0x8F, 0x25, 0xF1 ,0x8A ,0x47 ,0xC0 ,0x33 ,0xF9 ,0xCC ,0xD5 ,0x84 ,0xEE ,0xA9 ,0x5A 
							,0xA6 ,0x1E ,0x26 ,0x98 ,0xD5 ,0x4D ,0x49 ,0x80 ,0x6F ,0x30 ,0x47 ,0x15 ,0xBD ,0x57 ,0xD0 ,0x53 ,0x62 ,0x05 ,0x4E 
							,0x28 ,0x8B ,0xD4 ,0x6F ,0x8E ,0x7F ,0x2D ,0xA4 ,0x97 ,0xFF ,0xC4 ,0x47 ,0x46 ,0xA4 ,0xA0 ,0xE5 ,0xFE ,0x90 ,0x76
							 ,0x2E ,0x19 ,0xD6 ,0x0C ,0xDA ,0x5B ,0x8C ,0x9C ,0x05 ,0x19 ,0x1B ,0xF7 ,0xA6 ,0x30 ,0xAD ,0x64 ,0xFC ,0x8F ,0xD0 
							 ,0xB7 ,0x5A ,0x93 ,0x30 ,0x35 ,0xD6 ,0x17 ,0x23 ,0x3F ,0xA9 ,0x5A ,0xEB ,0x03 ,0x21 ,0x71 ,0x0D ,0x26 ,0xE6 ,0xA6
							  ,0xA9 ,0x5F ,0x55 ,0xCF ,0xDB ,0x16 ,0x7C ,0xA5 ,0x81 ,0x26 ,0xC8 ,0x47 ,0x03 ,0xCD ,0x31 ,0xB8 ,0x43 ,0x9F ,0x56
							   ,0xA5 ,0x11 ,0x1A ,0x2F ,0xF2 ,0x01 ,0x61 ,0xAE ,0xD9 ,0x21 ,0x5A ,0x63 ,0xE5 ,0x05 ,0xF2 ,0x70 ,0xC9 ,0x8C ,0xF2
							    ,0xFE ,0xBE ,0x64 ,0x11 ,0x66 ,0xC4 ,0x7B ,0x95 ,0x70 ,0x36 ,0x61 ,0xCB ,0x0E ,0xD0 ,0x4F ,0x55 ,0x5A ,0x7C ,0xB8
							     ,0xC8 ,0x32 ,0xCF ,0x1C ,0x8A ,0xE8 ,0x3E ,0x8C ,0x14 ,0x26 ,0x3A ,0xAE ,0x22 ,0x79 ,0x0C ,0x94 ,0xE4 ,0x09 ,0xC5 
							     ,0xA2 ,0x24 ,0xF9 ,0x41 ,0x18 ,0xC2 ,0x65 ,0x04 ,0xE7 ,0x26 ,0x35 ,0xF5 ,0x16 ,0x3B ,0xA1 ,0x30 ,0x7F ,0xE9 ,0x44 
							     ,0xF6 ,0x75 ,0x49 ,0xA2 ,0xEC ,0x5C ,0x7B ,0xFF ,0xF1 ,0xEA}; 


int main(void)
{



	uint64_t testStateArray1[5][5] = { 0 };
	uint64_t testStateArray2[5][5] = { 0 };
	
	keccak_p(test1);


	unsigned char *message[5];
	unsigned char *digest[5];
	unsigned int len[5];

	/* 1. Message = "", len = 0 */
	unsigned char message_0[] = "";
	message[0] = message_0;
	len[0] = 0;
	unsigned char digest_0[] = {
		0xa7, 0xff, 0xc6, 0xf8, 0xbf, 0x1e, 0xd7, 0x66,
		0x51, 0xc1, 0x47, 0x56, 0xa0, 0x61, 0xd6, 0x62,
		0xf5, 0x80, 0xff, 0x4d, 0xe4, 0x3b, 0x49, 0xfa,
		0x82, 0xd8, 0x0a, 0x4b, 0x80, 0xf8, 0x43, 0x4a
	};
	digest[0] = digest_0;
	/* 2. Message = "abc", len = 24 */
	unsigned char message_1[] = "abc";
	message[1] = message_1;
	len[1] = 24;
	unsigned char digest_1[] = {
		0x3a, 0x98, 0x5d, 0xa7, 0x4f, 0xe2, 0x25, 0xb2,
		0x04, 0x5c, 0x17, 0x2d, 0x6b, 0xd3, 0x90, 0xbd,
		0x85, 0x5f, 0x08, 0x6e, 0x3e, 0x9d, 0x52, 0x5b,
		0x46, 0xbf, 0xe2, 0x45, 0x11, 0x43, 0x15, 0x32
	};
	digest[1] = digest_1;
	/* 3. Message = "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq"
	 *    len = 448 */
	unsigned char message_2[] =
	    "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq";
	message[2] = message_2;
	len[2] = 448;
	unsigned char digest_2[] = {
		0x41, 0xc0, 0xdb, 0xa2, 0xa9, 0xd6, 0x24, 0x08,
		0x49, 0x10, 0x03, 0x76, 0xa8, 0x23, 0x5e, 0x2c,
		0x82, 0xe1, 0xb9, 0x99, 0x8a, 0x99, 0x9e, 0x21,
		0xdb, 0x32, 0xdd, 0x97, 0x49, 0x6d, 0x33, 0x76
	};
	digest[2] = digest_2;
	/* 4. Message = "abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmn
	 *               hijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu"
	 *    len = 896 */
	unsigned char message_3[] =
	    "abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmn"
	    "hijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu";
	message[3] = message_3;
	len[3] = 896;
	unsigned char digest_3[] = {
		0x91, 0x6f, 0x60, 0x61, 0xfe, 0x87, 0x97, 0x41,
		0xca, 0x64, 0x69, 0xb4, 0x39, 0x71, 0xdf, 0xdb,
		0x28, 0xb1, 0xa3, 0x2d, 0xc3, 0x6c, 0xb3, 0x25,
		0x4e, 0x81, 0x2b, 0xe2, 0x7a, 0xad, 0x1d, 0x18
	};
	digest[3] = digest_3;
	/* 5. Message = 1 million "a" (0x61), len = 8 * 1 000 000 */
	message[4] = calloc(1000000, sizeof(unsigned char));
	memset(message[4], 0x61, 1000000);
	len[4] = 8000000;
	unsigned char digest_4[] = {
		0x5c, 0x88, 0x75, 0xae, 0x47, 0x4a, 0x36, 0x34,
		0xba, 0x4f, 0xd5, 0x5e, 0xc8, 0x5b, 0xff, 0xd6,
		0x61, 0xf3, 0x2a, 0xca, 0x75, 0xc6, 0xd6, 0x99,
		0xd0, 0xcd, 0xcb, 0x6c, 0x11, 0x58, 0x91, 0xc1
	};
	digest[4] = digest_4;

	unsigned char d[32];

	for (int i = 0; i < 5; i++) {
		sha3(d, 256, message[i], len[i]);
		printf("%s\n", !memcmp(d, digest[i], 32) ? "PASS" : "FAIL");
	}

	free(message[4]);
	return 0;
}