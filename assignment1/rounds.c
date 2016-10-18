#include "rounds.h"


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


