#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Book {
  int id;
  string title;
  string author;
  int quantity;
};

const int M_books = 100; 
Book books[M_books];
int numBooks = 0;

void Bookdetails(const Book& book) {
  cout << "Book ID: " << book.id << endl;
  cout << "Title of book: " << book.title << endl;
  cout << "Author of book: " << book.author << endl;
  cout << "Quantity of book: " << book.quantity << endl << endl;
}

void AddBooks() {
  if (numBooks == M_books) {
    cout << "Library is full. You cannot add more books." << endl;
    return;
  }

  cout << "Enter Book ID: ";
  cin >> books[numBooks].id;

  cout << "Enter Book Title: ";
  cin.ignore(); 
  getline(cin, books[numBooks].title);

  cout << "Enter Book Author: ";
  getline(cin, books[numBooks].author);

  cout << "Enter Book Quantity: ";
  cin >> books[numBooks].quantity;

  numBooks++;

  cout << "Book added successfully!" << endl;
}

int booksId(int id) {
  for (int i = 0; i < numBooks; i++) {
    if (books[i].id == id) {
      return i;
    }
  }
  return -1;
}

int bookstitle(const string& title) {
  for (int i = 0; i < numBooks; i++) {
    if (books[i].title == title) {
      return i;
    }
  }
  return -1;
}

void AllBooks() {
  if (numBooks == 0) {
    cout << "No books found in the library." << endl;
    return;
  }

  cout << "Available Books:\n";
  for (int i = 0; i < numBooks; i++) {
    Bookdetails(books[i]);
  }
}

void LoadBooksFromFile(const string& filename) {
  ifstream file(filename);

  if (!file.is_open()) {
    cout << "Error opening file!" << endl;
    return;
  }

  int id;
  string title, author;
  int quantity;

  while (file >> id) {
    cin.ignore();
    getline(file, title);
    getline(file, author);
    file >> quantity;

    if (numBooks < M_books) {
      books[numBooks].id = id;
      books[numBooks].title = title;
      books[numBooks].author = author;
      books[numBooks].quantity = quantity;
      numBooks++;
    }
  }

  file.close();
}

void SaveBooksToFile(const string& filename) {
  ofstream file(filename);

  if (!file.is_open()) {
    cout << "Error opening file!" << endl;
    return;
  }

  for (int i = 0; i < numBooks; i++) {
    file << books[i].id << " " << books[i].title << " " << books[i].author << " " << books[i].quantity << endl;
  }

  file.close();
  cout << "Books saved successfully!" << endl;
}

int main() {
  LoadBooksFromFile("books.txt");

  int choice;

  do {
    cout << "\nLibrary Management System\n";
    cout << "1. Add a Book\n";
    cout << "2. Search for a Book\n";
    cout << "3. Display All Books\n";
    cout << "4. Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
      case 1:
        AddBooks();
        break;
      case 2: {
        int searchId;
        string searchTitle;

        cout << "Search by ID (1) or Title (2)? ";
        int searchType;
        cin >> searchType;

        if (searchType == 1) {
          cout << "Enter Book ID: ";
          cin >> searchId;
          int index = booksId(searchId);
          if (index != -1) {
            Bookdetails(books[index]);
          } else {
            cout << "Book not found." << endl;
          }
        } else if (searchType == 2) {
          cout << "Enter Book Title: ";
          cin.ignore();
          getline(cin, searchTitle);
          int index = bookstitle(searchTitle);
          if (index != -1) {
            Bookdetails(books[index]);
          } else {
            cout << "Book not found." << endl;
          }
        } else {
          cout << "Invalid search type." << endl;
        }
        break;
      }
      case 3:
        AllBooks();
        break;
      case 4:
        cout << "Exiting..." << endl;
        break;
      default:
        cout << "Invalid choice." << endl;
    }
  } while (choice != 4);

  SaveBooksToFile("books.txt");

  return 0;
}