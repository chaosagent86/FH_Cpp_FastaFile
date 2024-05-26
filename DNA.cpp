#include "FASTA_Analysis.h"
#include "DNA.h"

DNA::~DNA() {
    std::cout << "Destructor destroyed at least something :-)" << std::endl;
}

DNA::DNA(const std::string &iFilename) : FASTA_Analysis(iFilename) {
    ;
}

int DNA::Calculate_GC_Content(const FASTA_Structure& fasta) {
    int gc_content = 0;
    int gc_total_bases = 0;

    gc_total_bases = fasta.m_nucleotideCount.at('G') + fasta.m_nucleotideCount.at('C');
    int seq_length = fasta.sequence.length();

    gc_content = gc_total_bases*100/seq_length;

    return gc_content;
}

