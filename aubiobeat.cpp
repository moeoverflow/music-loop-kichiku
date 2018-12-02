#include "aubiobeat.h"
#include <sstream>
#include "utils.h"

std::vector<long> find_beat(std::string sourcePath) {
    std::vector<long> beats;

    std::string output = exec("/usr/local/bin/aubio beat " + sourcePath);
    std::istringstream f(output);
    std::string line;
    while (std::getline(f, line)) {
        try {
            double beat = std::stod(line);
            beats.push_back(long(beat * 1000));
        } catch (std::invalid_argument error) {
           continue;
        }
    }

    return beats;
}
