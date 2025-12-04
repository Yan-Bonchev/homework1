#ifndef MEMBER_H
#define MEMBER_H

#include <string>
#include <sstream>
#include <stdexcept>

class Member {
private:
    std::string name_;
    std::string memberId_;
    int yearJoined_;
public:
    Member() : name_("Unknown"), memberId_(""), yearJoined_(0) {}
    Member(const std::string& name, const std::string& memberId, int yearJoined)
        : name_(name), memberId_(memberId), yearJoined_(yearJoined) {
        if (memberId_.empty()) throw std::invalid_argument("Member::memberId");
    }

    const std::string& getName() const { return name_; }
    const std::string& getMemberId() const { return memberId_; }
    int getYearJoined() const { return yearJoined_; }

    void setName(const std::string& n) { name_ = n; }
    void setMemberId(const std::string& id) {
        if (id.empty()) throw std::invalid_argument("Member::setMemberId");
        memberId_ = id;
    }
    void setYearJoined(int y) { yearJoined_ = y; }

    std::string to_string() const {
        std::ostringstream oss;
        oss << "Member{name=\"" << name_ << "\", memberId=\"" << memberId_
            << "\", yearJoined=" << yearJoined_ << "}";
        return oss.str();
    }
};

#endif
