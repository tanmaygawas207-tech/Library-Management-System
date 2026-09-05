#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class Book
{
public:
    int bookId;
    string title;
    string author;
    bool issued;
    int memberId;
};

class Member
{
public:
    int memberId;
    string name;
};

vector<Book> books;
vector<Member> members;

// Save books
void saveBooks()
{
    ofstream file("books.txt");

    if (!file.is_open())
        return;

    for (int i = 0; i < books.size(); i++)
    {
        file << books[i].bookId << endl;
        file << books[i].title << endl;
        file << books[i].author << endl;
        file << books[i].issued << endl;
        file << books[i].memberId << endl;
    }

    file.close();
}

// Load books
void loadBooks()
{
    ifstream file("books.txt");

    if (!file.is_open())
        return;

    Book b;

    while (file >> b.bookId)
    {
        file.ignore();

        getline(file, b.title);
        getline(file, b.author);

        file >> b.issued;
        file >> b.memberId;
        file.ignore();

        books.push_back(b);
    }

    file.close();
}

// Save members
void saveMembers()
{
    ofstream file("members.txt");

    if (!file.is_open())
        return;

    for (int i = 0; i < members.size(); i++)
    {
        file << members[i].memberId << endl;
        file << members[i].name << endl;
    }

    file.close();
}

// Load members
void loadMembers()
{
    ifstream file("members.txt");

    if (!file.is_open())
        return;

    Member m;

    while (file >> m.memberId)
    {
        file.ignore();
        getline(file, m.name);

        members.push_back(m);
    }

    file.close();
}

// Find book
int findBook(int id)
{
    for (int i = 0; i < books.size(); i++)
    {
        if (books[i].bookId == id)
            return i;
    }

    return -1;
}

// Find member
int findMember(int id)
{
    for (int i = 0; i < members.size(); i++)
    {
        if (members[i].memberId == id)
            return i;
    }

    return -1;
}

// Check duplicate book ID
bool bookExists(int id)
{
    return findBook(id) != -1;
}

// Check duplicate member ID
bool memberExists(int id)
{
    return findMember(id) != -1;
}

// Add Book
void addBook()
{
    Book b;

    cout << "\n========== ADD BOOK ==========\n";

    cout << "Enter Book ID: ";
    cin >> b.bookId;

    if (bookExists(b.bookId))
    {
        cout << "\nBook ID already exists!\n";
        return;
    }

    cin.ignore();

    cout << "Enter Book Title: ";
    getline(cin, b.title);

    cout << "Enter Author Name: ";
    getline(cin, b.author);

    b.issued = false;
    b.memberId = 0;

    books.push_back(b);

    saveBooks();

    cout << "\nBook added successfully!\n";
}

// Display Books
void displayBooks()
{
    cout << "\n========== BOOK RECORDS ==========\n";

    if (books.empty())
    {
        cout << "\nNo books found!\n";
        return;
    }

    for (int i = 0; i < books.size(); i++)
    {
        cout << "\n--------------------------------";
        cout << "\nBook ID : " << books[i].bookId;
        cout << "\nTitle   : " << books[i].title;
        cout << "\nAuthor  : " << books[i].author;

        if (books[i].issued)
            cout << "\nStatus  : Issued";
        else
            cout << "\nStatus  : Available";

        cout << "\n--------------------------------";
    }
}

// Add Member
void addMember()
{
    Member m;

    cout << "\n========== ADD MEMBER ==========\n";

    cout << "Enter Member ID: ";
    cin >> m.memberId;

    if (memberExists(m.memberId))
    {
        cout << "\nMember ID already exists!\n";
        return;
    }

    cin.ignore();

    cout << "Enter Member Name: ";
    getline(cin, m.name);

    members.push_back(m);

    saveMembers();

    cout << "\nMember added successfully!\n";
}

// Display Members
void displayMembers()
{
    cout << "\n========== MEMBER RECORDS ==========\n";

    if (members.empty())
    {
        cout << "\nNo members found!\n";
        return;
    }

    for (int i = 0; i < members.size(); i++)
    {
        cout << "\n--------------------------------";
        cout << "\nMember ID : " << members[i].memberId;
        cout << "\nName      : " << members[i].name;
        cout << "\n--------------------------------";
    }
}

