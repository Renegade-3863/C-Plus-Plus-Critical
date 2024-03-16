#pragma once
#include <iostream>

// Here we expect MGNL to be 5, but it actually is "3+2"
#define MGNL 3+2
// Here we expect MIN(a, b) to be a function used to choose a smaller one between a and b(Type unknown)
#define MIN(a, b) a < b ? a : b

void Testing_MGNL();
void Testing_MIN();
