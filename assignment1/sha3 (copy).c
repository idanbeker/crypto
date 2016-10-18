#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "sha3.h"

/* Useful macros */
/* Rotate a 64b word to the left by n positions */
#define ROL64(a, n) ((((n)%64) != 0) ? ((((uint64_t)a) << ((n)%64)) ^ (((uint64_t)a) >> (64-((n)%64)))) : a)
#define WORD_SIZE 64
#define STATE_ARRAY_SIZE 5


unsigned long concatenate(unsigned char **Z, const unsigned char *X,
			  unsigned long X_len, const unsigned char *Y,
			  unsigned long Y_len);
unsigned long concatenate_01(unsigned char **Z, const unsigned char *X,
			     unsigned long X_len);
unsigned long pad10x1(unsigned char **P, unsigned int x, unsigned int m);
unsigned char rc(unsigned int t);

//My functions:
unsigned char* keccak_p(unsigned char* input_string);
void string_to_stateArray(unsigned char* input_string , uint64_t stateArray[][STATE_ARRAY_SIZE]);
void print_stateArray(uint64_t stateArray[][STATE_ARRAY_SIZE]);
void theta(uint64_t stateArray[][STATE_ARRAY_SIZE]);
void roh(uint64_t stateArray[][STATE_ARRAY_SIZE]);
void pi(uint64_t stateArray[][STATE_ARRAY_SIZE]);
void chi(uint64_t stateArray[][STATE_ARRAY_SIZE]);
void iota(uint64_t stateArray[][STATE_ARRAY_SIZE], int round_number);

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

//This shift given by the table in specs.
const uint64_t roh_table[5][5] = {{0 , 1 , 190 , 28, 91},
									{36 ,300 , 6, 55 , 276},
									{3, 10 , 171 , 153 , 231},
									{105, 45 , 15 , 21 , 136},
									{210 , 66 , 253, 120, 78}};



const uint64_t RC[24] = {
     0x0000000000000001,
     0x0000000000008082,
     0x800000000000808A,
     0x8000000080008000,
     0x000000000000808B,
     0x0000000080000001,
     0x8000000080008081,
     0x8000000000008009,
     0x000000000000008A,
     0x0000000000000088,
     0x0000000080008009,
     0x000000008000000A,
     0x000000008000808B,
     0x800000000000008B,
     0x8000000000008089,
     0x8000000000008003,
     0x8000000000008002,
     0x8000000000000080,
     0x000000000000800A,
     0x800000008000000A,
     0x8000000080008081,
     0x8000000000008080,
     0x0000000080000001,
     0x8000000080008008
};





void main()
{
	uint64_t testStateArray1[5][5] = { 0 };
	uint64_t testStateArray2[5][5] = { 0 };
	
	string_to_stateArray(test1,testStateArray1);
	puts("Original 1");
	print_stateArray(testStateArray1);
	theta(testStateArray1);
	puts("Theta 1");
	print_stateArray(testStateArray1);
	roh(testStateArray1);
	puts("ro 1");
	print_stateArray(testStateArray1);
	
	string_to_stateArray(test2,testStateArray2);
	puts("Original 2 ");
	print_stateArray(testStateArray2);
	theta(testStateArray2);
	puts("Theta 2");
	print_stateArray(testStateArray2);
	roh(testStateArray2);
	puts("ro 2");
	print_stateArray(testStateArray2);
	pi(testStateArray2);
	puts("pi 2");
	print_stateArray(testStateArray2);
	chi(testStateArray2);
	puts("chi 2");
	print_stateArray(testStateArray2);
	iota(testStateArray2,0);
	puts("iota 2");
	print_stateArray(testStateArray2);
}





unsigned char* keccak_p(unsigned char* input_string)
{
uint64_t stateArray[5][5] = { 0 };

string_to_stateArray(input_string,stateArray);


}

void print_stateArray(uint64_t stateArray[][STATE_ARRAY_SIZE])
{
	int i = 0 , j = 0;
	for( i = 0; i <  STATE_ARRAY_SIZE; i++)
	{
		for(j = 0; j < STATE_ARRAY_SIZE; j++)
		{
		printf("%016llx\t", (unsigned long long)stateArray[i][j] );
		}
	puts("");
	}	
}


void string_to_stateArray(unsigned char* input_string , unsigned long stateArray[][STATE_ARRAY_SIZE])
{
	//Cast input string to long
	uint64_t* input_string_as_long = (uint64_t*) input_string;
	int x = 0 , y = 0;
	int counter = 0;

	for(y = 0; y < STATE_ARRAY_SIZE; y++)
	{
		for( x = 0; x < STATE_ARRAY_SIZE; x++)
		{
		stateArray[y][x] = input_string_as_long[counter++];
		}
	
	}	
}


