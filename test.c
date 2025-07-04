#include <stdio.h>
#include <stdlib.h>
#include <arcfour.h>

int main() {
    // Initialize the RC4 context with key "hello"
    Arcfour *ctx = rc4init((int8 *)"hello", 5);
    if (!ctx) {
        fprintf(stderr, "Failed to initialize RC4 context.\n");
        return 1;
    }

    // Encrypt the message
    char *message = "secret";
    int16 size = 6;

    int8 *cipher = rc4encrypt(ctx, (int8 *)message, size);
    if (!cipher) {
        fprintf(stderr, "Encryption failed.\n");
        free(ctx);
        return 1;
    }

    printf("Encrypted: ");
    for (int i = 0; i < size; i++) {
        printf("%02x ", (unsigned char)cipher[i]);
    }
    printf("\n");

    // Free memory
    free(cipher);
    free(ctx);

    return 0;
}
