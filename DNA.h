#pragma once

#include "FASTA_Analysis.h"

class DNA : public FASTA_Analysis {
public:
    DNA(const std::string &iFilename);
    ~DNA();

    void Calculate_GC_Content();
};

