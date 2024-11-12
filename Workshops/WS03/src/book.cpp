#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <stdexcept>

#include "settings.h"
#include "book.h"
#include "mediaItem.h"

using namespace std;

namespace seneca { 
    Book::Book(const string& _author, const string& _country, double _price, const string& _title, const string& _summary, unsigned short _year) :
        MediaItem(_title, _summary, _year),
        m_author{_author},
        m_country{_country},
        m_price{_price}
    {}

    Book* Book::createItem(const string& strBook) {
		if(strBook.empty() || strBook[0] == '#') {
			throw "Not a valid book.";
		}

		string copy = strBook; 

		string _author{};
		string _country{};
		double _price{};
		string _title{};
		string _summary{};
		unsigned short _year{};

		_author = copy.substr(0, copy.find(","));
		copy.erase(0, copy.find(",") + 1);
		trim(_author);



		_title = copy.substr(0, copy.find(","));
		copy.erase(0, copy.find(",") + 1);
		trim(_title);



		_country = copy.substr(0, copy.find(","));
		copy.erase(0, copy.find(",") + 1);
		trim(_country);


		_price = stod(copy.substr(0, copy.find(",")));
		copy.erase(0, copy.find(",") + 1);


		_year = stoi(copy.substr(0, copy.find(",")));
		copy.erase(0, copy.find(",") + 1);

		trim(copy);
		_summary = copy;

		return new Book(_author, _country, _price, _title, _summary, _year);
    }  

    void Book::display(ostream& out) const {
        if (g_settings.m_tableView)
  	    {
  	    	out << "B | ";
  	    	out << std::left << std::setfill('.');
  	    	out << std::setw(50) << this->getTitle() << " | ";
  	    	out << std::right << std::setfill(' ');
  	    	out << std::setw(2) << this->m_country << " | ";
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
  	    	out << this->getTitle() << " [" << this->getYear() << "] [";
  	    	out << m_author << "] [" << m_country << "] [" << m_price << "]\n";
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