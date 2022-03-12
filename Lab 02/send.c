#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "link_emulator/lib.h"

/* We don't touch this */
#define HOST "127.0.0.1"
#define PORT 10000

#define DLE (char)0
#define STX (char)2
#define ETX (char)3

/* TODO 2: implement send_frame function */

struct Packet {
	int len;
	char payload[1500];
	int sum;
};


void send_text(char *s) {
	send_byte(DLE);
	send_byte(STX);

	for(int i = 0; i < strlen(s); i++) {
		send_byte(s[i]);
	}

	send_byte(DLE);
	send_byte(ETX);
}

void send_packet(struct Packet pkg) {
	send_byte(DLE);
	send_byte(STX);
	char *int_byte_ptr = &(pkg.len);
	for(int i = 0; i < sizeof(int); i++) {
		send_byte(int_byte_ptr[i]);
	}
	send_byte(DLE);
	send_byte(ETX);
	send_text(pkg.payload);
	send_byte(DLE);
	send_byte(STX);
	int_byte_ptr = &(pkg.sum);
	for(int i = 0; i < sizeof(int); i++) {
		send_byte(int_byte_ptr[i]);
	}
	send_byte(DLE);
	send_byte(ETX);
}




int main(int argc,char** argv){
	init(HOST,PORT);

	/* Send Hello */
	// send_byte(DLE);
	// send_byte(STX);
	// send_byte('H');
	// send_byte('e');
	// send_byte('l');
	// send_byte('l');
	// send_byte('o');
	// send_byte('!');

	/* TODO 2: call send_frame function with a given string input */

	// char *p[100];
	// int i = 0;

	// while (1) {
	// 	char *s = (char *)malloc(100 * sizeof(char));
	// 	scanf("%s", s);
	// 	p[i] = s;
	// 	++i;
	// 	if (strcmp(s, "END") == 0) {
	// 		break;
	// 	}
	// }
	// int n = i - 1;
	// for (int j = 0; j <= n; ++j) {
	// 	send_text(p[j]);
	// }


	/* TODO 3: use send_frame to send a structure of type Packet */

	struct Packet pack;
	scanf("%d", &pack.len);
	memset(pack.payload, 0, sizeof(pack.payload));
	scanf("%s", pack.payload);
	scanf("%d", &pack.sum);
	send_packet(pack);

	

	/* TODO 4: send 100 bytes, send 300 bytes, append a timestamp to these frames */	
	
	return 0;
}
