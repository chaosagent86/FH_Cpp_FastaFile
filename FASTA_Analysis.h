#pragma once

#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <string>
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
        const bool get_evaluation_file_content_correct_or_not();
        std::vector<FASTA_Structure> readDataFile(const std::string& filename);
        std::unordered_map<std::string, char> readCodonTable();
        std::unordered_map<char, std::vector<std::string>> reverse_CodonTable();

        // setter
        void evaluate_sequence_FASTA_File();


    private:
        //getter - internal helper functions
        std::string getFileExtension(const std::string& filename);

        //setter - internal helper functions
        void initialize_m_nucleotideCount(int i);
        void set_m_nucleotideCount_Values();
        const bool ValidateIfFileContentMayBeCorrect() const;
        const std::string EvaluateIfDNAorProteinDetected() const;


    protected:
        std::string m_file_extension;
        std::vector<FASTA_Structure> m_FASTA_Structure;
        std::unordered_map<std::string, char> m_CodonTable;
        std::unordered_map<char, std::vector<std::string>> m_CodonTable_reverse;
};