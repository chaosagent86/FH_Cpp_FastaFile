#include <iostream>
#include <fstream>

#include "FASTA_Analysis.h"
#include "DNA.h"
#include "RNA.h"

void show_help();
void show_menu(bool DNA_expected = false, bool Protein_expected = false, bool RNA_expected = false);
void overview_about_data(FASTA_Analysis *obj_FASTA_Basics, DNA *obj_DNA);
void write_output(FASTA_Analysis *obj_FASTA_Basics, std::string &output_filename);

int main(int argc, char *argv[]) {

    std::cout << "\n";
    std::cout << "****************************************" << std::endl;
    std::cout << "** FASTA Analysis Platform v0.9      **" << std::endl;
    std::cout << "** Last Update: 2024-05-29           **" << std::endl;
    std::cout << "***************************************\n" << std::endl;


    std::string filename;
    bool arg_input_file = false;
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
                return -1;
            }
        }
        if(std::string(argv[i]) == "--output") { // not yet implemented
            if(i+1 < argc) {
                arg_output_file = true;
                output_filename = argv[i+1];
                std::cout << "parameter arg_show_me_everything recognised" << std::endl;
                std::cout << "Output filename: " << output_filename << std::endl;
            } else {
                std::cerr << "Missing argument after --output !" << std::endl;
                return -1;
            }
        }

    } // end of for loop
    if(!arg_input_file) {
        std::cerr << "There's a FASTA file necessary. Please provide argument '--file <filename>'!" << std::endl;
        return -1;
    }

    FASTA_Analysis *obj_FASTA_Basics;
    obj_FASTA_Basics = new FASTA_Analysis(filename);

    /* Filename on the very first view seems for me to be completely unnecessary,
     * but I did not understand how to manage it without 'filename' as parameter */
    DNA *obj_DNA;
    obj_DNA = new DNA(filename);

    RNA *obj_RNA;
    obj_RNA = new RNA(filename);

    bool result_evaluation;
    result_evaluation = obj_FASTA_Basics->get_evaluation_file_content_correct_or_not();
    if(!result_evaluation) {
        std::cerr << "Please evaluate if file content or file extension is correctly chosen!\n"
                     "The content of the file and the extension seem not to fit!" << std::endl;
        return -1;
    } else {
        obj_FASTA_Basics->getFileExtensionText();
    }

    bool DNA_expected = false;
    bool Protein_expected = false;
    bool RNA_expected = false;

    /* short evaluation of the data, which might be necessary for the menu
     * breaks automatically if there are at least sequences (not programmed but logically) and
     * everything (=DNA & Protein & RNA) was found. Thus, no further loops are necessary, even
     * if there are for example 99 sequences inside the file */
    for(const auto& step : obj_FASTA_Basics->getMFastaStructure()) {
        if (step.classification == "DNA") {
            DNA_expected = true;
            continue;
        }
        if (step.classification == "Protein") {
            Protein_expected = true;
            continue;
        }
        if (step.classification == "RNA") {
            RNA_expected = true;
            continue;
        }
        if(DNA_expected && Protein_expected && RNA_expected)
            break;
    }

    bool menu_should_run = true;
    char input = 0;

    std::string DNA_error_message = "You have chosen an inactive option (no DNA sequence available!) Please choose again!";
    std::string RNA_error_message = "You have chosen an inactive option (no RNA sequence available!) Please choose again!";

    while (menu_should_run) {
        std::cout << " ~ ~ ~ ~ ~ ~ ~ INPUT NEEDED ~ ~ ~ ~ ~ ~ ~ \n" << std::endl;
        show_menu(DNA_expected, Protein_expected, RNA_expected);
        std::cout << "\nYour Decision: ";
        std::cin >> input;
        std::cout << "\n ~ ~ ~ ~ ~ ~ ~ ~ OUTPUT ~ ~ ~ ~ ~ ~ ~ ~ \n\n";

        switch(input) {
            case '1':
                overview_about_data(obj_FASTA_Basics, obj_DNA);
                break;
            case '2':
                write_output(obj_FASTA_Basics, output_filename);
                break;
            case '3':
                if(DNA_expected) {
                    std::cout << "option " << input << " chosen - calc gc content" << std::endl;
                    obj_DNA->Calculate_GC_Content();
                    break;
                } else {
                    std::cerr << DNA_error_message << std::endl;
                    break;
                }
            case '4':
                if(DNA_expected) {
                    std::cout << "option " << input << " chosen - translate into protein sequence (first forward reading frame)" << std::endl;
                    obj_DNA->Translate_into_protein_sequence();
                    break;
                } else {
                    std::cerr << DNA_error_message << std::endl;
                    break;
                }
            case '5':
                if(RNA_expected) {
                    std::cout << "option " << input << " chosen - search for open reading frames" << std::endl;
                    obj_RNA->findORFs();
                    break;
                } else {
                    std::cerr << RNA_error_message << std::endl;
                    break;
                }
            case '9':
                menu_should_run = false;
                break;
            default:
                std::cerr << "\nUncovered menu point! Please choose again!" << std::endl;
        } // end of switch
    } // end of while loop

    std::cout << "Little Helper for breakpoint!" << std::endl; // delete later
    delete obj_FASTA_Basics;
    delete obj_DNA; //unnötig, weil vll. automatisch gelöscht wenn überklasse gelöscht wird?
    delete obj_RNA; //unnötig, weil vll. automatisch gelöscht wenn überklasse gelöscht wird?
    return 0;
}

