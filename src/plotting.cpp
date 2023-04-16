#include "plotting.h"
#include "stat.h"
#include "trase.hpp"
#include <fstream>
#include <vector>
#include <string>

int create_plot(std::vector<Measurement> &ms, const std::string &plot_name,
                const std::string &x_label, const std::string &y_label) 
{
    /// create figure and axis
    auto fig = trase::figure();
    auto ax = fig->axis();

    /// create x and y vectors and set y = sin(x)
    int n = ms.size(); 
    std::vector<int> x(n);
    std::vector<double> y(n);
    for (int i = 0; i < n; ++i) {
        x[i] = ms[i].data_size;
        y[i] = ms[i].value;
    }

    /// create a trase dataset and then plot it using a line geometry
    auto data = trase::create_data().x(x).y(y);
    auto plt = ax->line(data);

    /// label axis
    ax->xlabel(x_label.c_str());
    ax->ylabel(y_label.c_str());

    auto max_measurement = std::max_element(ms.begin(), ms.end(), [](Measurement &a, Measurement &b)
    {
        return a.value < b.value;
    });
    double max_latency = max_measurement->value;
    float ylimit = static_cast<float>(max_latency);
    //ax->ylim({0, ylimit });

    // output to chosen backend
    std::string file_name = plot_name + ".svg";
    std::ofstream out(file_name);
    if (!out) {
        std::cerr << "[Error]: can't create plot file" << std::endl;
        return 1;
    }

    trase::BackendSVG backend(out);
    fig->draw(backend);
    out.close();

    return 0;
}