#include "FASTA_Analysis.h"



FASTA_Analysis::FASTA_Analysis(const std::string &i_FASTA_filename) {
    m_file_extension = getFileExtension(i_FASTA_filename);
    m_FASTA_Structure = readDataFile(i_FASTA_filename);
    set_m_nucleotideCount_Values();
    evaluate_sequence_FASTA_File();
    /* Dieser Teil unterhalb funktioniert wunderbar im Debug-Modus - aber aus mir nicht erfindlichen Gründen NICHT
     * wenn er 'regulär' ausgeführt wird - hier endet die Ausführung dann automatisch nach erscheinen der
     * Startmeldung mit 'FASTA Analysis Tool etc.'
     * Es erscheint kein Menü oder dergleichen
     * Ich konnte beim Debuggen auch keinerlei Fehler oder ähnliches erkennen.
     * Das Problem scheint beim Einlesen der readCodonTable() zu liegen
     * Aber das funktioniert ja beim Debuggen.....
     * Auch der Inhalt der Variablen scheint zu passen nachdem die beiden unteren Funktionen durchgelaufen sind
     * m_CodonTable = readCodonTable();
     * m_CodonTable_reverse = reverse_CodonTable();
     * ************************/

//    m_CodonTable = readCodonTable();
//    std::cout << "m_CodonTable created" << std::endl;
//    m_CodonTable_reverse = reverse_CodonTable();
//    std::cout << "m_CodonTable_reverse created" << std::endl;
}

FASTA_Analysis::~FASTA_Analysis() = default;

std::unordered_map<std::string, char> FASTA_Analysis::readCodonTable() {
    std::string map_filename = "..\\mapping_DNA_Protein.txt";
    std::string codon;
    char aminoAcid;
    std::unordered_map<std::string, char> codonTable;
    std::ifstream file(map_filename);
    if(!file.is_open()) {
        std::cerr << "Could not open mapping file!" << std::endl;
    }
    while (file >> codon >> aminoAcid) {
        codonTable[codon] = aminoAcid;
    }
    file.close();

    return codonTable;
}

std::unordered_map<char, std::vector<std::string>> FASTA_Analysis::reverse_CodonTable() {
    std::unordered_map<char, std::vector<std::string>> reverseCodonTable;
    for (const auto& pair : m_CodonTable) {
        reverseCodonTable[pair.second].push_back(pair.first);
    }
    return reverseCodonTable;
}

const bool FASTA_Analysis::get_evaluation_file_content_correct_or_not() {
    set_m_nucleotideCount_Values();
    evaluate_sequence_FASTA_File();
    if(!ValidateIfFileContentMayBeCorrect()) {
        return false;
    }
    return true;
}


