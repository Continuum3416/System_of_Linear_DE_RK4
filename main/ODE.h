#pragma once
#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

//extern int m; 

typedef double (*Function_Vector) (double t, double u[]);

template <typename T> std::vector<T> RK4_Sys(T(*f[]) (T, T[]), T, T, int, int, T*);

void print_RK4(int, double, double (*f[]) (double, double[]), double, int, int, double*, int, bool);