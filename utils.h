#include <iostream>
#include <stdio.h>
#include <stdlib.h>

std::string exec(std::string cmd);

void set_interval(std::function<void(void)> function, int interval);
