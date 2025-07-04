/* fse.h */

#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <arcfour.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/random.h>

int8 *securerand(int16);
int8 *readkey(char*);
int main(int, char**);