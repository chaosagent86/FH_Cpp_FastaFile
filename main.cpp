#include <iostream>
#include <fstream>

// https://stackoverflow.com/questions/35251635/fasta-reader-written-in-c


//using namespace std;

/*********************************************
 * ToDO: Argumente erstellen um FASTA File einlesen zu können
 * ToDO: Hilfetext als Argument erstellen --help
 * ToDO: Liste hinterlegen, was spezifisch für DNA Sequenzen ist
 * ToDO: Liste hinterlegen, was spezifisch für Protein Sequenzen ist
 * ToDO: Liste hinterlegen, was bei DNA und bei Protein-Sequenzen vorkommen kann
 * ToDO: Sequenzen einzeln hinterlegen, auch wenn diverse Sequenzen eingelesen werden
 * @return
 */

void help(); //help text in case of error

// not yet implemented
std::string open_file(std::string &filename);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Error: Missing arguments!" << std::endl;
        help();
        return -1;
    }

    // only for testing purposes
    for (int i = 1; i < argc; i++) {
        std::cout << "Argument " << i << ": " << argv[i] << std::endl;
    }

    for (int i = 1; i < argc; i++) {
        if(std::string(argv[i]) == "--help") {
            help();
            return 0;
        }
        if(std::string(argv[i]) == "--file") {
            std::string filename = argv[i+1];
            open_file(filename);
        }


    }

return 0;
} // temporary end of Main!!


std::string open_file(std::string &filename)
{
    std::cout << "open_file(std::string &filename):" << std::endl;
    std::cout << "\tat least theoretically the file '" << filename << "' was opened :-)" << std::endl;
    return "done";
}

void help()
{
    std::cout << "*************************************************************" << std::endl;
    std::cout << "--help \t\t shows help" << std::endl;
    std::cout << "--file <filename> \t attach filename (no wildcards!)" << std::endl;
    std::cout << "*************************************************************" << std::endl  << std::endl;
}