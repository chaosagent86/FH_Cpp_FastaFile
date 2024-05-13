#include <iostream> //standard
#include <vector>
#include <fstream>
#include <filesystem>

#include "FASTA_Analysis.h"

/*********************************************
-) Implementieren Sie ein nichttriviales objektorientiertes Datenmodell.  Wählen Sie aus einem der angefügten Beispiele.
-) Achten Sie darauf die Klassen vollständig zu implementieren: notwendige Konstruktoren und verwandte Funktionen, Getter, Setter und Vergleichsoperatoren.
-) Achten Sie, dass bei Parametern  unnötige Kopien vermieden werden.
-) Teilen Sie den Code in mehrere Kompilier-Einheiten (.cpp) und Include-Files(.h) ein.
-) Wenn möglich, bauen Sie eine einfache Klassenhierarchie ein.
-) Wenn möglich, bauen Sie Ein-, Ausgabe in eine Datei ein.
-) Wenn möglich, implementieren Sie eine kleinen Algorithmus.
-) Wenn möglich, implementeren Sie ein einfaches Errorhandling.
 */

struct FastaSequence {
    std::string header;
    std::string sequence;
};

void show_help();
std::vector<FastaSequence> readDataFile(const std::string& filename);
std::string getFileExtension(const std::string& filename);
void const showFileExtensionText(const std::string &fileExtension);

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

            std::cout << "Filename: " << filename << std::endl;
            std::string fileExtension = getFileExtension(filename);
            std::cout << "File Extension detected: " << fileExtension << std::endl;

            if (fileExtension == "fasta" || fileExtension == "fas" || fileExtension == "fa") {
                showFileExtensionText(fileExtension);
            } else if (fileExtension == "ffn") {
                showFileExtensionText(fileExtension);
            } else if (fileExtension == "faa" || fileExtension == "mpfa") {
                showFileExtensionText(fileExtension);
            } else if (fileExtension == "frn") {
                showFileExtensionText(fileExtension);
            } else {
                std::cerr << "File extension not supported!" << std::endl;
                show_help();
                return -1;
            }
//            std::vector<FastaSequence> sequences = readDataFile(filename);
//            for (const auto& seq : sequences) {
//                std::cout << "Header: " << seq.header << std::endl;
//                std::cout << "Sequence: " << seq.sequence << std::endl;
        } // end if-statement
    } // end for schleife
    return 0;
}

//******************************************************************
std::string getFileExtension(const std::string& filename) {
    size_t pos = filename.find_last_of('.');
    if (pos != std::string::npos) {
        return filename.substr(pos + 1);
    }
    return ""; // Keine Dateiendung gefunden
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
void show_help()
{
    std::cout << "*************************************************************" << std::endl;
    std::cout << "--help \t\t\t shows this help" << std::endl;
    std::cout << "--file <filename> \t attach filename (no wildcards!)" << std::endl;
    std::cout << "\t\tAllowed file extensions:" << std::endl;
    std::cout << "\t\t\t-) *.fasta / *.fas *.fa (detection possible what's inside!)" << std::endl;
    std::cout << "\t\t\t-) *.ffn (nucleic acids supposed)" << std::endl;
    std::cout << "\t\t\t-) *.faa / *.mpfa (amino acids supposed)" << std::endl;
    std::cout << "\t\t\t-) *.frn (ribosomic nucleic acids supposed)" << std::endl;
    std::cout << "*************************************************************" << std::endl  << std::endl;
}

//******************************************************************
void const showFileExtensionText(const std::string &fileExtension) {
    if (fileExtension == "fasta" || fileExtension == "fas" || fileExtension == "fa") {
        std::cout << "File Extension detected: " << fileExtension << std::endl;
        std::cout << "The following File extensions are generally considered to contain all possible\n"
                     "to contain all possible forms of acids: *.fasta / *.fas / *.fa\n"
                     "including nucleic acids, amino acids, non coding RNAs"  << std::endl;
    } else if (fileExtension == "ffn") {
        std::cout << "File Extension detected: " << fileExtension << std::endl;
        std::cout << "Assumed to be used generically to specify nucleic acids" << std::endl;
    } else if (fileExtension == "faa" || fileExtension == "mpfa") {
        std::cout << "File Extension detected: " << fileExtension << std::endl;
        std::cout << "Assumed to contain (multiple) amino acid sequences" << std::endl;
    } else if (fileExtension == "frn") {
        std::cout << "File Extension detected: " << fileExtension << std::endl;
        std::cout << "Assumed to contain non-coding RNA regions for a genome,\n"
                     "e.g. tRNA, rRNA | File extensions: *.frn" << std::endl;
    }
}