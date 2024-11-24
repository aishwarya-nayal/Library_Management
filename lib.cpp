#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

// Helper function to convert a string to lowercase
string toLower(const string& str) {
    string lowerStr = str;
    for (size_t i = 0; i < str.length(); ++i) {
        lowerStr[i] = tolower(str[i]);
    }
    return lowerStr;
}

// Book class definition
class Book {
public:
    int id;
    string title;
    string author;
    int quantity;

    Book(int id, const string& title, const string& author, int quantity)
        : id(id), title(title), author(author), quantity(quantity) {}

    void display() const {
        cout << setw(10) << id << setw(20) << title << setw(20) << author << setw(10) << quantity << endl;
    }
};

void addBook(vector<Book>& books) {
    int id, quantity;
    string title, author;

    cout << "Enter book ID: ";
    cin >> id;

    // Check for duplicate IDs
    for (size_t i = 0; i < books.size(); ++i) {
        if (books[i].id == id) {
            cout << "A book with this ID already exists.\n";
            return;
        }
    }

    cin.ignore();  // To ignore the newline character left by cin >> id
    cout << "Enter book title: ";
    getline(cin, title);
    cout << "Enter book author: ";
    getline(cin, author);
    cout << "Enter book quantity: ";
    cin >> quantity;

    books.push_back(Book(id, title, author, quantity));
    cout << "Book added successfully!\n";
}

void displayBooks(const vector<Book>& books) {
    if (books.empty()) {
        cout << "No books available.\n";
        return;
    }

    cout << setw(10) << "ID" << setw(20) << "Title" << setw(20) << "Author" << setw(10) << "Quantity" << endl;
    cout << string(60, '-') << endl;

    for (size_t i = 0; i < books.size(); ++i) {
        books[i].display();
    }
}

void deleteBook(vector<Book>& books) {
    if (books.empty()) {
        cout << "No books available to delete.\n";
        return;
    }

    int id;
    cout << "Enter the book ID to delete: ";
    cin >> id;

    // Find the book by ID and delete it
    for (size_t i = 0; i < books.size(); ++i) {
        if (books[i].id == id) {
            books.erase(books.begin() + i);
            cout << "Book with ID " << id << " has been deleted.\n";
            return;
        }
    }

    cout << "No book found with ID " << id << ".\n";
}

void loadFromFile(vector<Book>& books, const string& filename) {
    ifstream file(filename.c_str());
    if (!file.is_open()) {
        cout << "Error: Unable to open file " << filename << ".\n";
        return;
    }

    books.clear();
    int id, quantity;
    string title, author;

    while (file >> id) {
        file.ignore();  // Ignore the newline after the ID
        getline(file, title);
        getline(file, author);
        file >> quantity;
        file.ignore();  // Ignore the newline after the quantity
        books.push_back(Book(id, title, author, quantity));
    }

    file.close();
    cout << "Books loaded successfully from " << filename << ".\n";
}

void saveToFile(const vector<Book>& books, const string& filename) {
    ofstream file(filename.c_str());
    if (!file.is_open()) {
        cout << "Error: Unable to open file " << filename << ".\n";
        return;
    }

    for (size_t i = 0; i < books.size(); ++i) {
        file << books[i].id << endl
             << books[i].title << endl
             << books[i].author << endl
             << books[i].quantity << endl;
    }

    file.close();
    cout << "Books saved successfully to " << filename << ".\n";
}

void searchBook(const vector<Book>& books) {
    if (books.empty()) {
        cout << "No books available to search.\n";
        return;
    }

    string query;
    cout << "Enter title or author to search: ";
    getline(cin, query); // Read the full line (title/author)

    bool found = false;
    for (size_t i = 0; i < books.size(); ++i) {
        if (toLower(books[i].title).find(toLower(query)) != string::npos ||
            toLower(books[i].author).find(toLower(query)) != string::npos) {
            books[i].display();
            found = true;
        }
    }

    if (!found) {
        cout << "No matching books found.\n";
    }
}

int main() {
    vector<Book> books;
    const string filename = "books.txt";
    int choice;

    loadFromFile(books, filename);

    do {
        cout << "\nLibrary Management System\n";
        cout << "1. Add Book\n";
        cout << "2. Display All Books\n";
        cout << "3. Search Book\n";
        cout << "4. Delete Book\n";
        cout << "5. Save and Exit\n";
        cout << "Enter your choice: ";

        cin >> choice;

        // Handle invalid input
        while (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between 1 and 5: ";
            cin >> choice;
        }

        // Clear the input buffer before using getline
        cin.ignore(); // Ignore the newline character left by cin >> choice

        switch (choice) {
            case 1:
                addBook(books);
                break;
            case 2:
                displayBooks(books);
                break;
            case 3:
                searchBook(books);
                break;
            case 4:
                deleteBook(books);
                break;
            case 5:
                saveToFile(books, filename);
                cout << "Exiting the program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}

