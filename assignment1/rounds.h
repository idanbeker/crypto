#include <inttypes.h>
#include <string.h>
#include <stdlib.h>

#define ROL64(a, n) ((((n)%64) != 0) ? ((((uint64_t)a) << ((n)%64)) ^ (((uint64_t)a) >> (64-((n)%64)))) : a)
#define WORD_SIZE 64
#define STATE_ARRAY_SIZE 5


void print_stateArray(uint64_t stateArray[][STATE_ARRAY_SIZE]);
void theta(uint64_t stateArray[][STATE_ARRAY_SIZE]);
void roh(uint64_t stateArray[][STATE_ARRAY_SIZE]);
void pi(uint64_t stateArray[][STATE_ARRAY_SIZE]);
void chi(uint64_t stateArray[][STATE_ARRAY_SIZE]);
void iota(uint64_t stateArray[][STATE_ARRAY_SIZE], int round_number);



