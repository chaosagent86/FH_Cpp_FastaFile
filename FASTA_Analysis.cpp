#include "FASTA_Analysis.h"



FASTA_Analysis::FASTA_Analysis(const std::string &i_filename) {
    initialize_nucleotideCount(m_nucleotideCount);
    m_file_extension = getFileExtension(i_filename);
    getFileExtensionText(m_file_extension);

}

void FASTA_Analysis::initialize_nucleotideCount(std::map<char, int> &m_nucleotideCount) {
    m_nucleotideCount['A'] = 0; // DNA & Proteins (both)
    m_nucleotideCount['B'] = 0; // DNA & Proteins (both)
    m_nucleotideCount['C'] = 0; // DNA & Proteins (both)
    m_nucleotideCount['D'] = 0; // DNA & Proteins (both)
    m_nucleotideCount['E'] = 0; // ***** Proteins only!! *******
    m_nucleotideCount['F'] = 0; // ***** Proteins only!! *******
    m_nucleotideCount['G'] = 0; // DNA & Proteins (both)
    m_nucleotideCount['H'] = 0; // DNA & Proteins (both)
    m_nucleotideCount['I'] = 0; // ***** Proteins only!! *******
    m_nucleotideCount['K'] = 0; // DNA & Proteins (both)
    m_nucleotideCount['L'] = 0; // ***** Proteins only!! *******
    m_nucleotideCount['M'] = 0; // DNA & Proteins (both)
    m_nucleotideCount['N'] = 0; // DNA & Proteins (both)
    m_nucleotideCount['P'] = 0; // ***** Proteins only!! *******
    m_nucleotideCount['Q'] = 0; // ***** Proteins only!! *******
    m_nucleotideCount['R'] = 0; // DNA & Proteins (both)
    m_nucleotideCount['S'] = 0; // DNA & Proteins (both)
    m_nucleotideCount['T'] = 0; // DNA & Proteins (both)
    m_nucleotideCount['U'] = 0; // **** RNA only ****
    m_nucleotideCount['V'] = 0; // DNA & Proteins (both)
    m_nucleotideCount['W'] = 0; // DNA & Proteins (both)
    m_nucleotideCount['X'] = 0; // ***** Proteins only!! *******
    m_nucleotideCount['Y'] = 0; // DNA & Proteins (both)
    m_nucleotideCount['Z'] = 0; //***** Proteins only!! *******
}

std::vector<FASTA_Structure> FASTA_Analysis::readDataFile(const std::string& filename) {
    std::vector<FASTA_Structure> sequences;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "The file provided couldn't be opened: " << filename << std::endl;
        return sequences; // Return empty vector on error
    }

    std::string line;
    FASTA_Structure currentSeq;
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

std::string FASTA_Analysis::getFileExtension(const std::string& filename) {
    size_t pos = filename.find_last_of('.');
    if (pos != std::string::npos) {
        return filename.substr(pos + 1);
    }
    return ""; // Keine Dateiendung gefunden
}

void const FASTA_Analysis::getFileExtensionText(const std::string &fileExtension) {
    if (fileExtension == "fasta" || fileExtension == "fas" || fileExtension == "fa") {
        std::cout << "File Extension detected: " << fileExtension << std::endl;
        std::cout << "The following File extensions are generally considered\n"
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