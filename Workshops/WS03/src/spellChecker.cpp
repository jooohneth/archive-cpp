#include "spellChecker.h"

#include <array>
#include <string>
#include <fstream>
#include <iomanip>
#include <stdexcept>

using namespace std;

namespace seneca {
    SpellChecker::SpellChecker(const char* filename) {
        fstream fs(filename, ios::in);
        
        if(fs.is_open()) {
            char buffer[50]{};
            string strBuffer{};
            size_t idx{};

            while(fs.read(buffer, 13) && idx < 6) {
                strBuffer = buffer;
                strBuffer.erase(strBuffer.find_last_not_of(" ") + 1);
                m_badWords[idx] = strBuffer;

                getline(fs, strBuffer, '\n');
                m_goodWords[idx] = strBuffer;

                ++idx;
            }
            
        } else {
            throw runtime_error("Bad file name!");
        }

    }

void SpellChecker::operator()(std::string& text) {
    for (size_t i = 0; i < 6; i++) {
        size_t pos = 0;
        while ((pos = text.find(m_badWords[i], pos)) != std::string::npos) {
            text.replace(pos, m_badWords[i].length(), m_goodWords[i]);
            pos += m_goodWords[i].length();
            m_counts[i]++;
        }
    }
}
    
    void SpellChecker::showStatistics(std::ostream& out) const {
        out << "Spellchecker Statistics\n";
        for(auto i = 0u; i < m_counts.size(); ++i) {
            out << left << setw(15) << m_badWords[i] << ": " << m_counts[i] << " replacements" << endl;       
        }
    }
}