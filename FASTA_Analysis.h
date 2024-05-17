#include <iostream>
#include <map>
#include <vector>
#include <fstream>

struct FASTA_Structure {
    std::string header;
    std::string sequence;
};

class FASTA_Analysis {
    public:
        FASTA_Analysis() = delete;
        FASTA_Analysis(const std::string &i_filename);
        ~FASTA_Analysis();

        void const getFileExtensionText(const std::string &fileExtension);
        std::vector<FASTA_Structure> readDataFile(const std::string& filename);

    private:
        std::map<char, int> m_nucleotideCount;
        std::string header;
        std::string sequence;
        std::string m_file_extension;
        bool protein_TF_QAD; // True/False - Quick and Dirty
        bool protein_TF_inDetail; // True/False - in Detail analysis
        bool DNA_TF_QAD; // True/False - Quick and Dirty
        bool DNA_TF_inDetail; // True/False - in Detail analysis

        //setter
        // for that reason its private, as it should only be run by constructor!
        static void initialize_nucleotideCount(std::map<char, int> &m_nucleotideCount);

        // getter
        static std::string getFileExtension(const std::string& filename);
};

