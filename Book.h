#ifndef BOOK_H
#define BOOK_H

#include "Author.h"
#include <string>
#include <sstream>
#include <stdexcept>

class Book {
private:
    std::string title_;
    Author author_;
    int year_;
    double price_;
    std::string isbn_;

    static int totalBooks_;
public:
    Book()
        : title_("Untitled"), author_(), year_(1900), price_(0.0), isbn_("") {
        ++totalBooks_;
    }

    Book(const std::string& title, const Author& author, int year, double price, const std::string& isbn)
        : title_(title), author_(author), year_(year), price_(price), isbn_(isbn) {
        setYear(year);
        setPrice(price);
        setIsbn(isbn);
        ++totalBooks_;
    }

    Book(const Book& other)
        : title_(other.title_), author_(other.author_), year_(other.year_), price_(other.price_), isbn_(other.isbn_) {
        ++totalBooks_;
    }

    Book(Book&& other) noexcept
        : title_(std::move(other.title_)),
          author_(std::move(other.author_)),
          year_(other.year_),
          price_(other.price_),
          isbn_(std::move(other.isbn_)) {
        ++totalBooks_;
        other.year_ = 0;
        other.price_ = 0.0;
    }

    Book& operator=(const Book& other) {
        if (this != &other) {
            title_ = other.title_;
            author_ = other.author_;
            year_ = other.year_;
            price_ = other.price_;
            isbn_ = other.isbn_;
        }
        return *this;
    }

    Book& operator=(Book&& other) noexcept {
        if (this != &other) {
            title_ = std::move(other.title_);
            author_ = std::move(other.author_);
            year_ = other.year_;
            price_ = other.price_;
            isbn_ = std::move(other.isbn_);
            other.year_ = 0;
            other.price_ = 0.0;
        }
        return *this;
    }

    ~Book() { --totalBooks_; }

    const std::string& getTitle() const { return title_; }
    const Author& getAuthor() const { return author_; }
    int getYear() const { return year_; }
    double getPrice() const { return price_; }
    const std::string& getIsbn() const { return isbn_; }

    void setTitle(const std::string& t) { title_ = t; }
    void setAuthor(const Author& a) { author_ = a; }
    void setYear(int y) {
        if (y < 1450 || y > 2025) throw std::invalid_argument("Book::setYear");
        year_ = y;
    }
    void setPrice(double p) {
        if (p < 0.0) throw std::invalid_argument("Book::setPrice");
        price_ = p;
    }
    void setIsbn(const std::string& i) {
        if (i.empty()) throw std::invalid_argument("Book::setIsbn");
        isbn_ = i;
    }

    std::string to_string() const {
        std::ostringstream oss;
        oss << "Book{title=\"" << title_
            << "\", author=\"" << author_.getName()
            << "\", year=" << year_
            << ", price=" << price_
            << ", isbn=\"" << isbn_ << "\"}";
        return oss.str();
    }

    static int getTotalBooks() { return totalBooks_; }
};

#endif
