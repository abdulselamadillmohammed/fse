/* fse.c */
#include <fse.h>

int main(int argc, char argv[]){
    Arcfour *rc4;
    char *infile, *outfile;
    int infd, outfd;  // file discriptors
    int8 *key;
    int16 keysize;


    if (argc < 3){
        fprintf(stderr,
            "Usage: %s <infile> <outfile>\n",*argv);

        return -1;
    }
    infile = argv[1];
    outfile = argv[2];

    infd = open(infile, O_RDONLY);
    if (infile < 1){
        perror("open");
        return -1;
    }

    outfd = open(outfile, O_WRONLY|O_CREAT, 00600);
    if (outfd < 1){
        close(infd);
        perror("open");
    
        return -1;
    }

    key = readkey("Key: ");
    assert(key);
    keysize = (int16)strlen((char *)key);
}