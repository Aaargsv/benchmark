#ifndef STAT_H
#define STAT_H

#define THRESHOLD 0.2
#define SAMPLE_SIZE 2
#define CHECK_SAMPLE_SIZE 50

#include <vector>

struct Measurement {
    double value;
    int data_size;
};

void update_parameters_online(double &mean, double &m2, int &sample_count, double new_value);
double calc_variance_online(double m2, int sample_count);
double calc_sd_online(double m2, int sample_count);
double calc_standard_error_online(double m2, int sample_count);
void print_measurements(std::vector<Measurement> &ms);
double calc_mean(std::vector<double> &data, int n);
double calc_variance(std::vector<double> &data, int n);
double calc_standard_deviation(std::vector<double> &data, int n);

#endif