#include <bits/stdc++.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
using namespace std;

struct Packet {
    char  payload[100];
    int   sum;
    int   size;
};

int main()
{
    int fd = open("ex3.txt", O_RDONLY);

    if (fd < 0) {
        perror("Opening");
        exit(-1);
    }
    while (true) {
        struct Packet p;
        memset(p.payload, 0, sizeof(p.payload));
        p.sum = -1;
        p.size = -1;
        int rc = read(fd, &p, sizeof(p));
        if (rc < 0) {
            perror("Reading");
            exit(-1);
        }
        if (rc > 0) {
            printf("%s\n%d\n%d\n\n", p.payload, p.sum, p.size);
            continue;
        }
        break;
    }
    





    return 0;
}