#include"window/Window_SFML.h"

int main(int argc, char* argv[]) {

    //Find file directory
    if (argc > 0) {
        std::string fullPath = argv[0];

        // Find the last directory separator (e.g., '/' or '\')
        size_t found = fullPath.find_last_of("/\\");

        if (found != std::string::npos) {
            // Extract the directory path
            std::string exeDirectory = fullPath.substr(0, found);
            std::cout << "Executable directory: " << exeDirectory << std::endl;

            Window_SFML window(exeDirectory,BLACK,WHITE);
            //window.run("./ROMs/PONG.ch8");//keys 2,Q : Z,X
            //window.run("./ROMs/Blitz.ch8");
            //window.run("./ROMs/Hi-Lo.ch8");
            window.run("./ROMs/output");
            //window.run("./ROMs/ibm.ch8");
            //window.run("./ROMs/6-keypad.ch8");
            //window.run("./ROMs/5-quirks.ch8");            
            //window.run("./ROMs/4-flags.ch8");
            //window.run("./ROMs/3-corax+.ch8");
            //window.run("./ROMs/2-ibm-logo.ch8");
            //window.run("./ROMs/1-chip8-logo.ch8");
        }
        else {
            std::cerr << "Unable to determine the executable directory." << std::endl;
        }
    }
    else {
        std::cerr << "No command-line arguments provided." << std::endl;
    }

	
}