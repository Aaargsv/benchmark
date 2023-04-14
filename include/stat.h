#ifndef STAT_H
#define STAT_H

#define THRESHOLD 0.05
#define SAMPLE_SIZE 10

#include <vector>

struct Mesurement {
    double avr_duration;
    int data_size;
};

void print_measurements(std::vector<Mesurement> &ms);
double average(std::vector<double> &data, int n);
double variance(std::vector<double> &data, int n);
double standard_deviation(std::vector<double> &data, int n);

#endif