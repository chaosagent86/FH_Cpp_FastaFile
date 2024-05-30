#include "FASTA_Analysis.h"
#include "DNA.h"

DNA::~DNA() {
}

DNA::DNA(const std::string &iFilename) : FASTA_Analysis(iFilename) {

}

//int DNA::Calculate_GC_Content(const FASTA_Structure& fasta) {
void DNA::Calculate_GC_Content() {
    int gc = 0;
    int seq_length = 0;
    int gc_content = 0;

    for(auto & i : FASTA_Analysis::m_FASTA_Structure) {
        if (i.classification != "DNA")
            continue;
        std::cout << "*** New Header ***" << std::endl;
        std::cout << ">" << i.header << std::endl;
        gc = i.m_nucleotideCount['G'] + i.m_nucleotideCount['C'];
        seq_length = i.sequence.length();
        gc_content = gc*100/seq_length;
        std::cout << "GC Content: " << gc_content << " %" << std::endl;
    }
}

void DNA::Translate_into_protein_sequence() {
    std::cout << "function void Translate_into_protein_sequence() not yet implemented!" << std::endl;
}