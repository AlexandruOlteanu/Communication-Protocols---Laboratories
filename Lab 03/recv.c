#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "common.h"
#include "link_emulator/lib.h"

#define HOST "127.0.0.1"
#define PORT 10001

static inline uint8_t hamming_7to4(uint8_t c) {
	// TODO 3: Implement hamming decoding for one nibble
	bool d4 = ((c >> 0) & 1);
	bool d3 = ((c >> 1) & 1);
	bool d2 = ((c >> 2) & 1);
	bool d1 = ((c >> 4) & 1);

	bool p1 = ((c >> 6) & 1);
	bool p2 = ((c >> 5) & 1);
	bool p3 = ((c >> 3) & 1);

	bool z1 = (p1 ^ d1 ^ d2 ^ d4);
	bool z2 = (p2 ^ d1 ^ d3 ^ d4);
	bool z3 = (p3 ^ d2 ^ d3 ^ d4);
	int z = (z3 << 2) | (z2 << 1) | (z1);

	if (z == 3) {
		d1 ^= 1;
	}
	if (z == 5) {
		d2 ^= 1;
	}
	if (z == 6) {
		d3 ^= 1;
	}
	if (z == 7) {
		d4 ^= 1;
	}
	
	
	
	c = 0;
	c = (d1 << 3) | (d2 << 2) | (d3 << 1) | (d4);
	// TODO 4: Implement error correction
	return c;
}

size_t hamming_decode(uint8_t *enc, size_t len, uint8_t *buf) {
	for (size_t idx = 0; idx < (len / 2); idx++) {
		/* In the encoded message we have to concatenate 4 bits from two different bytes. */
		buf[idx] = hamming_7to4(enc[idx * 2]) << 4;
		buf[idx] |= hamming_7to4(enc[idx * 2 + 1]);
	}

	return len / 2;
}

int main(int argc,char** argv) {
	struct l3_msg t;
	init(HOST,PORT);

	uint8_t enc_ph[sizeof(struct l3_msg) * 2];

	/* Receive the encoded message */
	int len = link_recv(&enc_ph, sizeof(enc_ph));
	if (len < 0){
		perror("Receive message");
		return -1;
	}

	hamming_decode(enc_ph, len, (void *) &t);

	int sum_ok = inet_csum((void *) t.payload, t.hdr.len) == t.hdr.sum;

	printf("len=%d; sum(%s)=0x%04hx; payload=\"%s\";\n", t.hdr.len, sum_ok ? "GOOD" : "BAD", t.hdr.sum, t.payload);

	return 0;
}
