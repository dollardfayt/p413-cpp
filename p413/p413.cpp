#include <iostream>
#include <string>
#include <vector>
#include <clocale> 

class Book {
private:
    std::string author;
    std::string title;
    std::string publisher;
    int year;
    int pageCount;

public:
    explicit Book(const std::string& author, const std::string& title, const std::string& publisher, int year, int pageCount)
        : author(author), title(title), publisher(publisher), year(year), pageCount(pageCount) {
    }

    const std::string& getAuthor() const { return author; }
    const std::string& getTitle() const { return title; }
    const std::string& getPublisher() const { return publisher; }
    int getYear() const { return year; }
    int getPageCount() const { return pageCount; }

    void displayBook() const {
        std::cout << "Автор: " << author << std::endl;
        std::cout << "Название: " << title << std::endl;
        std::cout << "Издательство: " << publisher << std::endl;
        std::cout << "Год: " << year << std::endl;
        std::cout << "Страниц: " << pageCount << std::endl;
        std::cout << std::endl;
    }
};


void showBooksByAuthor(const std::vector<Book>& books, const std::string& author) {
    bool found = false;
    for (const auto& book : books) {
        if (book.getAuthor() == author) {
            book.displayBook();
            found = true;
        }
    }
    if (!found) {
        std::cout << "Книги автора \"" << author << "\" не найдены." << std::endl;
    }
}

void showBooksByPublisher(const std::vector<Book>& books, const std::string& publisher) {
    bool found = false;
    for (const auto& book : books) {
        if (book.getPublisher() == publisher) {
            book.displayBook();
            found = true;
        }
    }
    if (!found) {
        std::cout << "Книги издательства \"" << publisher << "\" не найдены." << std::endl;
    }
}

void showBooksAfterYear(const std::vector<Book>& books, int year) {
    bool found = false;
    for (const auto& book : books) {
        if (book.getYear() > year) {
            book.displayBook();
            found = true;
        }
    }
    if (!found) {
        std::cout << "Книги, выпущенные после " << year << " года, не найдены." << std::endl;
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    std::vector<Book> books;
    books.emplace_back("Alice Johnson", "The Midnight Bloom", "Stellaris Publishing", 2024, 385);
    books.emplace_back("Robert Chen", "Echoes of the Past", "Nova Books", 2019, 512);
    books.emplace_back("Emily Davis", "Secrets of the Deep", "Oceanus Press", 2022, 420);
    books.emplace_back("David Wilson", "The Lost City of Eldoria", "Mythic Tales Inc", 2022, 680);
    books.emplace_back("Sarah Rodriguez", "Shadows in the Wind", "Aurora Publishing", 2023, 320);
    books.emplace_back("Michael Brown", "The Alchemist's Legacy", "Emerald Books", 2017, 455);

    std::cout << "Книги автора Alice Johnson:" << std::endl;
    showBooksByAuthor(books, "Alice Johnson");

    std::cout << "Книги издательства Nova Books:" << std::endl;
    showBooksByPublisher(books, "Nova Books");

    std::cout << "Книги, выпущенные после 2020 года:" << std::endl;
    showBooksAfterYear(books, 2020);

    return 0;
}
