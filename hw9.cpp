#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <cstdio>
#pragma warning(disable: 4996)
using namespace std;

/****************** Forward Declarations ******************/
class container;
class person;
class athlete;
class student;

void branching(char c, container** pointerToHead);  // given
char* get_name();           // given
void printFirst(container* root);         // given
void printPerson(person* c); // prints person after found using search 
int insertion(container** pointerToHead);     // Question 2
person* search(container* root, char* sname);     // Question 3
void deleteAll(container** pointerToHead);    // Question 4
void printAll(container* root);       // Question 5
void deleteOne(container** pointerToHead);    // Question 4



// A class for nodes of the linked list. 
class container {
    public:
        person *plink;  // points to a person object
        container *next;

        container(){
            plink = NULL;
            next = NULL;
        }
};


// A class to hold attributes of a person
class person {
    public: 
        char *name;
        char *email;
        int phone;

        // constructor that uses the parameters to initialize the class properties
        person(char *cName, int iPhone, char *cEmail) {     
            name = new (char[32]);  // acquiring memory for storing name
            email = new (char[32]);   // acquiring memory for storing email
            phone = iPhone;     // initialize phone
            strcpy(name, cName);    // initialize name
            strcpy(email, cEmail);  // initialize email
        };

        /*deletes memory created in constructor */
        virtual ~person() {       
            /*char 32 is array? */
            delete[] name;
            delete[] email;
        }

        virtual void display() {
            cout << "Name: " << name << endl;
            cout << "Phone: " << phone << endl;
            cout << "Email: " << email << endl;
        }
};

class student: public person {
    public: 
        char *program;
        double gpa;

        student(char *cName, int iPhone, char *cEmail, char *cProgram, double cGpa)
            : person(cName, iPhone, cEmail) {
                program = new (char[32]);
                strcpy(program, cProgram);
                gpa = cGpa;
            }

        virtual  ~student() {
            delete[] program;
        }

        void display() {
            person::display();
            cout << "Program: " << program << endl;
            cout << "GPA: " << gpa << endl;
        }
};

class athlete: public student {
    public: 
        char *sport;

        athlete(char *cName, int iPhone, char *cEmail, char *cSport, char *cProgram, double cGpa)
            : student(cName, iPhone, cEmail, cProgram, cGpa)	{
                sport = new (char[32]);
                strcpy(sport, cSport); // initialize sport
            };

        virtual ~athlete() {       
            delete[] sport;
        }

        void display() {
            student::display();
            cout << "Sport: " << sport << endl;
        }
};

int insertion(container** pointerToHead) {
    container** head;
    head = pointerToHead;
    container* c = new container();  
    char nName[32], nEmail[32], nProgram[32], nSport[32], option;
    int nPhone;
    double nGpa; 
    person *p;

    cout << "Is this a (s)tudent, an (a)thlete, or just a regular (p)erson?:\n";
    cin >> option;
    if(option == 'a') {
        cout << "Enter athlete information:\n";
        cout << "Name:\n";
        cin >> nName;    
        cout << "Phone:\n";
        cin >> nPhone;
        cout << "Email:\n";
        cin  >> nEmail; 
        cout << "Sport:\n";
        cin >> nSport;    
        cout << "Program:\n";
        cin >> nProgram;
        cout << "GPA:\n";
        cin  >> nGpa; 

        p = new athlete(nName, nPhone, nEmail, nSport, nProgram, nGpa); 
    }
    else if(option == 's') {
        cout << "Enter Student information:\n";
        cout << "Name:\n";
        cin >> nName;    
        cout << "Phone:\n";
        cin >> nPhone;
        cout << "Email:\n";
        cin  >> nEmail; 
        cout << "Program:\n";
        cin >> nProgram;
        cout << "GPA:\n";
        cin  >> nGpa; 

        p = new student(nName, nPhone, nEmail, nProgram, nGpa); 
    }
    else if(option == 'p') {
        cout << "Enter Person information:\n";
        cout << "Name:\n";
        cin >> nName;    
        cout << "Phone:\n";
        cin >> nPhone;
        cout << "Email:\n";
        cin  >> nEmail; 

        p = new person(nName, nPhone, nEmail); 
    } else {
        cout << "that's not an option!";
        return 0;
    }


    // put person in container
    c->plink = p;
    // check if list is empty
    if(!*head) {
        *head = c;
    }
    else {
        container *current, *previous;
        current = previous = *head;
        while (current) {
            if (strcmp(c->plink->name, current->plink->name) >= 0) {
                if (current == *head) {
                    *head = c;
                } else {
                    previous->next = c;
                }
                c->next = current;
                break;
            } else if (!current->next) {
                current->next = c;
                c->next = NULL;
                break;
            }

            previous = current;
            current = current->next;

        }
    }
    return 0;
}

