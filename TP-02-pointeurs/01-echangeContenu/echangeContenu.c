#include "echangeContenu.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// TODO implementer echangeContenu



void echangeContenu (int *a, int *b){
    int *c = *a;
    *a = *b;
    *b = c;
}
