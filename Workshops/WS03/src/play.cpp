#include <iostream>
#include <sstream>
#include <array>
#include <fstream>
#include <array>

using namespace std;

using theArray = std::array<std::string, 6>;

void trim(std::string& str)
		{
			size_t i = 0u;
			for (i = 0u; i < str.length() && str[i] == ' '; ++i);
			str = str.substr(i);

			for (i = str.length(); i > 0 && str[i - 1] == ' '; --i);
			str = str.substr(0, i);
		}

void spellChecker(const char* filename, theArray& m_badWords, theArray& m_goodWords) {
        fstream fs(filename, ios::in);
        
        if(fs.is_open()) {
            char buffer[50]{};
            string strBuffer{}; 
            size_t idx = 0;

            while(fs.read(buffer, 13) && idx < 6) {
                strBuffer = buffer;

                strBuffer.erase(strBuffer.find_last_not_of(" ") + 1);

                cout << '[' <<  strBuffer << ']' << endl;

                m_badWords[idx] = strBuffer;

                getline(fs, strBuffer, '\n');

                cout << '[' <<  strBuffer << ']' << endl;

                m_goodWords[idx] = strBuffer;

                cout << "  ------------   --------------  - ------" << endl;

                ++idx;
            }
            
        } else {
            throw runtime_error("Bad file name!");
        }

    }

int main(int, char** argv) {
    theArray m_badWords{};
    theArray m_goodWords{};

    spellChecker(argv[1], m_badWords, m_goodWords);

    for(auto item : m_badWords) 
        cout << item << endl;

    cout << "------------------------" << endl; 

    for(auto item : m_goodWords) 
        cout << item << endl;

    // string copy{"   Thai      ,   something, somethingelse"};

    // string _author = copy.substr(0, copy.find(","));
	// copy.erase(0, copy.find(",") + 1);

    // cout << '[' << _author << ']' << endl;
    // cout << '[' << copy << ']' << endl;


    // // cout << first << endl;

    // // trim(first);

    // // cout << '[' << first << ']' << endl;


    // // stringstream sStream(bookStr);

    // // char buffer[50]{};
    // // char _[1]{};

    // // // sStream.getline(buffer, '\n');

    // // while (sStream >> buffer) {
    // //     sStream >> _; 
    // //     cout << '[' << buffer << ']' << endl;
    // // }
    

    // // cout << '[' << buffer << ']' << endl;
}