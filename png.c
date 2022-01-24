#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

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
    printf("Inspected file is %s\n", input_filepath);

    return 0;
}