// Issue Book
void issueBook()
{
    int bookId;
    int memberId;

    cout << "\n========== ISSUE BOOK ==========\n";

    cout << "Enter Book ID: ";
    cin >> bookId;

    int bookIndex = findBook(bookId);

    if (bookIndex == -1)
    {
        cout << "\nBook not found!\n";
        return;
    }

    if (books[bookIndex].issued)
    {
        cout << "\nBook is already issued!\n";
        return;
    }

    cout << "Enter Member ID: ";
    cin >> memberId;

    if (findMember(memberId) == -1)
    {
        cout << "\nMember not found!\n";
        return;
    }

    books[bookIndex].issued = true;
    books[bookIndex].memberId = memberId;

    saveBooks();

    cout << "\nBook issued successfully!\n";
}

// Return Book
void returnBook()
{
    int bookId;

    cout << "\n========== RETURN BOOK ==========\n";

    cout << "Enter Book ID: ";
    cin >> bookId;

    int bookIndex = findBook(bookId);

    if (bookIndex == -1)
    {
        cout << "\nBook not found!\n";
        return;
    }

    if (!books[bookIndex].issued)
    {
        cout << "\nBook is not currently issued!\n";
        return;
    }

    books[bookIndex].issued = false;
    books[bookIndex].memberId = 0;

    saveBooks();

    cout << "\nBook returned successfully!\n";
}

// Search by Title
void searchByTitle()
{
    string title;
    bool found = false;

    cout << "\n========== SEARCH BY TITLE ==========\n";

    cin.ignore();

    cout << "Enter Book Title: ";
    getline(cin, title);

    for (int i = 0; i < books.size(); i++)
    {
        if (books[i].title == title)
        {
            cout << "\nBook Found!";
            cout << "\nBook ID : " << books[i].bookId;
            cout << "\nTitle   : " << books[i].title;
            cout << "\nAuthor  : " << books[i].author;

            if (books[i].issued)
                cout << "\nStatus  : Issued\n";
            else
                cout << "\nStatus  : Available\n";

            found = true;
        }
    }

    if (!found)
        cout << "\nBook not found!\n";
}

// Search by Author
void searchByAuthor()
{
    string author;
    bool found = false;

    cout << "\n========== SEARCH BY AUTHOR ==========\n";

    cin.ignore();

    cout << "Enter Author Name: ";
    getline(cin, author);

    for (int i = 0; i < books.size(); i++)
    {
        if (books[i].author == author)
        {
            cout << "\nBook Found!";
            cout << "\nBook ID : " << books[i].bookId;
            cout << "\nTitle   : " << books[i].title;
            cout << "\nAuthor  : " << books[i].author;

            if (books[i].issued)
                cout << "\nStatus  : Issued\n";
            else
                cout << "\nStatus  : Available\n";

            found = true;
        }
    }

    if (!found)
        cout << "\nNo books found by this author!\n";
}

// Main Function
int main()
{
    loadBooks();
    loadMembers();

    int choice;

    do
    {
        cout << "\n\n==========================================";
        cout << "\n        LIBRARY MANAGEMENT SYSTEM";
        cout << "\n==========================================";
        cout << "\n1. Add Book";
        cout << "\n2. Display Books";
        cout << "\n3. Add Member";
        cout << "\n4. Display Members";
        cout << "\n5. Issue Book";
        cout << "\n6. Return Book";
        cout << "\n7. Search Book by Title";
        cout << "\n8. Search Book by Author";
        cout << "\n9. Exit";
        cout << "\n==========================================";

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addBook();
            break;

        case 2:
            displayBooks();
            break;

        case 3:
            addMember();
            break;

        case 4:
            displayMembers();
            break;

        case 5:
            issueBook();
            break;

        case 6:
            returnBook();
            break;

        case 7:
            searchByTitle();
            break;

        case 8:
            searchByAuthor();
            break;

        case 9:
            cout << "\nThank you for using Library Management System!\n";
            break;

        default:
            cout << "\nInvalid choice! Please try again.\n";
        }

    } while (choice != 9);

    return 0;
}
