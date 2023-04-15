#ifndef PLOTTING_H
#define PLOTTING_H

#include <stat.h>
#include <vector>
#include <string>

int create_plot(std::vector<Measurement> &ms, const std::string &plot_name,
                const std::string &x_label, const std::string &y_label);

#endif