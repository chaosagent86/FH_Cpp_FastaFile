#include "RNA.h"

RNA::~RNA() {
    std::cout << "Destructor destroyed at least something :-)" << std::endl;
}

RNA::RNA(const std::string &iFilename) : FASTA_Analysis(iFilename) {
    ;
}

bool RNA::isStopCodon(const std::string& codon) {
    return codon == "UAG" || codon == "UGA" || codon == "UAA";
}

void RNA::findORFs() {
    size_t seq_length = 0;
    std::vector<std::string> orfs;

    for (auto & step : FASTA_Analysis::m_FASTA_Structure) {
        if (step.classification != "RNA")
            continue;
        std::cout << "*** New Header ***" << std::endl;
        std::cout << ">" << step.header << std::endl;
        seq_length = step.sequence.length();
        for (size_t i = 0; i < seq_length - 2; i++) {
            if (step.sequence.substr(i, 3) == "AUG") {
                for (size_t j = i + 3; j < seq_length - 2; j += 3) {
                    std::string codon =step.sequence.substr(j, 3);
                    if (isStopCodon(codon)) {
                        std::cout << step.sequence.substr(i, j - i + 3) << std::endl;
                        //orfs.push_back(m_FASTA_Structure[i].sequence.substr(i, j - i + 3));
                        break;
                    }
                }
            }
        }
//        for (const std::string& orf : orfs) {
//            std::cout << orf << std::endl;
//        }
    }

}