 
#include <iostream>
#include <string>
#include <limits>   

using namespace std;

struct BookNode{
    string title;
    string author;
    int publishYear;
    string isbn;
    BookNode* next;     

};

BookNode* head = nullptr;



void addBook();
void deleteBook();
void searchBookByISBN();
void listAllBooks();
void deleteAllBooks();
bool isISBNExists(const string& isbn_to_check);


int main() {
    int choice;
    do {
        
        cout << "\n------********* Library Management System ******----------" << endl;
        cout << "1. Add Book" << endl;
        cout << "2. Delete Book" << endl;
        cout << "3. Search Book by ISBN" << endl;
        cout << "4. List All Books" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";


        cin >> choice;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                
                deleteBook();
                break;
            case 3:
                
                searchBookByISBN();
                break;
            case 4:
                
                listAllBooks();
                break;
            case 5:
                
                deleteAllBooks();
                cout << "Exiting program. Memory cleared." << endl;
                break;
            default:
                
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 5); 

    return 0;
}


bool isISBNExists(const string& isbn_to_check) {
    BookNode* current = head;
    while (current != nullptr) {
        if (current->isbn == isbn_to_check) {
            return true; 
        }
        current = current->next;
    }
    return false; 
}


void addBook() {
    string isbn;

    cout << "Enter ISBN code: ";
    getline(cin, isbn);

    
    if (isISBNExists(isbn)) {
        cout << "Error: Book with ISBN " << isbn << " already exists. Book not added." << endl;
        return; 
    }

    
    BookNode* newNode = new BookNode;

    newNode->isbn = isbn; 

    cout << "Enter Title: ";
    getline(cin, newNode->title);

    cout << "Enter Author: ";
    getline(cin, newNode->author);

    cout << "Enter Publish Year: ";
    cin >> newNode->publishYear;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    newNode->next = nullptr;

    
    if (head == nullptr) {
        
        head = newNode;
    } else {
        
        BookNode* temp = head; 
        while (temp->next != nullptr) {
            temp = temp->next; 
        }
        
        temp->next = newNode;
    }

    cout << "Book with ISBN " << isbn << " added successfully!" << endl;
}

void deleteBook() {
    // Check if the list is empty
    if (head == nullptr) {
        cout << "No books to delete (library is empty)." << endl;
        return; 
    }

    int criteria_choice;
    cout << "Delete by:\n1. ISBN\n2. Title\nEnter choice (1 or 2): ";
    cin >> criteria_choice;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');


    string search_criteria; 

    if (criteria_choice == 1) {
        cout << "Enter ISBN of the book to delete: ";
        getline(cin, search_criteria);
    } else if (criteria_choice == 2) {
        cout << "Enter Title of the book to delete: ";
        getline(cin, search_criteria);
    } else {
        cout << "Invalid deletion criteria choice." << endl;
        return; 
    }

    
    BookNode* current = head;
    BookNode* previous = nullptr;
    bool found = false; 

    
    while (current != nullptr) {
        bool match = false;
        if (criteria_choice == 1 && current->isbn == search_criteria) {
            match = true; 
        } else if (criteria_choice == 2 && current->title == search_criteria) {
            match = true; 
        }

        if (match) {
            found = true; 
            
            if (previous == nullptr) {
                head = current->next; 
            } else {
                
                previous->next = current->next; 
            }

           
            string deleted_title = current->title;
            string deleted_isbn = current->isbn;

            delete current;
            cout << "Book \"" << deleted_title << "\" (ISBN: " << deleted_isbn << ") deleted successfully!" << endl;

           
            if (criteria_choice == 1 || criteria_choice == 2) {
                return;
            }

        } else {
            
             previous = current; 
             current = current->next; 
        }
    }

    
    if (!found) {
         if (criteria_choice == 1) {
            cout << "Book with ISBN " << search_criteria << " not found!" << endl;
         } else if (criteria_choice == 2) {
            cout << "Book with Title \"" << search_criteria << "\" not found!" << endl;
         }
    }
}


void searchBookByISBN() {
    
    if (head == nullptr) {
        cout << "No books available to search (library is empty)." << endl;
        return; 
    }

    string isbn_to_find; 
    cout << "Enter ISBN of the book to find: ";
    
    getline(cin, isbn_to_find);

    
    BookNode* current = head;

    
    while (current != nullptr) {
        if (current->isbn == isbn_to_find) {
            
            cout << "\n--- Book Found ---" << endl;
            cout << "Title: " << current->title << endl;
            cout << "Author: " << current->author << endl;
            cout << "Publish Year: " << current->publishYear << endl;
            cout << "ISBN: " << current->isbn << endl;
            cout << "------------------" << endl;
            return; 
        }
        
        current = current->next;
    }

    
    cout << "Book with ISBN " << isbn_to_find << " not found!" << endl;
}


void listAllBooks() {
    // Check if the list is empty
    if (head == nullptr) {
        cout << "No books to display (library is empty)." << endl;
        return; 
    }

    
    cout << "\n===== All Books in the Library =====" << endl;
    cout << "-------------------------------------------------------------------" << endl;
    

    BookNode* current = head; 
    int count = 0; 

    
    while (current != nullptr) {
        // Print the details of the current book
        cout << "Book " << (count + 1) << ":" << endl;
        cout << "  ISBN: " << current->isbn << endl;
        cout << "  Title: " << current->title << endl;
        cout << "  Author: " << current->author << endl;
        cout << "  Publish Year: " << current->publishYear << endl;
        cout << "-------------------------------------------------------------------" << endl;


        current = current->next;
        count++; 
    }

    cout << "Total Books: " << count << endl;
}


void deleteAllBooks() {
    BookNode* current = head; 
    BookNode* nextNode;       

    
    while (current != nullptr) {
        nextNode = current->next; 
        delete current;           
        current = nextNode;       
    }
    
    head = nullptr;
    cout << "Memory cleared for all books." << endl; 
}