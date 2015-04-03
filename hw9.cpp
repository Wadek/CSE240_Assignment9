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
  person(char *cName, char *cEmail, int iPhone) {     
    name = new (char[32]);  // acquiring memory for storing name
    email = new (char[32]);   // acquiring memory for storing email
    strcpy(name, cName);    // initialize name
    strcpy(email, cEmail);  // initialize email
    phone = iPhone;     // initialize phone
  };

  /*deletes memory created in constructor */
  virtual ~person() {       
    /*char 32 is array? */
    delete[] name;
    delete[] email;
  }
};

class student: public person {
  char *program;
  double gpa;

  student( char *cProgram, double cGpa) {
    program = new (char[32])
    gpa = new (double);
    strcpy(program, cProgram);
  }
  virtual ~student() {
    delete[] program;
    delete gpa;
  }
  virtual display() {
  }
}
  class athlete: public student {
  char *sport;
  
  athlete(char *cSport) {
    sport = new (char[32]);
    strcpy(sport, cSport); // initialize sport
  }
  virtual ~athlete() {       
    delete[] sport;
 }
  virtual display() { 
  }
};


int insertion(container** pointerToHead) {
  container** head;
  head = pointerToHead;
  container* c = new container();  
  char nName[32], nEmail[32];
  int nPhone;

  cout << "Enter name, phone, email:\n";
  cin >> nName >> nEmail >> nPhone;
  person* p = new person(nName, nEmail, nPhone); 
  

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
}

/*Find's a person based on their name */
person* search(container* root, char* sname) {
  if(sname) {
    if(root) { 
      container* c = new container();  
      c = root;
   
      while(c) {
        if(strcmp(sname, c->plink->name) == 0) {
          cout << "Great job, you found who you're looking for!";
          printPerson(c->plink);
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
    cout << "\n\nname = " << c->name << endl;
    cout << "email = " << c->email << endl;
    cout << "phone = " << c->phone << endl;
    }
}

void printFirst(container* root)
{
  if (root != NULL)
  {
    cout << "\n\nname = " << root->plink->name << endl;
    cout << "email = " << root->plink->email << endl;
    cout << "phone = " << root->plink->phone << endl;
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
  char ch;
  do {
    flush();
    cout<< "Enter your selection" << endl;
    cout<< "\ti: insert a new entry" << endl;
    cout<< "\tr: delete all entries" << endl;
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


