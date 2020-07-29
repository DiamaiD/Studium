// Copyright 2020, Viktor Gange
// Author: Viktor Gange <viktor.gange@gmail.com>

#include <stdio.h>
#include <math.h>
#include "./ApproximateEulersNumber.h"

// Simple program that approximates the Eulers number
int main(int argc, char** argv) {
    int n = 10;
    float euler = approximateEulersNumber(n);
    printf("\n");
    printf("Compute Euler Number for        : %d!\n", n);
    printf("Approximation of Euler Number   : %f\n", euler);
    printf("\n");
}
