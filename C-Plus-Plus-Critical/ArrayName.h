#pragma once
#include <iostream>
using namespace std;

int arr[3];
int arr2D[2][3];

void traverse(int arr[]) {
    cout << "arr is: " << arr << "\t&arr is: " << &arr << "\t&arr[0] is: " << &arr[0] << endl;
}
void traverse2D(int arr2D[][3]) {
    cout << "arr2D is: " << arr2D << "\t&arr2D is: " << &arr2D << "\t&arr2D[0] is: " << &arr2D[0] << endl;
}