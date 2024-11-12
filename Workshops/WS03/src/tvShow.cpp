#include "tvShow.h"
#include "settings.h"

#include <list>
#include <iostream>
#include <string>
#include <iomanip>
#include <stdexcept>
#include <algorithm>
#include <numeric>
#include <functional>
#include <stdexcept>

using namespace std;

namespace seneca {
    TvShow::TvShow(string _id, std::string _title, unsigned short _year, std::string _summary) : 
        MediaItem(_title, _summary, _year),
        m_id{_id}
    {}


    void TvShow::display(std::ostream& out) const {
        if (g_settings.m_tableView)
		{
			out << "S | ";
			out << std::left << std::setfill('.');
			out << std::setw(50) << this->getTitle() << " | ";
			out << std::right << std::setfill(' ');
			out << std::setw(2) << this->m_episodes.size() << " | ";
			out << std::setw(4) << this->getYear() << " | ";
			out << std::left;
			if (g_settings.m_maxSummaryWidth > -1)
			{
				if (static_cast<short>(this->getSummary().size()) <= g_settings.m_maxSummaryWidth)
					out << this->getSummary();
				else
					out << this->getSummary().substr(0, g_settings.m_maxSummaryWidth - 3) << "...";
			}
			else
				out << this->getSummary();
			out << std::endl;
		}
		else
		{
			size_t pos = 0;
			out << this->getTitle() << " [" << this->getYear() << "]\n";
			out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << "" << '\n';
			while (pos < this->getSummary().size())
			{
				out << "    " << this->getSummary().substr(pos, g_settings.m_maxSummaryWidth) << '\n';
				pos += g_settings.m_maxSummaryWidth;
			}
			for (auto& item : m_episodes)
			{
				out << std::setfill('0') << std::right;
				out << "    " << 'S' << std::setw(2) << item.m_season
					<< 'E' << std::setw(2) << item.m_numberInSeason << ' ';
				if (item.m_title != "")
					out << item.m_title << '\n';
				else
					out << "Episode " << item.m_numberOverall << '\n';

				pos = 0;
				while (pos < item.m_summary.size())
				{
					out << "            " << item.m_summary.substr(pos, g_settings.m_maxSummaryWidth - 8) << '\n';
					pos += g_settings.m_maxSummaryWidth - 8;
				}
			}
			out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << ""
				<< std::setfill(' ') << '\n';
		}
    }

    TvShow* TvShow::createItem(const std::string& strShow) {   
		if(strShow.empty() || strShow[0] == '#') {
			throw "Not a valid show.";
		}        

            string copy = strShow;

            string _id{};
            string _title{};
            string _summary{};
            unsigned short _year{};


            _id = copy.substr(0, copy.find(","));
            copy.erase(0, copy.find(",") + 1);
            trim(_id);
            
            _title = copy.substr(0, copy.find(","));
            copy.erase(0, copy.find(",") + 1);
            trim(_title);
                
            _year = stoi(copy.substr(0, copy.find(",")));
            copy.erase(0, copy.find(",") + 1);

            trim(copy);
            _summary = copy;

            return new TvShow(_id, _title, _year, _summary);
    }

    double TvShow::getEpisodeAverageLength() const {
        unsigned int totalLength = accumulate(m_episodes.begin(), m_episodes.end(), (unsigned int)0, [](unsigned int& sum, const TvEpisode& episode) {
            return sum += episode.m_length;
        });

        return totalLength / m_episodes.size();
    }

    // TODO: copy only the episode title, not the whole content of TvEpisode
    list<string> TvShow::getLongEpisodes() const {
    list<TvEpisode> returnList{};
    
    copy_if(m_episodes.begin(), m_episodes.end(), 
            back_inserter(returnList),
            [](const TvEpisode& episode) {
                return episode.m_length >= 3600;
            });

    // Transform the TvEpisode objects to strings (episode titles)
    list<string> titleList{};
    transform(returnList.begin(), returnList.end(),
             back_inserter(titleList),
             [](const TvEpisode& episode) {
                 return episode.m_title;
             });

    return titleList;
    }

    string TvShow::getId() {
        return m_id;
    }
}