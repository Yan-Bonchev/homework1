#include "Library.h"
#include <algorithm>
#include <sstream>
#include <stdexcept>

void Library::addBook(const Book& b) {
    if (hasBook(b.getIsbn())) throw std::runtime_error("duplicate isbn");
    books_.push_back(b);
}

void Library::addMember(const Member& m) {
    auto it = std::find_if(members_.begin(), members_.end(),
        [&](const Member& mm){ return mm.getMemberId() == m.getMemberId(); });
    if (it != members_.end()) throw std::runtime_error("duplicate memberId");
    members_.push_back(m);
}

bool Library::hasBook(const std::string& isbn) const {
    return std::any_of(books_.begin(), books_.end(),
        [&](const Book& b){ return b.getIsbn() == isbn; });
}

bool Library::isBookAvailable(const std::string& isbn) const {
    if (!hasBook(isbn)) return false;
    for (const auto& loan : loans_) {
        if (loan.getIsbn() == isbn && !loan.isReturned()) return false;
    }
    return true;
}

bool Library::loanBook(const std::string& isbn, const std::string& memberId,
                       const std::string& start, const std::string& due) {
    if (!hasBook(isbn)) return false;
    auto memIt = std::find_if(members_.begin(), members_.end(),
        [&](const Member& m){ return m.getMemberId() == memberId; });
    if (memIt == members_.end()) return false;
    if (!isBookAvailable(isbn)) return false;

    try {
        loans_.emplace_back(isbn, memberId, start, due);
    } catch (...) {
        return false;
    }
    return true;
}

bool Library::returnBook(const std::string& isbn, const std::string& memberId) {
    for (auto& loan : loans_) {
        if (loan.getIsbn() == isbn && loan.getMemberId() == memberId && !loan.isReturned()) {
            loan.markReturned();
            return true;
        }
    }
    return false;
}

std::vector<Book> Library::findByAuthor(const std::string& authorName) const {
    std::vector<Book> result;
    for (const auto& b : books_) {
        if (b.getAuthor().getName().find(authorName) != std::string::npos) result.push_back(b);
    }
    return result;
}

std::string Library::to_string() const {
    std::ostringstream oss;
    int activeLoans = 0;
    for (const auto& l : loans_) if (!l.isReturned()) ++activeLoans;
    oss << "Library{books=" << books_.size()
        << ", members=" << members_.size()
        << ", activeLoans=" << activeLoans << "}";
    return oss.str();
}
