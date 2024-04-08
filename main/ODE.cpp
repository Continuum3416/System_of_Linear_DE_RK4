#include "ODE.h"


void special_operator(double k_n[], double w[], double factor, double kn[], int m) {
    for (int i = 0; i < m; i++)
        k_n[i] = w[i] + factor * kn[i];
    return;
}

//m: number of equations/initial condition
//N: number of steps
//i: solution number, w[0] for w1(t), w[1] for w2(t), and so on...
template <typename T> std::vector<T> RK4_Sys(T(*f[]) (T, T[]), T a, T b, int m, int N, T A[])
{
    T h = (b - a) / T(N);
    T t = a;

    T* w = new T[m];
    T* k1 = new T[m];
    T* k2 = new T[m];
    T* k3 = new T[m];
    T* k4 = new T[m];

    T* k_1 = new T[m];
    T* k_2 = new T[m];
    T* k_3 = new T[m];

    for (int j = 0; j < m; j++) {
        w[j] = A[j];
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < m; j++) {
            k1[j] = h * f[j](t, w);
        }

        special_operator(k_1, w, 0.5, k1, m);
        for (int j = 0; j < m; j++) {
            k2[j] = h * f[j](t + h / 2, k_1);
        }

        special_operator(k_2, w, 0.5, k2, m);
        for (int j = 0; j < m; j++) {
            k3[j] = h * f[j](t + h / 2, k_2);
        }

        special_operator(k_3, w, 1.0, k3, m);
        for (int j = 0; j < m; j++) {
            k4[j] = h * f[j](t + h, k_3);
        }

        for (int j = 0; j < m; j++) {
            w[j] = w[j] + (1.0 / 6.0) * (k1[j] + 2 * k2[j] + 2 * k3[j] + k4[j]);
        }

        t = a + (i + 1) * h;
    }

    std::vector<T> result(m);
    for (int j = 0; j < m; j++) {
        result[j] = w[j];
    }

    delete[] w;
    delete[] k1;
    delete[] k2;
    delete[] k3;
    delete[] k4;
    delete[] k_1;
    delete[] k_2;
    delete[] k_3;

    return result;
}

int count_digits(double* num) {
    if (num == nullptr) {
        // Handle the case where the pointer is null
        std::cerr << "Error: Null pointer passed to count_digits function\n";
        return -1; // Or handle it differently based on your requirements
    }

    long long n = static_cast<long long>(std::abs(*num));
    if (n == 0) return 1;
    return static_cast<int>(std::floor(std::log10(n))) + 1;
}

std::string space(int num, std::string s) {
    std::string spacing;
    for (int i = 0; i < num; i++)
        spacing += s;
    return spacing;
}

void print_RK4
(int times, double TS, double (*f[]) (double, double[]), double a, int m, int N, double A[], int precision, bool align)
{
    int inside_space;
    std::vector<double> display(m);
    int max = 0;

    for (int i = 0; i <= times; i++) {
        display = RK4_Sys(f, a, a + i * TS, m, 5, A);
        for (int j = 0; j < m; j++) {
            inside_space = count_digits(&display[j]);
            if (inside_space > max)
                max = inside_space;
        }
    }
    std::cout << "t" << std::setw(8);
    for (int i = 0; i < m; i++)
        std::cout << "w" << i + 1 << "(t) RK4" << std::setw(precision + max - 1) << std::right;
    std::cout << std::endl;

    std::cout << space(8 + m * (max + precision) + m * 5, "-") << std::endl;

    for (int i = 0; i <= times; i++) {
        std::cout << std::setw(7) << std::left;
        std::cout << std::setprecision(1) << std::fixed << a + i * TS;
        std::cout << std::setprecision(precision) << std::fixed;

        std::vector<double> result = RK4_Sys(f, a, a + i * TS, m, N, A);

        for (int j = 0; j < m; j++) {
            
            inside_space = count_digits(&result[j]);
            if (align) {
                if (result[j] >= 0)
                    std::cout << " " << space(max - inside_space, "0") << result[j];
                else
                    std::cout << "-" << space(max - inside_space, "0") << (-1) * result[j];
            }
            else {
                (result[j] >= 0) ? std::cout << " " : std::cout << "";
                std::cout << result[j] << space(max - inside_space, " ");
            }

            std::cout << "     "; //5 spaces
        }
        std::cout << std::endl;
    }

    return;
}