void FASTA_Analysis::initialize_m_nucleotideCount(int i) {
    m_FASTA_Structure[i].m_nucleotideCount['A'] = 0; // DNA & Proteins (both)
    m_FASTA_Structure[i].m_nucleotideCount['B'] = 0; // DNA & Proteins (both)
    m_FASTA_Structure[i].m_nucleotideCount['C'] = 0; // DNA & Proteins (both)
    m_FASTA_Structure[i].m_nucleotideCount['D'] = 0; // DNA & Proteins (both)
    m_FASTA_Structure[i].m_nucleotideCount['E'] = 0; // ***** Proteins only!! *******
    m_FASTA_Structure[i].m_nucleotideCount['F'] = 0; // ***** Proteins only!! *******
    m_FASTA_Structure[i].m_nucleotideCount['G'] = 0; // DNA & Proteins (both)
    m_FASTA_Structure[i].m_nucleotideCount['H'] = 0; // DNA & Proteins (both)
    m_FASTA_Structure[i].m_nucleotideCount['I'] = 0; // ***** Proteins only!! *******
    m_FASTA_Structure[i].m_nucleotideCount['K'] = 0; // DNA & Proteins (both)
    m_FASTA_Structure[i].m_nucleotideCount['L'] = 0; // ***** Proteins only!! *******
    m_FASTA_Structure[i].m_nucleotideCount['M'] = 0; // DNA & Proteins (both)
    m_FASTA_Structure[i].m_nucleotideCount['N'] = 0; // DNA & Proteins (both)
    m_FASTA_Structure[i].m_nucleotideCount['P'] = 0; // ***** Proteins only!! *******
    m_FASTA_Structure[i].m_nucleotideCount['Q'] = 0; // ***** Proteins only!! *******
    m_FASTA_Structure[i].m_nucleotideCount['R'] = 0; // DNA & Proteins (both)
    m_FASTA_Structure[i].m_nucleotideCount['S'] = 0; // DNA & Proteins (both)
    m_FASTA_Structure[i].m_nucleotideCount['T'] = 0; // DNA & Proteins (both)
    m_FASTA_Structure[i].m_nucleotideCount['U'] = 0; // **** RNA only ****
    m_FASTA_Structure[i].m_nucleotideCount['V'] = 0; // DNA & Proteins (both)
    m_FASTA_Structure[i].m_nucleotideCount['W'] = 0; // DNA & Proteins (both)
    m_FASTA_Structure[i].m_nucleotideCount['X'] = 0; // ***** Proteins only!! *******
    m_FASTA_Structure[i].m_nucleotideCount['Y'] = 0; // DNA & Proteins (both)
    m_FASTA_Structure[i].m_nucleotideCount['Z'] = 0; //***** Proteins only!! *******
}

std::vector<FASTA_Structure> FASTA_Analysis::readDataFile(const std::string& filename) {
    std::vector<FASTA_Structure> sequences;
    std::ifstream in_file(filename);
    if (!in_file.is_open()) {
        std::cerr << "The file provided couldn't be opened: " << filename << std::endl;
        return sequences; // Return empty vector on error
    }

    std::string line;
    FASTA_Structure currentSeq;
    while (std::getline(in_file, line)) {
        if (line.empty())
            continue; // Skip empty lines

        if (line[0] == '>') { // New sequence header
            if (!currentSeq.header.empty()) {
                // Store previous sequence before starting a new one
                sequences.push_back(currentSeq);
                currentSeq.header.clear();
                currentSeq.sequence.clear();
            }
            currentSeq.header = line.substr(1); // Exclude '>'
        } else {
            currentSeq.sequence += line;
        }
    } // end while loop
    if (!currentSeq.header.empty()) {
        sequences.push_back(currentSeq);
    }

    in_file.close();
    return sequences;
}

std::string FASTA_Analysis::getFileExtension(const std::string& filename) {
    size_t pos = filename.find_last_of('.');
    if (pos != std::string::npos) {
        return filename.substr(pos + 1);
    }
    return ""; // No file extension found
}

void FASTA_Analysis::getFileExtensionText() {
    std::cout << "File Extension detected: " << m_file_extension << std::endl;
    if (m_file_extension == "fasta" || m_file_extension == "fas" || m_file_extension == "fa") {
        std::cout << "It's assumed that this file may contain all possible forms of acids" << std::endl;
    } else if (m_file_extension == "ffn") {
        std::cout << "Assumed to be used generically to specify nucleic acids." << std::endl;
    } else if (m_file_extension == "faa" || m_file_extension == "mpfa") {
        std::cout << "Assumed to contain (multiple) amino acid sequences." << std::endl;
    } else if (m_file_extension == "frn") {
        std::cout << "Assumed to contain non-coding RNA regions for a genome, e.g. tRNA, rRNA" << std::endl;
    }
}

void FASTA_Analysis::set_m_nucleotideCount_Values() {
    for (int i = 0; i < m_FASTA_Structure.size(); i++) {
        initialize_m_nucleotideCount(i);
        int character_to_test = 0;
        for(char nucleotide :  m_FASTA_Structure[i].sequence) {
            if(nucleotide == m_FASTA_Structure[i].sequence[character_to_test]) {
                m_FASTA_Structure[i].m_nucleotideCount[nucleotide]++;
            }
            character_to_test++;
        } // end for loop # counting
    } // end for loop
}

