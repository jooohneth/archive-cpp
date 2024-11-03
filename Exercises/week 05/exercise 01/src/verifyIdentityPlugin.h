#ifndef SENECA_VERIFYIDENTITYPLUGIN_H
#define SENECA_VERIFYIDENTITYPLUGIN_H

#include <string>

#include "plugin.h"

namespace seneca {
    class VerifyIdentityPlugin : public Plugin {
        std::string trustedKeywords[3]{};
        size_t iNum{};
        unsigned trustCounter{};
        
        public:
            VerifyIdentityPlugin(const char* filename);
            void operator()(Message& msg);
            void showStats() const;
    };
}

#endif