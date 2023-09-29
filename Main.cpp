#include"window/Window_SFML.h"

int main(int argc, char* argv[]) {

    if (argc > 0) {
        std::string fullPath = argv[0];

        // Find the last directory separator (e.g., '/' or '\')
        size_t found = fullPath.find_last_of("/\\");

        if (found != std::string::npos) {
            // Extract the directory path
            std::string exeDirectory = fullPath.substr(0, found);
            std::cout << "Executable directory: " << exeDirectory << std::endl;

            Window_SFML window(exeDirectory);
            //window.run("./ROMs/PONG.ch8");
            //window.run("./ROMs/Blitz.ch8");
            //window.run("./ROMs/Hi-Lo.ch8");
            window.run("./ROMs/output");
        }
        else {
            std::cerr << "Unable to determine the executable directory." << std::endl;
        }
    }
    else {
        std::cerr << "No command-line arguments provided." << std::endl;
    }

	
}