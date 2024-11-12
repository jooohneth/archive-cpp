#ifndef SENECA_TVSHOW_H
#define SENECA_TVSHOW_H 

#include "mediaItem.h"
#include <list>
#include <iostream>
#include <string>
#include <algorithm>

namespace seneca {
    class TvShow;

    struct TvEpisode
    {
        const TvShow* m_show{};
        unsigned short m_numberOverall{};
        unsigned short m_season{};
        unsigned short m_numberInSeason{};
        std::string m_airDate{};
        unsigned int m_length{};
        std::string m_title{};
        std::string m_summary{};
    };

    class TvShow : public MediaItem{
        std::string  m_id{};
        std::list<TvEpisode> m_episodes{};

        TvShow(std::string _id, std::string _title, unsigned short _year, std::string _summary);
        std::string getId();
        public:
            void display(std::ostream& out) const override;
            static TvShow* createItem(const std::string& strShow);
            double getEpisodeAverageLength() const;
            std::list<std::string> getLongEpisodes() const;

            template<typename Collection_t> 
            static void addEpisode(Collection_t& col, const std::string& strEpisode) {
                if(strEpisode.empty() || strEpisode[0] == '#') 
                    throw "Not a valid episode.";


                std::string copy = strEpisode;
                TvEpisode episode{};
                episode.m_show = nullptr;

                // Extract ID
                std::string showId = copy.substr(0, copy.find(","));
                copy.erase(0, copy.find(",") + 1);
                trim(showId);

                // Extract episode number
                episode.m_numberOverall = std::stoi(copy.substr(0, copy.find(",")));
                copy.erase(0, copy.find(",") + 1);

                // Extract season number (default to 1 if missing)
                try {
                    episode.m_season = std::stoi(copy.substr(0, copy.find(",")));
                } catch(...) {
                    episode.m_season = 1;
                }
                copy.erase(0, copy.find(",") + 1);

                // Extract episode number in season
                episode.m_numberInSeason = std::stoi(copy.substr(0, copy.find(",")));
                copy.erase(0, copy.find(",") + 1);

                // Extract air date
                episode.m_airDate = copy.substr(0, copy.find(","));
                copy.erase(0, copy.find(",") + 1);
                trim(episode.m_airDate);

                // Extract length
                std::string h = copy.substr(0, copy.find(":"));
                episode.m_length += std::stoi(h) * 3600;
                copy.erase(0, copy.find(":") + 1);

                std::string m = copy.substr(0, copy.find(":"));
                episode.m_length += std::stoi(m) * 60;
                copy.erase(0, copy.find(":") + 1);    

                std::string s = copy.substr(0, copy.find(":"));
                episode.m_length += std::stoi(s);
                copy.erase(0, copy.find(":") + 1);         
                
                copy.erase(0, copy.find(",") + 1);

                // Extract title
                episode.m_title = copy.substr(0, copy.find(","));
                copy.erase(0, copy.find(",") + 1);
                trim(episode.m_title);

                // Extract summary
                episode.m_summary = copy;
                trim(episode.m_summary);

                for(auto i = 0u; i < col.size(); ++i) {
                        
                    TvShow* show = dynamic_cast<TvShow*>(col[i]);
                    if(show && show->getId() == showId) {
                        episode.m_show = show;
                        show->m_episodes.push_back(episode); 
                    } 
                }


                
            }
    };
}

#endif 