void FASTA_Analysis::evaluate_sequence_FASTA_File() {
    for (int i = 0; i < m_FASTA_Structure.size(); i++) {
        if(m_FASTA_Structure[i].m_nucleotideCount['U'] >= 1) {
            m_FASTA_Structure[i].classification = "RNA";
        } else if(m_FASTA_Structure[i].m_nucleotideCount['E'] >= 1 ||
                m_FASTA_Structure[i].m_nucleotideCount['F'] >= 1 ||
                m_FASTA_Structure[i].m_nucleotideCount['I'] >= 1 ||
                m_FASTA_Structure[i].m_nucleotideCount['L'] >= 1 ||
                m_FASTA_Structure[i].m_nucleotideCount['P'] >= 1 ||
                m_FASTA_Structure[i].m_nucleotideCount['Q'] >= 1 ||
                m_FASTA_Structure[i].m_nucleotideCount['X'] >= 1 ||
                m_FASTA_Structure[i].m_nucleotideCount['Z'] >= 1) {
            m_FASTA_Structure[i].classification = "Protein";
        } else if(m_FASTA_Structure[i].classification != "RNA" & m_FASTA_Structure[i].classification != "Protein") {
            int ATGC = 0;
            ATGC = m_FASTA_Structure[i].m_nucleotideCount['A'] +
                   m_FASTA_Structure[i].m_nucleotideCount['C'] +
                   m_FASTA_Structure[i].m_nucleotideCount['G'] +
                   m_FASTA_Structure[i].m_nucleotideCount['T'];
            int sequence_length = 0;
            sequence_length = m_FASTA_Structure[i].sequence.length();
            if(sequence_length>=1) {
                if(ATGC/sequence_length > 0.6) // random threshhold - just to be extra safe
                    m_FASTA_Structure[i].classification = "DNA";
            } else {
                std::cout << "Couldn't figure out whether it's RNA, Protein or RNA";
                m_FASTA_Structure[i].classification = "error - unable to set";
            } // end else
        } // end if DNA
    } // end for loop
}

const std::vector<FASTA_Structure> &FASTA_Analysis::getMFastaStructure() const {
    return m_FASTA_Structure;
}

const std::string &FASTA_Analysis::getMFileExtension() const {
    return m_file_extension;
}

const bool FASTA_Analysis::ValidateIfFileContentMayBeCorrect() const {
    std::string Content;
    Content = EvaluateIfDNAorProteinDetected();

    if (m_file_extension == "fasta" || m_file_extension == "fas" || m_file_extension == "fa") {
        return true; // may contain just everything - thus - always true
    } else if (m_file_extension == "ffn") {
        if(Content == "DNA")
            return true;
        else
            return false;
    } else if (m_file_extension == "faa" || m_file_extension == "mpfa") {
        if(Content == "Protein")
            return true;
        else
            return false;
    } else if (m_file_extension == "frn") {
        if(Content == "RNA")
            return true;
        else
            return false;
    }
    return false;
}

const std::string FASTA_Analysis::EvaluateIfDNAorProteinDetected() const {
    int DNA = 0;
    int Protein = 0;
    int RNA = 0;

    for (int i = 0; i < m_FASTA_Structure.size(); i++) {
        if(m_FASTA_Structure[i].classification == "DNA")
            DNA++;
        if(m_FASTA_Structure[i].classification == "Protein")
            Protein++;
        if(m_FASTA_Structure[i].classification == "RNA")
            RNA++;
    }

    if(DNA >= 1 && Protein == 0 && RNA == 0)
        return "DNA";
    if(DNA == 0 && Protein >= 1 && RNA == 0)
        return "Protein";
    if(DNA == 0 && Protein == 0 && RNA >= 0)
        return "RNA";
    else
        return "undefinied";
}



