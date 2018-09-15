#include <iostream>
#include "Application.h"


int main(int argc, char* args[]) {
    try {
        Application application;  //we create...
        application.start();     //and start the application
    } catch (std::exception& e) {
        std::cerr << "Application was unable to start" << std::endl;
    }
    return 0;
}
