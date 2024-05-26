#pragma once

#include "FASTA_Analysis.h"

class DNA : public FASTA_Analysis {
public:
    DNA(const std::string &iFilename);
    ~DNA();

    int Calculate_GC_Content(const FASTA_Structure& fasta);
};

