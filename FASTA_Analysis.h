#include <iostream>
#include <map>
#include <vector>
#include <fstream>

struct FASTA_Structure {
    std::string header;
    std::string sequence;
    std::map<char, int> m_nucleotideCount;
    std::string classification = "not set";
};

class FASTA_Analysis {
    public:
        FASTA_Analysis() = delete;
        FASTA_Analysis(const std::string &i_filename);
        ~FASTA_Analysis();


        // getter
        void getFileExtensionText();

        // setter
        void evaluate_sequence_FASTA_File();




    private:
        std::vector<FASTA_Structure> m_FASTA_Structure;
        std::string m_file_extension;

        //getter - internal helper functions
        std::vector<FASTA_Structure> readDataFile(const std::string& filename);
        std::string getFileExtension(const std::string& filename);

        //setter - internal helper functions
        void initialize_m_nucleotideCount(int i);
        void set_m_nucleotideCount_Values();
};

