#include <iostream>

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

void show_help();

int main(int argc, char *argv[]) {

    std::string filename;

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
            if(i+1 < argc) {
                filename = argv[i+1]; // hier ein try-except einbauen!
            } else {
                std::cerr << "Missing argument after --file !" << std::endl;
            }
        }

    } // end for schleife
    std::cout << "Filename found: " << filename << std::endl;
    // Versuch eine Klasse einzubinden

    FASTA_Analysis *objBasics = new FASTA_Analysis(filename);

    return 0;
}

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