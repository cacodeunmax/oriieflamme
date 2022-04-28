#include "struct.c"
#include "struct.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "carte.h"


char* get_name(carte c){
    return c.name;
}

int get_func(carte c){
    return c.function_number;
}

int equals_carte(carte c, carte v){
    return (strcmp(c.name,v.name)&&(c.function_number==v.function_number));
}

