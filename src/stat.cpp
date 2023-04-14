#include "stat.h"
#include <vector>
#include <cmath>
#include <iostream>

double average(std::vector<double> &data, int n)
{
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += data[i];
    }
    return sum / n;
}

double variance(std::vector<double> &data, int n)
{
    double avr = average(data, n);
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += (data[i] - avr) * (data[i] - avr);
    }
    return sum / n;
}

double standard_deviation(std::vector<double> &data, int n)
{
    double var = variance(data, n);
    return sqrt(var);
}

void print_measurements(std::vector<Mesurement> &ms)
{
    for (int i = 0; i < ms.size(); i++) {
        std::cout << "delay: " << ms[i].avr_duration << " size: " << ms[i].data_size << std::endl;
    }
}
