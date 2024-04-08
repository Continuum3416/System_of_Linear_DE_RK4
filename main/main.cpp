#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>
#include "ODE.h"
using namespace std;

//<--------------------------------Modify here---------------------------------->

const int N = 10000;     //steps
const double a = 0;     //starting interval
double initial_conditions[] = { 0.2, 0.2, 0.2 };

// x1' = x1 + 2x2 -3x3        x1(0) = 0.2
// x2' = -5x1 + x2 -4x3       x2(0) = 0.2
// x3' = -2x2 + 4x3           x3(0) = 0.2
double f1(double t, double u[]) { return 1 * u[0] + 2 * u[1] + (-3) * u[2]; }
double f2(double t, double u[]) { return (-5) * u[0] + u[1] + (-4) * u[2]; }
double f3(double t, double u[]) { return 0 * u[0] + (-2) * u[1] + 4 * u[2]; }

Function_Vector f[] = {f1, f2, f3};

int m = sizeof(f) / sizeof(f[0]);

//<----------------------------------------------------------------------------->

int main()
{
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

    auto t1 = high_resolution_clock::now();

    cout << "For a period of time,\n\n";
    const int times = 30;            //# of times print after the first time mark
    const double time_step = 0.1;   //time step
    int precision = 10;

    print_RK4(times, time_step, f, a, m, N, initial_conditions, precision, false);
    //cout << RK4_Sys(f, 0, 0.2, m, N, initial_conditions)[1] << endl << endl;
    auto t2 = high_resolution_clock::now();

    /* Getting number of milliseconds as an integer. */
    auto ms_int = duration_cast<milliseconds>(t2 - t1);

    /* Getting number of milliseconds as a double. */
    duration<double, std::milli> ms_double = t2 - t1;

    std::cout << "\nRun time: " << ms_int.count() << "ms\n";
    std::cout << "Run time (Exact): " << ms_double.count() << "ms\n";

    cout << "\n\n";
    system("pause");
    return 0;
}