//***********************************************************************

void show_menu(bool DNA_expected, bool Protein_expected, bool RNA_expected) {
    std::cout << "1\t - Show overview about data" << std::endl;
    std::cout << "2\t - Write output (same as in 1!)" << std::endl;
    if(DNA_expected) {
        std::cout << "3\t - Calculate GC-Content for each DNA-Sequence (everything else is ignored)" << std::endl;
        std::cout << "4\t - NOT IMPLEMENTED YET - Translate DNA Sequence into Protein Sequence (first forward reading frame)" << std::endl;
    } else {
        std::cout << "3\t - [inactive!] Calculate GC-Content for each DNA-Sequence (everything else is ignored)" << std::endl;
        std::cout << "4\t - [inactive!] NOT IMPLEMENTED YET - Translate DNA Sequence into Protein Sequence (first forward reading frame)" << std::endl;
    }
    if(RNA_expected)  {
        std::cout << "5\t - Search for open reading frames" << std::endl;
    } else {
        std::cout << "5\t - [inactive!] Search for open reading frames" << std::endl;
    }
    std::cout << "99\t - End program" << std::endl;
}
//***********************************************************************

void overview_about_data(FASTA_Analysis *obj_FASTA_Basics, DNA *obj_DNA) {
    std::cout << "The following File Extension was detected : ";
    std::string file_extension = obj_FASTA_Basics->getMFileExtension();
    std::cout << file_extension << std::endl;

    for(const auto& step : obj_FASTA_Basics->getMFastaStructure()) {
        if(step.classification == "DNA") {
            std::cout << "The Following sequence was classified as DNA" << std::endl;
            std::cout << "Header: " << step.header << std::endl;
            std::cout << "To Calculate GC Content, please choose option in menu" << std::endl;
        }
        if(step.classification == "Protein") {
            std::cout << "The Following sequence was classified as Protein" << std::endl;
            std::cout << "Header: " << step.header << std::endl;
        }
        if(step.classification == "RNA") {
            std::cout << "The Following sequence was classified as RNA" << std::endl;
            std::cout << "Header: " << step.header << std::endl;
        }

    }
}
//***********************************************************************

void show_help() {
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

void write_output(FASTA_Analysis *obj_FASTA_Basics, std::string &output_filename) {


    std::cout << "nothing happening so far as it is throwing an strange exception!" << std::endl;
    //        std::cout << "TEST:" << file_extension << std::endl;
//        //Try to write an analysis file
//        std::ofstream out_file;
//        out_file.open(output_filename);
//        if (!out_file.is_open()) {
//            std::cerr << "The file couldn't be created: " << output_filename << std::endl;
//            return -1;
//        }
//        out_file << "The following File Extension was detected: ";
//        out_file << file_extension << std::endl; // throws exception "concurrence_unlock_error" (zumindest vermutlich - laut inhalt von txt datei)
//        out_file << "The Following sequence was classified as DNA" << std::endl;
//
//        for(const auto& step : obj_FASTA_Basics->getMFastaStructure()) {
//            std::cout << "*********************************************************" << std::endl;
//            if(step.classification == "DNA") {
//                out_file << "The Following sequence was classified as DNA" << std::endl;
//                out_file << "Header: " << step.header << std::endl;
//                out_file << "GC Content: " << obj_DNA->Calculate_GC_Content(step) << " %" << std::endl;
//            }
//            if(step.classification == "Protein") {
//                out_file << "The Following sequence was classified as Protein" << std::endl;
//                out_file << "Header: " << step.header << std::endl;
//            }
//            if(step.classification == "RNA") {
//                out_file << "The Following sequence was classified as RNA" << std::endl;
//                out_file << "Header: " << step.header << std::endl;
//            }
//
//        } // end for loop
//
//        out_file.close();
}