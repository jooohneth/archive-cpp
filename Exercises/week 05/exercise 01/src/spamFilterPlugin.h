#ifndef SENECA_SPAMFILTERPLUGIN_H
#define SENECA_SPAMFILTERPLUGIN_H

#include <string>
#include <iostream>

#include "plugin.h"

namespace seneca {
    class SpamFilterPlugin : public Plugin {   
        std::string spamKeywords[3]{};
        size_t iNum{};
        unsigned spamCounter{};

        public: 
            SpamFilterPlugin(const char* filename);
            void operator()(Message& msg);
            void showStats() const;
    };
}

#endif