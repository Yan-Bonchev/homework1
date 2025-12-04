#ifndef AUTHOR_H
#define AUTHOR_H

#include <string>
#include <sstream>
#include <stdexcept>

class Author {
private:
    std::string name_;
    int birthYear_;
public:
    Author() : name_("Unknown"), birthYear_(1900) {}
    Author(const std::string& name, int birthYear) : name_(name) {
        setBirthYear(birthYear);
    }

    const std::string& getName() const { return name_; }
    int getBirthYear() const { return birthYear_; }

    void setName(const std::string& name) { name_ = name; }
    void setBirthYear(int y) {
        if (y < 1850 || y > 2025) throw std::invalid_argument("Author::setBirthYear");
        birthYear_ = y;
    }

    std::string to_string() const {
        std::ostringstream oss;
        oss << "Author{name=\"" << name_ << "\", birthYear=" << birthYear_ << "}";
        return oss.str();
    }
};

#endif
