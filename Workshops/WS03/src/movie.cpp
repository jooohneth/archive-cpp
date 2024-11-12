#include "movie.h"
#include "settings.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <stdexcept>

using namespace std;

namespace seneca {
    Movie::Movie(string _title, string _summary, unsigned short _year) : MediaItem(_title, _summary, _year) {}  


    Movie* Movie::createItem(const std::string& strMovie) {
        if(strMovie.empty() || strMovie[0] == '#') {
			throw "Not a valid movie.";
		}

        string copy = strMovie;

        string _title;
        unsigned short _year;
        string _summary; 

        _title = copy.substr(0, copy.find(","));
		copy.erase(0, copy.find(",") + 1);
		trim(_title);


        _year = stoi(copy.substr(0, copy.find(",")));
		copy.erase(0, copy.find(",") + 1);


        trim(copy);
	    _summary = copy;

        return new Movie(_title, _summary, _year);
    }

    void Movie::display(std::ostream& out) const
	{
		if (g_settings.m_tableView)
		{
			out << "M | ";
			out << std::left << std::setfill('.');
			out << std::setw(50) << this->getTitle() << " | ";
			out << std::right << std::setfill(' ');
			out << std::setw(9) << this->getYear() << " | ";
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
			out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << ""
				<< std::setfill(' ') << '\n';
		}
	}
}
