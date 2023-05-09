#include <string>
#include <iostream>
#include <map>

#include <boost/program_options.hpp>

#include "bars.h"

namespace po = boost::program_options;

int main(int argc, char** argv) {
    po::options_description desc("General options");
    std::string sortType;
    int barsAmount = 100;
    int waitTime = 10;
    
    desc.add_options()  ("help,h", "Show help")
                        ("alg,a", po::value<std::string>(&sortType), "Sorting algorithm to perform")
                        ("count,c", po::value<int>(&barsAmount), "Amount of bars to be sorted")
                        ("wait,w", po::value<int>(&waitTime), "Time to wait in microseconds after each operation");
    
    po::variables_map vm;
    po::parsed_options parsed = po::command_line_parser(argc, argv).options(desc).allow_unregistered().run();
    po::store(parsed, vm);
    po::notify(vm);

    
    if (vm.count("alg") || vm.count("a")) {
        Bars bars;
        if (vm.count("count") || vm.count("c")) {
            bars.setBarsAmount(vm["count"].as<int>());
        }
        if (vm.count("wait") || vm.count("w")) {
            bars.setWaitTime(vm["wait"].as<int>());
        }
        bars.performSort(vm["alg"].as<std::string>());
    } else {
        std::cout << desc << std::endl;
    }


    return 0;
}