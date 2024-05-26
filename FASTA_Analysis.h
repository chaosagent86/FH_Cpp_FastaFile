#pragma once

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
        FASTA_Analysis(const std::string &i_filename);
        ~FASTA_Analysis();

        // getter
        void getFileExtensionText();
        const std::vector<FASTA_Structure> &getMFastaStructure() const;
        const std::string &getMFileExtension() const;

        // setter
        void evaluate_sequence_FASTA_File();


    private:

        std::string m_file_extension;

    //getter - internal helper functions
        std::vector<FASTA_Structure> readDataFile(const std::string& filename);
        std::string getFileExtension(const std::string& filename);

        //setter - internal helper functions
        void initialize_m_nucleotideCount(int i);
        void set_m_nucleotideCount_Values();
        const bool ValidateIfFileContentMayBeCorrect() const;
        const std::string EvaluateIfDNAorProteinDetected() const;

protected:
    std::vector<FASTA_Structure> m_FASTA_Structure;
};

