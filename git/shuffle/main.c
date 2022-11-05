#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "strings.h"


int main(int argc, char** argv) {
    if(argc != 2)
        return -1; 
    FILE* in = fopen(argv[1], "r");
    if(in == NULL)
        return -2;
    FILE* out;
    strings strs = strings_fillfromfile(in);
    strings_shuffle(strs);
    strings_print(strs);
    fclose(in);
    out = fopen(argv[1], "w");
    strings_fprint(strs, out);
    fclose(out);

    strings_free(strs);
}