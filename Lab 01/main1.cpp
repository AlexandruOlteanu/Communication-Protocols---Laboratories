#include <bits/stdc++.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
using namespace std;


int main()
{

    char input_name[100];
    cin >> input_name;

    int fd = open(input_name, O_RDONLY);

    if (fd < 0) {
        perror("Opening");
        exit(-1);
    }

    while (true) {
        char s[1005];
        memset(s, 0, sizeof(s));
        int rc = read(fd, &s, sizeof(s));
        if (rc < 0) {
            perror("Reading");
            exit(-1);
        }
        if (rc > 0) {
            printf("%s\n", s);
            continue;
        }
        break;
    }
    


    





    return 0;
}