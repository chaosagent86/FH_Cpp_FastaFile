#include <iostream> //standard
#include <fstream>  //file specific
#include <vector>


// https://stackoverflow.com/questions/35251635/fasta-reader-written-in-c

/*********************************************
-) Implementieren Sie ein nichttriviales objektorientiertes Datenmodell.  Wählen Sie aus einem der angefügten Beispiele.
-) Achten Sie darauf die Klassen vollständig zu implementieren: notwendige Konstruktoren und verwandte Funktionen, Getter, Setter und Vergleichsoperatoren.
-) Achten Sie, dass bei Parametern  unnötige Kopien vermieden werden.
-) Teilen Sie den Code in mehrere Kompiliereinheiten (.cpp) und Includefiles(.h) ein.
-) Wenn möglich, bauen Sie eine einfache Klassenhierarchie ein.
-) Wenn möglich, bauen Sie Ein-, Ausgabe in eine Datei ein.
-) Wenn möglich, implementieren Sie eine kleinen Algorithmus.
-) Wenn möglich, implmentieren Sie ein einfaches Errorhandling.
 */

struct FastaSequence {
    std::string header;
    std::string sequence;
};

void show_help(); //help text in case of error
std::vector<FastaSequence> readDataFile(const std::string& filename);

//******************************************************************
int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "\nError: Missing arguments!" << std::endl;
        show_help();
        return -1;
    }
    for (int i = 1; i < argc; i++) {
        if(std::string(argv[i]) == "--help") {
            show_help();
            return 0;
        }
        if(std::string(argv[i]) == "--file") {
            std::string filename = argv[i+1];
            std::vector<FastaSequence> sequences = readDataFile(filename);
            for (const auto& seq : sequences) {
                std::cout << "Header: " << seq.header << std::endl;
                std::cout << "Sequence: " << seq.sequence << std::endl;
            }
        }
        // show what was read in

    }
return 0;
}

//******************************************************************
std::vector<FastaSequence> readDataFile(const std::string& filename) {
    std::vector<FastaSequence> sequences;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "The file provided couldn't be opened: " << filename << std::endl;
        return sequences; // Return empty vector on error
    }

    std::string line;
    FastaSequence currentSeq;
    while (std::getline(file, line)) {
        if (line.empty())
            continue; // Skip empty lines

        if (line[0] == '>') { // New sequence header
            if (!currentSeq.header.empty()) {
                // Store previous sequence before starting a new one
                sequences.push_back(currentSeq);
                currentSeq.header.clear();
                currentSeq.sequence.clear();
            }
            currentSeq.header = line.substr(1); // Exclude '>'
        } else {
            // Sequence data
            currentSeq.sequence += line;
        }
    }
    // Store the last sequence
    if (!currentSeq.header.empty())
        sequences.push_back(currentSeq);

    file.close();
    return sequences;
}

//******************************************************************
//void open_file(std::string &i_filename)
//{
//    std::string line;
//    std::string id;
//    std::string sequence;
//
//    std::ifstream datafile;
//    datafile.open(i_filename);
//
//    if(datafile.is_open())
//    {
//        std::string line;
//        while (getline(datafile, line))
//        {
//            std::cout << "Line read: " << line << std::endl;
//        }
//    }
//    else
//    {
//        std::cerr << "The file provided couldn't be opened!" << std::endl;
//    }
//    datafile.close();
//}

//******************************************************************
void show_help()
{
    std::cout << "*************************************************************" << std::endl;
    std::cout << "--help \t\t\t shows this help" << std::endl;
    std::cout << "--file <filename> \t attach filename (no wildcards!)" << std::endl;
    std::cout << "*************************************************************" << std::endl  << std::endl;
}