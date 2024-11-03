#include <fstream>
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <list>
#include <functional> 
#include <numeric>

#include "SongCollection.h"

using namespace std;

namespace seneca {

    SongCollection::SongCollection(const char* filename) {
        fstream file(filename, ios::in);
        
        if(!file.is_open())
            throw runtime_error("Can't find / open file...");


        char _buffer[26];


        while(file.read(_buffer, 25)) {

            Song _song{};

            _buffer[25] = '\0';
            _song.title = _buffer;
            _song.title.erase(_song.title.find_last_not_of(' ') + 1);

            file.read(_buffer, 25);
            _buffer[25] = '\0';
            _song.artist = _buffer;
            _song.artist.erase(_song.artist.find_last_not_of(' ') + 1);

            file.read(_buffer, 25);
            _buffer[25] = '\0';
            _song.album = _buffer;
            _song.album.erase(_song.album.find_last_not_of(' ') + 1);

            file.read(_buffer, 5);
            _buffer[5] = '\0';
            string(_buffer).erase(string(_buffer).find_last_not_of(' ') + 1);
            _song.year = (_buffer[0] != ' ') ? stoi(string(_buffer)) : 0;

            file.read(_buffer, 5);
            _buffer[5] = '\0';
            string(_buffer).erase(string(_buffer).find_last_not_of(' ') + 1);
            _song.len = stoi(string(_buffer));      

            file.read(_buffer, 5);
            _buffer[5] = '\0';
            string(_buffer).erase(string(_buffer).find_last_not_of(' ') + 1);
            _song.price = stod(string(_buffer));
            
            file.get();

            songs.push_back(_song);
        }

        file.close();
    }; 

    void SongCollection::sort(const char* sortBy) {   

        std::sort(songs.begin(), songs.end(), [=](const Song& x, const Song& y) {
            if(string(sortBy) == "title")   
                return x.title < y.title;
            
            if(string(sortBy) == "album")
                return x.album < y.album;

            if(string(sortBy) == "length")
                return x.len < y.len;
            
            return false;
        });
    }

    void SongCollection::cleanAlbum() {
        transform(songs.begin(), songs.end(), songs.begin(), [](Song& theSong) {
            if(theSong.album == "[None]"){
                theSong.album.clear();
            }

            return theSong;
        }); 

        // ANOTHER METHOD
        // for_each(songs.begin(), songs.end(), [](Song& theSong){
        //     if(theSong.album == "[None]")
        //         theSong.album.clear();
        // });
    }

    void SongCollection::display(std::ostream& out) const { 
        copy(songs.begin(), songs.end(), ostream_iterator<Song>(out, "\n"));

        auto totalLen = accumulate(songs.begin(), songs.end(), (int)0, [](int& sum, const Song& theSong) {
            return sum += theSong.len;
        });

        // int totalLen{};
        // for_each(songs.begin(), songs.end(), [&](const Song& theSong) {
        //     totalLen += theSong.len;
        //     out << theSong << endl;
        // });

        out << "----------------------------------------------------------------------------------------" << endl;
        out << "| " << setw(77) << right << "Total Listening Time: " << (totalLen / 60 / 60) << ':' << ((totalLen / 60) % 60) << ':' << (totalLen % 60) << " |" << endl;
    }

    bool SongCollection::inCollection(const string& theArtist) const {
        return any_of(songs.begin(), songs.end(), [=](const Song& theSong) {
            return theSong.artist == theArtist; 
        });

        // bool found = false;
        // for_each(songs.begin(), songs.end(), [=, &found](const Song& theSong){
        //     if(theSong.artist == theArtist) found = true;
        // });
        // return found;
    }

    std::list<Song> SongCollection::getSongsForArtist(const string& theArtist) const {
        std::list<Song> _songs{};

        if(inCollection(theArtist)) {

            copy_if(songs.begin(), songs.end(), back_inserter(_songs), [theArtist](const Song& theSong){
                return theSong.artist == theArtist;
            });

            // ANOTHER METHOD
            // for_each(songs.begin(), songs.end(), [=, &_songs](const Song& theSong){
            //     if(theSong.artist == theArtist) _songs.push_back(theSong); 
            // });
        }

        return _songs;
    }

    ostream& operator<<(ostream& out, const Song& theSong) {
        out 
            << "| " << left << setw(20) << theSong.title 
            << " | " << left << setw(15) << theSong.artist
            << " | " << left << setw(20) << theSong.album
            << " | " << left << setw(6) << ((theSong.year == 0) ? " " : to_string(theSong.year))
            << " | " << left << (theSong.len / 60) << ':' << ((theSong.len % 60) > 9 ? '\0' : '0') << (theSong.len % 60)
            << " | " << left << theSong.price << " |";
        return out;
    }
}
