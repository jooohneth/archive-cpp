#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>

#include "spamFilterPlugin.h"
#include "message.h"

using namespace std;

namespace seneca {
    SpamFilterPlugin::SpamFilterPlugin(const char* filename) {
        ifstream fs(filename);

        if(!fs.is_open()) {
            throw runtime_error("you fucked up");
        } 

        string buffer;
        while(getline(fs, buffer)) {

            spamKeywords[iNum] = buffer;
            ++iNum;


            // getline(fs, buffer, ',');
            // getline(fs, buffer, ',');

            // if(buffer.find("?!?!") != string::npos || buffer.find("ltery") != string::npos || buffer.find("Exciting News!!!") != string::npos) {
            //     spamEmails[i] = buffer;
            //     ++i;
            // }

            // getline(fs, buffer);
        }
    }

    void SpamFilterPlugin::operator()(Message& msg) {
        for(auto i = 0u; i < iNum; ++i) {
            
            if(msg.m_subject.find(spamKeywords[i]) != string::npos) {
                msg.m_subject = "[SPAM] " + msg.m_subject;
                ++spamCounter;
            }

        }
    }

    void SpamFilterPlugin::showStats() const {
        cout << "[Spam Filter Plugin] Identified " << spamCounter << " spam messages." << endl;
    }

}