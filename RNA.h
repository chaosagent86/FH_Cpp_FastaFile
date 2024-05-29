#pragma once

#include <iostream>
#include <vector>

#include "FASTA_Analysis.h"

class RNA : public FASTA_Analysis {
public:
    RNA(const std::string &iFilename);
    ~RNA();
    void findORFs();

private:
    bool isStopCodon(const std::string& codon);
};
