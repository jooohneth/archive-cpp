#include "mediaItem.h"
#include "collection.h" 

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

namespace seneca {
    Collection::Collection(const std::string& name) : m_name{name} {}

    Collection::~Collection() {
    for(auto item : m_collection) {
        delete item;
    }
    m_collection.clear();
    }

    const std::string& Collection::name() const {
        return m_name;
    }

    size_t Collection::size() const {
        return m_collection.size();
    }

    void Collection::setObserver(void (*observer)(const Collection&, const MediaItem&)) {
        if(observer != nullptr)
            m_observer = observer;
    }

    Collection& Collection::operator+=(MediaItem* item) { 
        if(item == nullptr) {
            return *this;
        }

        for(auto i = 0u; i < m_collection.size(); ++i) {
            if(m_collection[i] != nullptr && item->getTitle() == m_collection[i]->getTitle()){
                delete item;
                return *this;
            }
        }

        m_collection.push_back(item);
        
        if(m_observer) {
            (*m_observer)(*this, *item);
        }
        return *this;
    }

    MediaItem* Collection::operator[](size_t idx) const {
        return m_collection.at(idx);
    }

    MediaItem* Collection::operator[](const std::string& title) const {
        auto it = find_if(m_collection.begin(), m_collection.end(), [=](const MediaItem* item) {
            return item->getTitle() == title;
        });
        
        return (it != m_collection.end()) ? *it : nullptr;
    }

    void Collection::removeQuotes() {
        auto removeQuotesFromString = [](string& str) {
            if(str.front() == '"') 
                str = str.substr(1, str.length() - 1);

            if(str.back() == '"')   
                str = str.substr(0, str.length() - 1);
                
            // if (str.front() == '"' || str.back() == '"') {
            //     str = str.substr(1, str.length() - 2);
            // }
        };

        for_each(m_collection.begin(), m_collection.end(), [=](MediaItem* item) {
            string title = item->getTitle();
            string summary = item->getSummary();
            removeQuotesFromString(title);
            removeQuotesFromString(summary);
            item->setTitle(title);
            item->setSummary(summary); 
        });
    }

    void Collection::sort(const std::string& field) {
        std::sort(m_collection.begin(), m_collection.end(), [field](const MediaItem* a, const MediaItem* b) {
            if (field == "title")
                return a->getTitle() < b->getTitle();
            else if (field == "year") 
                return a->getYear() < b->getYear();
            else
                return false;
        });
    }
    
    std::ostream& operator<<(std::ostream& out, const Collection& collection) {
        for (const auto* item : collection.m_collection) {
            out << *item;
        }
        return out;
    }

}