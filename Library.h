#ifndef LIBRARY_H
#define LIBRARY_H

#include "Book.h"
#include "Member.h"
#include "Loan.h"
#include <vector>
#include <string>

class Library {
private:
    std::vector<Book> books_;
    std::vector<Member> members_;
    std::vector<Loan> loans_;
public:
    Library() = default;

    void addBook(const Book& b);
    void addMember(const Member& m);

    bool hasBook(const std::string& isbn) const;
    bool isBookAvailable(const std::string& isbn) const;

    bool loanBook(const std::string& isbn, const std::string& memberId, const std::string& start, const std::string& due);
    bool returnBook(const std::string& isbn, const std::string& memberId);

    std::vector<Book> findByAuthor(const std::string& authorName) const;

    std::string to_string() const;
};

#endif
