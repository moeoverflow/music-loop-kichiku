#include "utils.h"
#include <thread>
#include <chrono>

std::string exec(std::string cmd) {
    std::string data;
    FILE * stream;
    const int max_buffer = 256;
    char buffer[max_buffer];
    cmd.append(" 2>&1");

    stream = popen(cmd.c_str(), "r");
    if (stream) {
        while (!feof(stream))
            if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
        pclose(stream);
    }
    return data;
}

void set_interval(std::function<void(void)> function, int interval) {
    std::thread th([=]() {
        while(true) {
            std::this_thread::sleep_for(std::chrono::milliseconds(interval));
            function();
        }
    });
    th.detach();
}
