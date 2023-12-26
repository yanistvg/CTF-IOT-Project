#include <iostream>
#include <csignal>
#include <unistd.h>
#include <cstdlib>

void sigIntHandler(int sigNum)
{
    std::cout << "Stopping..." << std::endl;
    std::exit(EXIT_SUCCESS);
}

int main(int argc, char** argv)
{
    float frequency = 100.f;
    std::string musicFile;

    int opt;
    while ((opt = getopt(argc, argv, "f:m:")) != -1) {
        switch (opt) {
            case 'f':
                frequency = std::stof(optarg);
                break;
            case 'm':
                musicFile = optarg;
                break;
        }
    }

    if (musicFile.empty()) {
        std::cout << "Usage: " << argv[0] << " -f <frequency> -m <music_file>" << std::endl;
        return EXIT_FAILURE;
    }

    std::signal(SIGINT, sigIntHandler);

    // Transmitting FM signal using PiFmRds
    std::string command = "sudo ./pifmrds -audio " + musicFile + " -freq " + std::to_string(frequency);
    std::cout << "Broadcasting at " << frequency << " MHz" << std::endl;

    // Execute the PiFmRds command
    system(command.c_str());

    return EXIT_SUCCESS;
}
