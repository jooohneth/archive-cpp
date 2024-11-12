#ifndef SENECA_MOVIE_H
#define SENECA_MOVIE_H 

#include "mediaItem.h"
#include <iostream> 
#include <string>

namespace seneca {
    class Movie : public MediaItem {
        Movie(std::string _title, std::string _summary, unsigned short _year);

        public: 
            void display(std::ostream& out) const override;
            static Movie* createItem(const std::string& strMovie);
    };
}

#endif 