#include "FASTA_Analysis.h"

FASTA_Analysis::FASTA_Analysis(const std::string &i_fasta_structure) {
    initialize_nucleotideCount(m_nucleotideCount);
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