void theta(uint64_t stateArray[][STATE_ARRAY_SIZE])
{
	uint64_t C[5] = {0};
	uint64_t D[5] = {0};
	uint64_t temp = 0;
	int i = 0, j = 0;
	
	for(i = 0; i < STATE_ARRAY_SIZE ; i++)
	{
		C[i] = stateArray[0][i] ^ stateArray[1][i] ^ stateArray[2][i] ^ stateArray[3][i] ^ stateArray[4][i];
	}
	
	for (i = 0; i < STATE_ARRAY_SIZE; i++) 
	{

         D[i]=C[(i + 4) % 5] ^ ROL64(C[(i + 1) % 5] ,1);
	}	
	
	for(i=0;i<5;i++)
	{
    	for( j = 0;j < 5;j++)
    	{
      	stateArray[j][i] = stateArray[j][i]^D[i];
      	}
    }

}



void roh(uint64_t stateArray[][STATE_ARRAY_SIZE])
{
	int x = 1, y = 0;
	int t= 0;
	int temp = 0;
	uint64_t stateArray_tag[5][5] = {0};
	
	//Copies array
	memcpy(stateArray_tag , stateArray , 25 * sizeof(uint64_t));

	
	for(t = 0; t <= 23; t++)
	{
	stateArray_tag[y][x] = ROL64(stateArray[y][x] , roh_table[y][x] % 64);
	temp = x;
	x = y;
	y =  ((2 * temp) + (3 * y)) % 5;
	}
	
	//Copies back
	memcpy(stateArray , stateArray_tag , 25 * sizeof(uint64_t));


}


void pi(uint64_t stateArray[][STATE_ARRAY_SIZE])
{
	int i = 0, j = 0;	
	uint64_t stateArray_tag[5][5] = {0};
	
	//Copies array
	memcpy(stateArray_tag , stateArray , 25 * sizeof(uint64_t));

	for(i = 0; i < STATE_ARRAY_SIZE; i++)
	{
		for( j = 0; j < STATE_ARRAY_SIZE; j++)
		{
			stateArray_tag[i][j] = stateArray[j][(j + (3 * i)) % 5];
		}
	}
		
	//Copies back
	memcpy(stateArray , stateArray_tag , 25 * sizeof(uint64_t));
	
}


void chi(uint64_t stateArray[][STATE_ARRAY_SIZE])
{
	int i = 0, j = 0;	
	uint64_t stateArray_tag[5][5] = {0};
	
	//Copies array
	memcpy(stateArray_tag , stateArray , 25 * sizeof(uint64_t));

	for(i = 0; i < STATE_ARRAY_SIZE; i++)
	{
		for( j = 0; j < STATE_ARRAY_SIZE; j++)
		{
			stateArray_tag[i][j] = stateArray[i][j] ^ ((~stateArray[i][(j + 1) % 5]) & stateArray[i][(j + 2) % 5]); 
		}
	}
	
	//Copies back
	memcpy(stateArray , stateArray_tag , 25 * sizeof(uint64_t));

}


void iota(uint64_t stateArray[][STATE_ARRAY_SIZE], int round_number)
{
	stateArray[0][0] ^= RC[round_number];
}



/* Compute the SHA-3 hash for a message.
 *
 * d - the output buffer
 * s - size of the output buffer in bits
 * m - the input message
 * l - size of the input message in bits
 */
void sha3(unsigned char *d, unsigned int s, const unsigned char *m,
	  unsigned int l)
{
	/* The hash size must be one of the supported ones */
	if (s != 224 && s != 256 && s != 384 && s != 512)
		return;

	/* Implement the rest of this function */
}

/* Concatenate two bit strings (X||Y)
 *
 * Z     - the output bit string. The array is allocated by this function: the
 *         caller must take care of freeing it after use.
 * X     - the first bit string
 * X_len - the length of the first string in bits
 * Y     - the second bit string
 * Y_len - the length of the second string in bits
 *
 * Returns the length of the output string in bits. The length in Bytes of the
 * output C array is ceiling(output_bit_len/8).
 */
