#include "FASTA_Analysis.h"



FASTA_Analysis::FASTA_Analysis(const std::string &i_filename) {
    m_file_extension = getFileExtension(i_filename);
    getFileExtensionText();
    m_FASTA_Structure = readDataFile(i_filename);
    set_m_nucleotideCount_Values();
}

FASTA_Analysis::~FASTA_Analysis() = default;

void FASTA_Analysis::initialize_m_nucleotideCount(int i) {
    m_FASTA_Structure[i].m_nucleotideCount['A'] = 0; // DNA & Proteins (both)
    m_FASTA_Structure[i].m_nucleotideCount['B'] = 0; // DNA & Proteins (both)
    m_FASTA_Structure[i].m_nucleotideCount['C'] = 0; // DNA & Proteins (both)
    m_FASTA_Structure[i].m_nucleotideCount['D'] = 0; // DNA & Proteins (both)
    m_FASTA_Structure[i].m_nucleotideCount['E'] = 0; // ***** Proteins only!! *******
    m_FASTA_Structure[i].m_nucleotideCount['F'] = 0; // ***** Proteins only!! *******
    m_FASTA_Structure[i].m_nucleotideCount['G'] = 0; // DNA & Proteins (both)
    m_FASTA_Structure[i].m_nucleotideCount['H'] = 0; // DNA & Proteins (both)
    m_FASTA_Structure[i].m_nucleotideCount['I'] = 0; // ***** Proteins only!! *******
    m_FASTA_Structure[i].m_nucleotideCount['K'] = 0; // DNA & Proteins (both)
    m_FASTA_Structure[i].m_nucleotideCount['L'] = 0; // ***** Proteins only!! *******
    m_FASTA_Structure[i].m_nucleotideCount['M'] = 0; // DNA & Proteins (both)
    m_FASTA_Structure[i].m_nucleotideCount['N'] = 0; // DNA & Proteins (both)
    m_FASTA_Structure[i].m_nucleotideCount['P'] = 0; // ***** Proteins only!! *******
    m_FASTA_Structure[i].m_nucleotideCount['Q'] = 0; // ***** Proteins only!! *******
    m_FASTA_Structure[i].m_nucleotideCount['R'] = 0; // DNA & Proteins (both)
    m_FASTA_Structure[i].m_nucleotideCount['S'] = 0; // DNA & Proteins (both)
    m_FASTA_Structure[i].m_nucleotideCount['T'] = 0; // DNA & Proteins (both)
    m_FASTA_Structure[i].m_nucleotideCount['U'] = 0; // **** RNA only ****
    m_FASTA_Structure[i].m_nucleotideCount['V'] = 0; // DNA & Proteins (both)
    m_FASTA_Structure[i].m_nucleotideCount['W'] = 0; // DNA & Proteins (both)
    m_FASTA_Structure[i].m_nucleotideCount['X'] = 0; // ***** Proteins only!! *******
    m_FASTA_Structure[i].m_nucleotideCount['Y'] = 0; // DNA & Proteins (both)
    m_FASTA_Structure[i].m_nucleotideCount['Z'] = 0; //***** Proteins only!! *******
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
            currentSeq.sequence += line;
        }
    } // end while loop
    if (!currentSeq.header.empty()) {
        sequences.push_back(currentSeq);
    }

    file.close();
    return sequences;
}

std::string FASTA_Analysis::getFileExtension(const std::string& filename) {
    size_t pos = filename.find_last_of('.');
    if (pos != std::string::npos) {
        return filename.substr(pos + 1);
    }
    return ""; // No file extension found
}

void FASTA_Analysis::getFileExtensionText() {
    std::cout << "File Extension detected: " << m_file_extension << std::endl;
    if (m_file_extension == "fasta" || m_file_extension == "fas" || m_file_extension == "fa") {
        std::cout << "It's assumed that this file may contain all possible forms of acids" << std::endl;
    } else if (m_file_extension == "ffn") {
        std::cout << "Assumed to be used generically to specify nucleic acids." << std::endl;
    } else if (m_file_extension == "faa" || m_file_extension == "mpfa") {
        std::cout << "Assumed to contain (multiple) amino acid sequences." << std::endl;
    } else if (m_file_extension == "frn") {
        std::cout << "Assumed to contain non-coding RNA regions for a genome, e.g. tRNA, rRNA" << std::endl;
    }
}

void FASTA_Analysis::set_m_nucleotideCount_Values() {
    for (int i = 0; i < m_FASTA_Structure.size(); i++) {
        initialize_m_nucleotideCount(i);
        int character_to_test = 0;
        for(char nucleotide :  m_FASTA_Structure[i].sequence) {
            if(nucleotide == m_FASTA_Structure[i].sequence[character_to_test]) {
                m_FASTA_Structure[i].m_nucleotideCount[nucleotide]++;
            }
            character_to_test++;
        } // end for loop # counting
    } // end for loop
}

void FASTA_Analysis::evaluate_sequence_FASTA_file_QAD() {
    for (int i = 0; i < m_FASTA_Structure.size(); i++) {
        if(m_FASTA_Structure[i].m_nucleotideCount['U'] >= 1) {
            m_FASTA_Structure[i].RNA = true;
        } else if(m_FASTA_Structure[i].m_nucleotideCount['E'] >= 1 ||
                m_FASTA_Structure[i].m_nucleotideCount['F'] >= 1 ||
                m_FASTA_Structure[i].m_nucleotideCount['I'] >= 1 ||
                m_FASTA_Structure[i].m_nucleotideCount['L'] >= 1 ||
                m_FASTA_Structure[i].m_nucleotideCount['P'] >= 1 ||
                m_FASTA_Structure[i].m_nucleotideCount['Q'] >= 1 ||
                m_FASTA_Structure[i].m_nucleotideCount['X'] >= 1 ||
                m_FASTA_Structure[i].m_nucleotideCount['Z'] >= 1) {
            m_FASTA_Structure[i].Protein = true;
        } else if(!m_FASTA_Structure[i].DNA & !m_FASTA_Structure[i].DNA) {
            int ATGC = 0;
            ATGC = m_FASTA_Structure[i].m_nucleotideCount['A'] +
                   m_FASTA_Structure[i].m_nucleotideCount['C'] +
                   m_FASTA_Structure[i].m_nucleotideCount['G'] +
                   m_FASTA_Structure[i].m_nucleotideCount['T'];
            int sequence_length = 0;
            sequence_length = m_FASTA_Structure[i].sequence.length();
            if(sequence_length>=1) {
                if(ATGC/sequence_length > 0.6) // random threshhold - just to be extra safe
                    m_FASTA_Structure[i].DNA = true;
            } else {
                std::cout << "Couldn't figure out whether it's RNA, Protein or RNA";
            } // end else
        } // end if DNA
    } // end for loop
}

