#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "FileOperations.h"

int main(void) {
    struct LineInfo *text_ptr = (struct LineInfo *) calloc(FILESIZE + 1, sizeof(LineInfo));
    
    int err = pointers_text(text_ptr);
    free(text_ptr);
    return err;
}