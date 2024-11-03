#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>

#include "verifyIdentityPlugin.h"
#include "message.h"

using namespace std;

namespace seneca {
    VerifyIdentityPlugin::VerifyIdentityPlugin(const char* filename) {
        ifstream fs(filename);

        if(!fs.is_open()) {
            throw runtime_error("you fucked up");
        } 

        string buffer;
        while(getline(fs, buffer)) {

            trustedKeywords[iNum] = buffer;
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

    void VerifyIdentityPlugin::operator()(Message& msg) {
        for(auto i = 0u; i < iNum; ++i) {
            if(msg.m_fromAddress == trustedKeywords[i]) {
                msg.m_subject = "[TRUSTED]" + msg.m_subject;
                ++trustCounter;
            }
        }
    }

    void VerifyIdentityPlugin::showStats() const {
        cout << "[Identity Checker Plugin] can validate identity for ";
        for(auto i = 0u; i < iNum; ++i) {
            cout << trustedKeywords[i] << ", ";
        }
    }
}