#ifndef SENECA_BOOK_H
#define SENECA_BOOK_H 

#include <string>
#include <iostream>

#include "mediaItem.h"

namespace seneca {
    class Book : public MediaItem {
        std::string m_author{};
        std::string m_country{};
        double m_price{};
        
        Book(const std::string& _author, const std::string& _country, double _price, const std::string& _title, const std::string& _summary, unsigned short _year);

        public:
            void display(std::ostream& out) const override;
            static Book* createItem(const std::string& strBook);
    };
}

#endif 