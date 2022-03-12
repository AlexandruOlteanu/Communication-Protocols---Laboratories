#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "link_emulator/lib.h"

#define HOST "127.0.0.1"
#define PORT 10001

#define DLE (char)0
#define STX (char)2
#define ETX (char)3

/* TODO 2: write recv_frame function */

char* recv_text() {
    
    char c1, c2;
    do {
      c1 = recv_byte();
      c2 = recv_byte();
    }while (c1 != DLE || c2 != STX);

    char *s = (char *)malloc(100 * sizeof(char));
    int i = 0;
    while (1) {
      c1 = recv_byte();
      if (c1 != DLE && c1 != ETX) {
        s[i] = c1;
        ++i;
      }
      else {
        char c2 = recv_byte();
        if (c1 == DLE && c2 == ETX) {
           break;
        }
      }
    }
    s[i] = '\0';
    return s;
}

int recv_nr() {
   char c1, c2;
    do {
      c1 = recv_byte();
      c2 = recv_byte();
    }while (c1 != DLE || c2 != STX);
    return 0;
}

int recv_frame(char *buffer, int max_size)
{
      /* Am primit începutul de frame? */
      char c1, c2;
 
      c1 = recv_byte();
      c2 = recv_byte();
 
      while((c1 != DLE) && (c2 != STX)) {
         c1 = c2;
         c2 = recv_byte();
      }
 
      for (int i = 0; i < max_size; i++) {
        char byte = recv_byte();
      
        if (byte == DLE) {
          byte = recv_byte();
 
          if (byte == ETX)
            return i;
 
          else if (byte != DLE)
            return -1;
        }
 
        buffer[i] = byte; 
      }
 
      return max_size;
}

int main(int argc,char** argv){
  init(HOST,PORT);
  

  // char c;

  /* Wait for the start of a frame */
  // char c1,c2;
  // do {
	// c1 = recv_byte();
	// c2 = recv_byte();
  // } while(c1 != DLE || c2 != STX);
  
  // printf("%d ## %d\n",c1, c2);
  // c = recv_byte();
  // printf("%c\n", c);

  // c = recv_byte();
  // printf("%c\n", c);

  // c = recv_byte();
  // printf("%c\n", c);

  // c = recv_byte();
  // printf("%c\n", c);

  // c = recv_byte();
  // printf("%c\n", c);

  // c = recv_byte();
  // printf("%c\n", c);

  // while (1) {
  //    char *s = recv_text();
  //    printf("%s\n", s);
  //    if (strcmp(s, "END") == 0) {
  //      break;
  //    }
  // }

  int len = recv_nr();
  char *s = recv_text();
  int sum = recv_nr();
  printf("%d\n", len);
  printf("%s\n", s);
  printf("%d\n", sum);
 

  /* TODO 2: Run the receiver until you receive the frame DONE */

  /* TODO 3: receive a frame with a structure of type Packet */

  


  /* TODO 4: Measure latency in a while loop for any frame that contains a timestamp we receive, print frame_size and latency */

  printf("[RECEIVER] Finished transmission\n");
  return 0;
}