/*Find's a person based on their name */
person* search(container* root, char* sname) {
    if(sname) {
        if(root) { 
            container* c = new container();  
            c = root;

            while(c) {
                if(strcmp(sname, c->plink->name) == 0) {
                    c->plink->display();
                    break;  
                }
                c = c->next;
            }
            if (c) {
                return c->plink;
            } else {
                return NULL;
            }
        }
    }
    return NULL;
}

/*delete the first node in the linked list. Ensuring no memory is being leaked.
 * i.e. deleting all of the heap memory that was created for that node */
void deleteOne(container** pointerToHead) {
    if(*pointerToHead) {
        container* c;
        c = *pointerToHead;
        *pointerToHead = c->next;
        delete c->plink;
        delete c;
    }
}

/* using recursion we delete the last node in the list first
 * then recursively we delete all the others. */
void deleteAll(container** pointerToHead) {
    if(*pointerToHead) {
        deleteAll(&(*pointerToHead)->next);
        /* this delete causes the destroy person fucntion to be called.
         * which in turn deletes name and email which somehow causes an
         * error... */
        delete (*pointerToHead)->plink;
        (*pointerToHead)->plink = NULL;
        delete *pointerToHead;
        *pointerToHead = NULL;
    }
    /* head is null here */
}

/*recursively print all items in container until null pointer reached */
void printAll(container* root) {
    if (root) {
        printAll(root->next);
        printPerson(root->plink);
    }
}

void printPerson(person* c) {
    if(c) {
        cout << "For security reasons, we only display public information:\n";
        cout << "\n\nname = " << c->name << endl;
        cout << "phone = " << c->phone << endl;
        cout << "email = " << c->email << endl;
    }
}

void printFirst(container* root)
{
    if (root != NULL)
    {
        cout << "\n\nname = " << root->plink->name << endl;
        cout << "phone = " << root->plink->phone << endl;
        cout << "email = " << root->plink->email << endl;
    }
}

void flush() {  // flush the input buffer. To be discussed later
    int c;
    do {
        c = cin.get();
    } while (c != '\n' && c != EOF);
}

int main()
{
    container* head = NULL; // Declare head as a local variable of main function
    // Print a menu for selection
    char ch = 'z';
    do {
        if (ch != 'z') {
            flush();
        }
        cout<< "Enter your selection" << endl;
        cout<< "\ti: insert a new entry" << endl;
        cout<< "\tr: delete all entries" << endl;
        cout<< "\td: delete first entry only" << endl;
        cout<< "\ts: search an entry" << endl;
        cout<< "\tp: print all entries" << endl;
        cout<< "\tq: quit" << endl;
        cin >> ch;
        //scanf("%c", &ch);
        //flush();
        ch = tolower(ch); // Convert any uppercase char to lowercase.
        branching(ch, &head);
        cout << endl;
    } while (ch != 'q');
    return 0;
}
// Branch to different tasks: insert a person, search for a person, delete a person
// print all added persons.
void branching(char c, container** pointerToHead)
{
    class person *pp; 
    char *p;
    switch (c) {
        case 'i':
            insertion(pointerToHead);
            break;
        case 's':
            p = get_name();
            pp = search(*pointerToHead, p);
            break;
        case 'r':
            deleteAll(pointerToHead);
            break;
        case 'd':
            deleteOne(pointerToHead);
            break;
        case 'p':
            printAll(*pointerToHead);
            break;
        case 'q':
            deleteAll(pointerToHead); // free all memory
            break;
        default:
            cout <<"Invalid input\n";
    }
}
// Read the input from the user.
char * get_name()
{
    char *p = new(char[32]); // Use dynamic memory which does not go out of scope
    cout << "Please enter a name for the search: " <<endl;
    cin >> p;
    return p;
}
