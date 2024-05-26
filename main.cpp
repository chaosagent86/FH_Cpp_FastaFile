#include <iostream>
#include <fstream>

#include "FASTA_Analysis.h"
#include "DNA.h"

/*********************************************
-) Implementieren Sie ein nichttriviales objektorientiertes Datenmodell.  Wählen Sie aus einem der angefügten Beispiele.
-) Wenn möglich, bauen Sie eine Ausgabe in eine Datei ein.
-) Wenn möglich, implementieren Sie eine kleinen Algorithmus.
 ********************************************/

void show_help();

int main(int argc, char *argv[]) {

    std::string filename;
    bool arg_input_file = false;
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
        if(std::string(argv[i]) == "--output") { // not yet implemented
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

    DNA *obj_DNA;
    obj_DNA = new DNA(filename);

//    std::cout << "The following File Extension was detected : ";
//    std::string file_extension = obj_FASTA_Basics->getMFileExtension();
//    std::cout << file_extension << std::endl;
//
//    for(const auto& step : obj_FASTA_Basics->getMFastaStructure()) {
//        std::cout << "*********************************************************" << std::endl;
//        if(step.classification == "DNA") {
//            std::cout << "The Following sequence was classified as DNA" << std::endl;
//            std::cout << "Header: " << step.header << std::endl;
//            std::cout << "GC Content: " << obj_DNA->Calculate_GC_Content(step) << " %" << std::endl;
//        }
//        if(step.classification == "Protein") {
//            std::cout << "The Following sequence was classified as Protein" << std::endl;
//            std::cout << "Header: " << step.header << std::endl;
//        }
//        if(step.classification == "RNA") {
//            std::cout << "The Following sequence was classified as RNA" << std::endl;
//            std::cout << "Header: " << step.header << std::endl;
//        }
//
//    } // end for loop



    std::string file_extension = obj_FASTA_Basics->getMFileExtension();
    std::cout << "TEST:" << file_extension << std::endl;
    //Try to write an analysis file
    std::ofstream out_file;
    out_file.open(output_filename);
    if (!out_file.is_open()) {
        std::cerr << "The file couldn't be created: " << output_filename << std::endl;
        return -1;
    }
    out_file << "The following File Extension was detected: ";
    out_file << file_extension << std::endl;
//    out_file << "The Following sequence was classified as DNA" << std::endl;
    out_file.close();

    std::cout << "Little Helper for breakpoint!" << std::endl; // delete later
    delete obj_FASTA_Basics;
    delete obj_DNA;
    return 0;
}

//***********************************************************************

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
    std::cout << "--output <filename> \t\t\t In case of 'write_file_again please also prive output filename!"  << std::endl;
    std::cout << "*************************************************************" << std::endl  << std::endl;
}