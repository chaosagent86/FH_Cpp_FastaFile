#include <iostream>
#include <map>
#include <vector>
#include <fstream>

struct FASTA_Structure {
    std::string header;
    std::string sequence;
    std::map<char, int> m_nucleotideCount;
    bool PROTEIN_quick_and_dirty;
    bool RNA_quick_and_dirty;
    bool DNA_sure;
};

class FASTA_Analysis {
    public:
        FASTA_Analysis() = delete;
        FASTA_Analysis(const std::string &i_filename);
        ~FASTA_Analysis();


        // getter
        static void getFileExtensionText();
        static std::vector<FASTA_Structure> readDataFile(const std::string& filename);
        bool validateFileExtension();
        static std::string getFileExtension(const std::string& filename);

        // setter
        void evaluate_sequence_FASTA_file_QAD();
        void set_m_nucleotideCount(int i);

    private:
        std::vector<FASTA_Structure> m_FASTA_Structure;
        static std::string m_file_extension;
};

