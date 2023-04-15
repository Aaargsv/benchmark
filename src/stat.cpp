#include "stat.h"
#include <vector>
#include <cmath>
#include <iostream>


void update_parameters_online(double &mean, double &m2, int &sample_count, double new_value)
{
    sample_count++;
    double delta = new_value - mean;
    mean += delta / sample_count;
    double delta2 = new_value - mean;
    m2 += delta * delta2;
}

double calc_variance_online(double m2, int sample_count)
{
    return m2 / sample_count;
}

double calc_sd_online(double m2, int sample_count)
{
    return sqrt(m2 / sample_count);
}

double calc_standard_error_online(double m2, int sample_count)
{
    return sqrt(m2 / sample_count) / sqrt(sample_count);
}

double calc_average(std::vector<double> &data, int n)
{
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += data[i];
    }
    return sum / n;
}

double calc_variance(std::vector<double> &data, int n)
{
    double avr = calc_average(data, n);
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += (data[i] - avr) * (data[i] - avr);
    }
    return sum / n;
}

double calc_standard_deviation(std::vector<double> &data, int n)
{
    double var = calc_variance(data, n);
    return sqrt(var);
}

void print_measurements(std::vector<Measurement> &ms)
{
    for (int i = 0; i < ms.size(); i++) {
        std::cout << "delay: " << ms[i].avr_duration << " size: " << ms[i].data_size << std::endl;
    }
}
