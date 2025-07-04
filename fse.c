/* fse.c */
#include "fse.h"

// int8 *securerand(int16 size){
//     int8 *start, *p;
//     size_t n;

//     assert(size > 0);
//     p = (int8 *)malloc(size);
//     assert(p);
//     start = p;

//     n = getrandom(p, (size_t)size, GRND_RANDOM | GRND_NONBLOCK);

//     if (n == size)
//         return p;
//     else if (n < 0){
//         free(p);
//         return 0;
//     }

//     fprintf(stderr, "Warning: Entropy pool is"
//         " empty. This may take longer than usual.\n");

//     p += n;
//     n = getrandom(p, (size - n), GRND_RANDOM);

//     if (n == size)
//         return start;

//     else {
//         free(start);
//         return 0;
//     }
// }

int8 *securerand(int16 size) {
    int8 *start, *p;
    size_t n = 0;

    assert(size > 0);

    p = (int8 *)malloc(size);
    assert(p);
    start = p;

    int fd = open("/dev/urandom", O_RDONLY);
    if (fd < 0) {
        perror("open /dev/urandom");
        free(p);
        return 0;
    }

    // Try to read all bytes in one go
    ssize_t r = read(fd, p, size);
    if (r < 0) {
        perror("read");
        close(fd);
        free(p);
        return 0;
    }

    if (r == size) {
        close(fd);
        return start;
    }

    fprintf(stderr, "Warning: Entropy pool is incomplete. This may take longer than usual.\n");

    // Try to read the rest of the bytes
    p += r;
    n = read(fd, p, size - r);

    close(fd);

    if ((r + n) == size) {
        return start;
    } else {
        free(start);
        return 0;
    }
}

int8 *readkey(char *prompt){
    char buf[256];
    int8 *p;
    int8 size;

    // Prompt
    printf("%s ", prompt);
    fflush(stdout);

    // Read up to 255 chars
    memset(buf, 0, sizeof buf);
    ssize_t r = read(STDIN_FILENO, buf, sizeof(buf)-1);
    if (r <= 0) {
        perror("read");
        return NULL;
    }

    // Strip trailing newline, if present
    size = (int8)r;
    if (buf[size-1] == '\n') {
        buf[size-1] = '\0';
        size--;
    }

    // Allocate exactly size+1 bytes (including NUL)
    p = malloc(size+1);
    assert(p);

    // Copy and NUL-terminate
    memcpy(p, buf, size);
    p[size] = '\0';

    return p;
}

int main(int argc, char *argv[]){
    Arcfour *rc4;
    char *infile, *outfile;
    int infd, outfd;  // file discriptors
    int8 *key;
    int16 keysize;
    int16 padsize;
    int16 *padsize16;
    int8 *padsize8;
    int8 *padding;

    if (argc < 3){
        fprintf(stderr,
            "Usage: %s <infile> <outfile>\n",*argv);

        return -1;
    }
    infile = argv[1];
    outfile = argv[2];
 
    infd = open(infile, O_RDONLY);
    if (infd < 1){
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
    padsize8 = securerand(2);
    padsize16 = (int16 *) padsize8;
    padsize = *padsize16;
    printf("padsize: %d\n", (int)padsize);

    close(infd);
    close(outfd);
    free(padsize8);
    
    return 0;
}