#include <iostream>

#include "FASTA_Analysis.h"

/*********************************************
-) Implementieren Sie ein nichttriviales objektorientiertes Datenmodell.  Wählen Sie aus einem der angefügten Beispiele.
-) Wenn möglich, bauen Sie eine einfache Klassenhierarchie ein.
-) Wenn möglich, bauen Sie eine Ausgabe in eine Datei ein.
-) Wenn möglich, implementieren Sie eine kleinen Algorithmus.
 */

void show_help();
void show_initial_text();

int main(int argc, char *argv[]) {
    //show_initial_text();

    std::string filename;
    bool arg_input_file = false;
    bool arg_show_me_everything = false;
    bool arg_Sequence_in_Depth = false;
    bool arg_Sequence_Quick_and_Dirty = false;
    bool arg_Show_fancy_histogram = false;
    bool arg_output_file = false;
    std::string output_filename;

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
                filename = argv[i+1];
                arg_input_file = true;
            } else {
                std::cerr << "Missing argument after --file !" << std::endl;
            }
        }
        if(std::string(argv[i]) == "--show_me_everything") { // not yet implemented
            arg_show_me_everything = true;
            std::cout << "parameter --show_me_everything recognised" << std::endl;
        }
        if(std::string(argv[i]) == "--sequence_quick_and_dirty") { // not yet implemented
            arg_Sequence_Quick_and_Dirty = true;
            std::cout << "parameter --sequence_quick_and_dirty recognised" << std::endl;
        }
        if(std::string(argv[i]) == "--Sequence_in_Depth") { // not yet implemented
            arg_Sequence_in_Depth = true;
            std::cout << "parameter --Sequence_in_Depth recognised" << std::endl;
        }
        if(std::string(argv[i]) == "--show_histogram") { // not yet implemented
            arg_Show_fancy_histogram = true;
            std::cout << "parameter --show_histogram recognised" << std::endl;
        }
        if(std::string(argv[i]) == "--output") { // not yet implemented
            arg_output_file  = true;
            if(i+1 < argc) {
                output_filename = argv[i+1];
                std::cout << "parameter arg_show_me_everything recognised" << std::endl;
                std::cout << "Output filename: " << output_filename << std::endl;
            } else {
                std::cerr << "Missing argument after --output !" << std::endl;
            }
        }

    } // end of for loop
    if(!arg_input_file) {
        std::cerr << "There's a FASTA file necessary. Please provide argument '--file <filename>'!" << std::endl;
        return -1;
    }

    FASTA_Analysis *obj_FASTA_Basics;
    obj_FASTA_Basics = new FASTA_Analysis(filename);



    delete obj_FASTA_Basics;
    return 0;
}

void show_initial_text() {
    std::cout << "************************************************************************" << std::endl;
    std::cout << "** FASTA-File Analysis Kit Pre Alpha :)                               **" << std::endl;
    std::cout << "** Intended to work completely automatically based on your arguments! **" << std::endl;
    std::cout << "************************************************************************\n" << std::endl;
}

void show_help()
{
    std::cout << "*************************************************************" << std::endl;
    std::cout << "--help \t\t\t shows this help" << std::endl;
    std::cout << "--file <filename> \t attach filename to be analysed (no wildcards!)" << std::endl;
    std::cout << "\t\tAllowed file extensions:" << std::endl;
    std::cout << "\t\t\t-) *.fasta / *.fas *.fa (detection possible what's inside!)" << std::endl;
    std::cout << "\t\t\t-) *.ffn (nucleic acids supposed)" << std::endl;
    std::cout << "\t\t\t-) *.faa / *.mpfa (amino acids supposed)" << std::endl;
    std::cout << "\t\t\t-) *.frn (ribosomic nucleic acids supposed)" << std::endl;
    std::cout << "--show_me_everything \t\t\t just do EVERYTHING (!) which seems possible (or at least is implemented)" << std::endl;
    std::cout << "--Sequence_Quick_and_Dirty \t\t\t fastest possible way to evaulate if it's DNA/Protein/RNA" << std::endl;
    std::cout << "--Sequence_in_Depth \t\t\t Do an in-Depth Analysis of the DNA" << std::endl;
    std::cout << "--output <filename> \t\t\t In case of 'write_file_again please also prive output filename!"  << std::endl;
    std::cout << "--show_histogram \t\t\t Provide (information) about histogram" << std::endl;
    std::cout << "*************************************************************" << std::endl  << std::endl;
}