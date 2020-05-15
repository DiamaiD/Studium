// Copyright 2020, Viktor Gange
// Author: Viktor Gange <viktor.gange@gmail.com>

// Simple program that approximates the Eulers number
float approximateEulersNumber(int n) {
    int numberOfIterations = n;
    int k = 0;
    float teiler = 1.0;
    float euler = 0.0;
    for (int i = 0; i <= numberOfIterations; i++) {
        if (k != 0) {
            teiler = teiler * k;
        } else {
            teiler = teiler * 1;
        }
        euler += 1 / teiler;
        k++;
    }
    return euler;
}
