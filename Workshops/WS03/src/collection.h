#ifndef SENECA_COLLECTION_H
#define SENECA_COLLECTION_H 

#include <string>
#include <vector>
#include <iostream>

#include "mediaItem.h"

namespace seneca {
    class Collection {
        using fptr = void(*)(const Collection&, const MediaItem&);

        std::string m_name{};
        std::vector<MediaItem*> m_collection{};
        fptr m_observer{};

        public:   
            Collection(const Collection& other) = delete;
            Collection(Collection&& other) = delete;
            Collection& operator=(const Collection& other) = delete;
            Collection& operator=(Collection&& other) = delete;

            Collection(const std::string& name);
            ~Collection();

            const std::string& name() const;
            size_t size() const;

            void setObserver(void (*observer)(const Collection&, const MediaItem&));
            Collection& operator+=(MediaItem* item);

            MediaItem* operator[](size_t idx) const;
            MediaItem* operator[](const std::string& title) const;

            void removeQuotes();
            void sort(const std::string& field);

            friend std::ostream& operator<<(std::ostream&, const Collection& collection);
    };
}

#endif 