#ifndef SENECA_SONGCOLLECTION_H
#define SENECA_SONGCOLLECTION_H

#include <vector>
#include <string>
#include <functional>
#include <chrono>

namespace seneca {
    struct Song {
        std::string artist{};
        std::string title{};
        std::string album{};
        double price{};
        int year{};
        int len{};

        friend std::ostream& operator<<(std::ostream& out, const Song& theSong);
    };

    class SongCollection {
        std::vector<Song> songs{};

        public:
            SongCollection(const char* filename);

            std::list<Song> getSongsForArtist(const std::string& theArtist) const;
            bool inCollection(const std::string& theArtist) const;
            void cleanAlbum();      
            void sort(const char* sortBy);
            void display(std::ostream& out) const;

    };

}

#endif