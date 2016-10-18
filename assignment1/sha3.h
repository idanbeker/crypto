/* Implement the following API. Do NOT modify the given prototypes. */

/* Compute the SHA-3 hash for a message.
 *
 * d - the output buffer (allocated by the caller)
 * s - size of the output buffer in bits
 * m - the input message
 * l - size of the input message in bits
 */
void sha3(unsigned char *d, unsigned int s, const unsigned char *m,
	  unsigned int l);

//My functions:
void string_to_stateArray(unsigned char* input_string , uint64_t stateArray[][STATE_ARRAY_SIZE]);
unsigned char* keccak_p(unsigned char* input_string);

/* You can add your own functions below this line.
 * Do NOT modify anything above. */