unsigned long concatenate(unsigned char **Z, const unsigned char *X,
			  unsigned long X_len, const unsigned char *Y,
			  unsigned long Y_len)
{
	/* The bit length of Z: the sum of X_len and Y_len */
	unsigned long Z_bit_len = X_len + Y_len;
	/* The byte length of Z:
	 * the least multiple of 8 greater than X_len + Y_len */
	unsigned long Z_byte_len = (Z_bit_len / 8) + (Z_bit_len % 8 ? 1 : 0);
	// Allocate the output string and initialize it to 0
	*Z = calloc(Z_byte_len, sizeof(unsigned char));
	if (*Z == NULL)
		return 0;
	// Copy X_len/8 bytes from X to Z
	memcpy(*Z, X, X_len / 8);
	// Copy X_len%8 bits from X to Z
	for (unsigned int i = 0; i < X_len % 8; i++) {
		(*Z)[X_len / 8] |= (X[X_len / 8] & (1 << i));
	}
	// Copy Y_len bits from Y to Z
	unsigned long Z_byte_cursor = X_len / 8, Z_bit_cursor = X_len % 8;
	unsigned long Y_byte_cursor = 0, Y_bit_cursor = 0;
	unsigned int v;
	for (unsigned long i = 0; i < Y_len; i++) {
		// Get the bit
		v = ((Y[Y_byte_cursor] >> Y_bit_cursor) & 1);
		// Set the bit
		(*Z)[Z_byte_cursor] |= (v << Z_bit_cursor);
		// Increment cursors
		if (++Y_bit_cursor == 8) {
			Y_byte_cursor++;
			Y_bit_cursor = 0;
		}
		if (++Z_bit_cursor == 8) {
			Z_byte_cursor++;
			Z_bit_cursor = 0;
		}
	}
	return Z_bit_len;
}

/* Concatenate the 01 bit string to a given bit string (X||01)
 *
 * Z     - the output bit string. The array is allocated by this function: the
 *         caller must take care of freeing it after use.
 * X     - the bit string
 * X_len - the length of the string in bits
 *
 * Returns the length of the output string in bits. The length in Bytes of the
 * output C array is ceiling(output_bit_len/8).
 */
unsigned long concatenate_01(unsigned char **Z, const unsigned char *X,
			     unsigned long X_len)
{
	/* Due to the SHA-3 bit string representation convention, the 01
	 * bit string is represented in hexadecimal as 0x02.
	 * See Appendix B.1 of the Standard.
	 */
	unsigned char zeroone[] = { 0x02 };
	return concatenate(Z, X, X_len, zeroone, 2);
}

/* Performs the pad10*1(x, m) algorithm
 *
 * P - the output bit string. The array is allocated by this function: the
 *     caller must take care of freeing it after use.
 * x - the alignment value
 * m - the existing string length in bits
 *
 * Returns the length in bits of the output bit string.
 */
unsigned long pad10x1(unsigned char **P, unsigned int x, unsigned int m)
{
	/* 1. j = (-m-2) mod x */
	long j = x - ((m + 2) % x);
	/* 2. P = 1 || zeroes(j) || 1 */
	// Compute P bit and byte length
	unsigned long P_bit_len = 2 + j;
	unsigned long P_byte_len = (P_bit_len / 8) + (P_bit_len % 8 ? 1 : 0);
	// Allocate P and initialize to 0
	*P = calloc(P_byte_len, sizeof(unsigned char));
	if (*P == NULL)
		return 0;
	// Set the 1st bit of P to 1
	(*P)[0] |= 1;
	// Set the last bit of P to 1
	(*P)[P_byte_len - 1] |= (1 << (P_bit_len - 1) % 8);

	return P_bit_len;
}

/* Perform the rc(t) algorithm
 *
 * t - the number of rounds to perform in the LFSR
 *
 * Returns a single bit stored as the LSB of an unsigned char.
 */
unsigned char rc(unsigned int t)
{
	unsigned int tmod = t % 255;
	/* 1. If t mod255 = 0, return 1 */
	if (tmod == 0)
		return 1;
	/* 2. Let R = 10000000
	 *    The LSB is on the right: R[0] = R &0x80, R[8] = R &1 */
	unsigned char R = 0x80, R0;
	/* 3. For i from 1 to t mod 255 */
	for (unsigned int i = 1; i <= tmod; i++) {
		/* a. R = 0 || R */
		R0 = 0;
		/* b. R[0] ^= R[8] */
		R0 ^= (R & 1);
		/* c. R[4] ^= R[8] */
		R ^= (R & 0x1) << 4;
		/* d. R[5] ^= R[8] */
		R ^= (R & 0x1) << 3;
		/* e. R[6] ^= R[8] */
		R ^= (R & 0x1) << 2;
		/* Shift right by one */
		R >>= 1;
		/* Copy the value of R0 in */
		R ^= R0 << 7;
	}
	/* 4. Return R[0] */
	return R >> 7;
}
