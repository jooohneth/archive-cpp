#include <string>
#include <iomanip>
#include <iostream>

#include "plugin.h"
#include "message.h"
#include "mailServer.h"


using namespace std;

namespace seneca {
    MailServer::MailServer(const char* name, const char* address) : m_userName{string(name)}, m_userAddress{string(address)}{}

    MailServer::MailServer(const MailServer& other) {
        *this = other;
    }

    MailServer& MailServer::operator=(const MailServer& other) {
        if(this != & other) {
            delete[] m_inbox;

            m_userName = other.m_userName;
            m_userAddress = other.m_userAddress;
            m_cnt = other.m_cnt;
            // onNewMailArrive = other.onNewMailArrive;

            for(auto i = 0u; i < 2; ++i) {
                m_plugins[i] = other.m_plugins[i];
            }

            if(m_cnt > 0) {
                m_inbox = new Message[m_cnt];

                for(auto i = 0u; i < m_cnt; ++i) {
                    m_inbox[i] = other.m_inbox[i];
                }
            } else {
                m_inbox = nullptr;
            }
        }
        return *this;
    }

    MailServer::MailServer(MailServer&& other) noexcept {
        *this = std::move(other);
    }

    MailServer& MailServer::operator=(MailServer&& other) noexcept {
            if(this != & other) {
            delete[] m_inbox;

            m_userName = std::move(other.m_userName);
            m_userAddress = std::move(other.m_userAddress);
            m_cnt = other.m_cnt;
            // onNewMailArrive = other.onNewMailArrive;

            for(auto i = 0u; i < 2; ++i) {
                m_plugins[i] = std::move(other.m_plugins[i]);
            }

            m_inbox = other.m_inbox;

            other.m_userName = "";
            other.m_userAddress = "";
            other.m_cnt = 0;
            other.onNewMailArrive = nullptr;
            other.m_inbox = nullptr;
        }

        return *this;
    }

    void MailServer::receiveMail(Message msg) {
        if(msg.m_toAddress != m_userAddress) {
            throw std::runtime_error("Message addressed to a different user: " + msg.m_toAddress);
        }
    
        auto temp = new Message[m_cnt + 1];

        for(auto i = 0u; i < m_cnt; ++i) 
            temp[i] = m_inbox[i];
        delete[] m_inbox;


        temp[m_cnt] = msg;
        m_inbox = temp;
        ++m_cnt;

        for(auto i = 0u; i < 2; ++i) {
            if(m_plugins[i]) 
                (*m_plugins[i])(m_inbox[m_cnt - 1]);
        }

        if(onNewMailArrive) 
            onNewMailArrive(msg);
    }

    void MailServer::addPlugin(Plugin* thePlugin) {
        for(auto i = 0u; i < 2; ++i) {
            if(m_plugins[i] == nullptr) {
                m_plugins[i] = thePlugin;
                return;
            }
        }
    }

    void MailServer::setObserver(Observer_pfn observer) {
        onNewMailArrive = observer;
    }

    Message& MailServer::operator[](size_t idx) {
        if(idx >= m_cnt) {
            throw out_of_range("Index " +  to_string(idx) +  " is out of bounds");
        }

        return m_inbox[idx];
        
    }

    size_t MailServer::getInboxSize() {
        return m_cnt;
    }
    
    void MailServer::showInbox() {

        for(auto i = 0u; i < m_cnt; ++i) {
            cout << right << setw(20) << m_inbox[i].m_fromName << ' '; 
            cout << left << setw(40) << m_inbox[i].m_fromAddress << ' ';
            cout << left << setw(15) << m_inbox[i].m_date << ' ';
            cout << m_inbox[i].m_subject << endl;
        }
    }

    MailServer::~MailServer() {
        delete[] m_inbox;
    }
}
