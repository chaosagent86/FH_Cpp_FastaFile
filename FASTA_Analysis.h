#include <iostream>
#include <map>

class FASTA_Analysis {

private:
    std::map<char, int> m_nucleotideCount;

    //setter - helper function for constructor!
    // for that reason its private, as it should only be run by constructor!
    static void initialize_nucleotideCount(std::map<char, int> &m_nucleotideCount);

public:
    FASTA_Analysis() = delete;
    FASTA_Analysis(const std::string &i_fasta_structure);
    ~FASTA_Analysis();
};

