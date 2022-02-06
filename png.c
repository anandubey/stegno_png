#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>

#define PNG_SIG_CAP 8
const uint8_t png_sig[PNG_SIG_CAP] = {137, 80, 78, 71, 13, 10, 26, 10};

void read_buffer_or_panic(FILE *file, uint8_t *buf, size_t buf_cap)
{
    size_t n = fread(buf, buf_cap, 1, file);
    if(n != 1) {
        if(ferror(file)) {
            fprintf(stderr, "ERROR: Could not read PNG header: %s\n", strerror(errno));
            exit(1);
        } else if (feof(file)) {
            fprintf(stderr, "ERROR: Could not read PNG header: reached the end of file!\n");
            exit(1);
        } else {
            assert(0 && "unreachable");
        }
    }
}


void print_bytes(uint8_t *buf, size_t buf_cap)
{
    for (size_t i=0; i < buf_cap; ++i) {
        printf("%u ", buf[i]);
    } 
    printf("\n");
}


int main(int argc, char **argv)
{
    (void) argc;
    assert(*argv != NULL);

    char *program = *argv++;

    if (*argv == NULL) {
        fprintf(stderr, "Usage: %s <input.png>\n", program);
        fprintf(stderr, "ERROR: No Input file is provided!\n");
        exit(1);
    }
    
    char *input_filepath = *argv++;

    FILE *input_file = fopen(input_filepath, "rb");
    if (input_file == NULL){
        fprintf(stderr, "ERROR: Could not open file %s: %s\n", input_filepath, strerror(errno));
        exit(1);
    }


    uint8_t sig[8];
    read_buffer_or_panic(input_file, sig, sizeof(sig));
    
    print_bytes(sig, sizeof(sig));

    fclose(input_file);

    return 0;
}
