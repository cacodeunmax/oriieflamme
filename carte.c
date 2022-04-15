#include "struct.c"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int equals_carte(carte c, carte v){
    return (strcmp(c.name,v.name)&&(c.function_number==v.function_number));
}