// Section 11
// Challenge 
/*
     Recall the challenge from Section 9 below.
    Your challenge for section 11 is to modularize your solution to the Section 9
    challenge by refactoring your solution so that it uses uses functions.
    
    You decide how to modularize the program.
    you can use my solution which is included in this file, or modularize your solution.
    
    Here are a few hints:
        - Create functions for each major function
        - Keep the functions small
        - Remember the Boss/Worker analogy
        - Keep the vector declaration in the main function and pass the vector object
          to any function that requires it

        DO NOT move the vector object outside main and make it a global variable.
    
        - You can start by defining a function that displays the menu
        - You can then define a function that reads the selection from the user and returns it in uppercase
        - Create functions for each menu option
        - Create functions that display the list of numbers, calculates the mean and so forth
        
    Take it one function at a time and take your time.
    If you get frustrated, take a break -- this isn't as easy as it looks the first time you do it!
    
    Finally,  don't forget to use function prototypes!
    
    Good luck -- I know you can do it!
*/
/*    
    This challenge is about using a collection (list) of integers and allowing the user
    to select options from a menu to perform operations on the list.
    
    Your program should display a menu options to the user as follows:
    
    P - Print numbers
    A - Add a number
    M - Display mean of the numbers
    S - Display the smallest number
    L - Display the largest number
    Q - Quit

    Enter your choice:
    
The program should only accept valid choices from the user, both upper and lowercase selections should be allowed.
If an illegal choice is made, you should display, "Unknown selection, please try again" and the menu options should be
displayed again.


If the user enters 'P' or 'p', you should display all of the elements (ints) in the list.
If the list is empty you should display "[] - the list is empty"
If the list is not empty then all the list element should be displayed inside square brackets separated by a space. 
For example, [ 1 2 3 4 5 ]
      
If the user enters 'A' or 'a' then you should prompt the user for an integer to add to the list 
which you will add to the list and then display it was added. For example, if the user enters 5
You should display, "5 added".
Duplicate list entries are OK

If the user enters 'M' or 'm'  you should calculate the mean or average of the elements in the list and display it.
If the list is empty you should display, "Unable to calculate the mean - no data"

If the user enters 'S' or 's' you should display the smallest element in the list.
For example, if the list contains [2 4 5 1],  you should display, "The smallest number is 1"
If the list is empty you should display, "Unable to determine the smallest number - list is empty"

If the user enters 'L' or 'l' you should display the largest element in the list
For example, if the list contains [2 4 5 1], you should display, "The largest number is 5"
If the list is empty you should display, "Unable to determine the largest number - list is empty"

If the user enters 'Q' or 'q' then you should display 'Goodbye" and the program should terminate.

Before you begin. Write out the steps you need to take and decide in what order they should be done.
Think about what loops you should use as well as what you will use for your selection logic.

This exercise can be challenging! It may likely take a few attempts before you complete it -- that's OK!

Finally, be sure to test your program as you go and at the end.

Hint: Use a vector!

Additional functionality if you wish to extend this program.

- search for a number in the list and if found display the number of times it occurs in the list
- clearing out the list (make it empty again) (Hint: the vector class has a .clear() method)
- don't allow duplicate entries
- come up with your own ideas!

Good luck!

*/
#include <iostream>
#include <vector>

using namespace std;

void print_menu();
bool check_empty_list(const vector<int> &vec);
void clear_list(vector<int> &vec);
void print_list(const vector<int> &vec);
void add_list(vector<int> &vec);
double mean_list(const vector<int> &vec);
int smallest_list(const vector<int> &vec);
int largest_list(const vector<int> &vec);
size_t occurance_list(const vector<int> &vec);



bool check_empty_list(const vector<int> &vec){
    if(vec.empty())
        return true;
    else
        return false;
}

void clear_list(vector<int> &vec){
    if(check_empty_list(vec))
        cout << "List is already empty" <<endl;
    else{
        vec.clear();
        cout << "List is cleared!" << endl;
    }
}

void print_list(const vector<int> &vec){
    if(check_empty_list(vec))
        cout << "List is empty" <<endl;
    else{
        cout << "[";
        for(auto v:vec)
            cout << v << " ";
        cout << "]" << endl;
    }
}

void add_list(vector<int> &vec){
    cout << "Enter an integer to add to the list :";
    int num {};
    cin >> num;
    vec.push_back(num);
}

double mean_list(const vector<int> &vec){
    double mean{0};
    if(check_empty_list(vec))
        cout << "Unable to calculate mean - list is empty" << endl;
    else{
        for(auto v: vec){
            mean += v;
        }
        mean /= static_cast<double>(vec.size());
        cout << "Mean of the list :" << mean << endl;
    }
    return mean;
}

int smallest_list(const vector<int> &vec){
    double smallest{0};
    if(check_empty_list(vec))
        cout << "Unable to calculate smallest - list is empty" << endl;
    else{
        smallest = vec.at(0);
        for(auto v: vec){
            if(v<smallest)
                smallest = v;
        }
        cout << "Smallest of the list :" << smallest << endl;
    }
    return smallest;
}

int largest_list(const vector<int> &vec){
    double largest{0};
    if(check_empty_list(vec))
        cout << "Unable to calculate largest - list is empty" << endl;
    else{
        largest = vec.at(0);
        for(auto v: vec){
            if(v>largest)
                largest = v;
        }
        cout << "largest of the list :" << largest << endl;
    }
    return largest;
}

size_t occurance_list(const vector<int> &vec){
    size_t count{0};
    if(check_empty_list(vec))
        cout << "Unable to find - list is empty" << endl;
    else{
        cout << "Enter an integer to find :" ;
        int num{0};
        cin >> num;
        for(auto v:vec){
            if(v==num)
                ++count;
        }
        cout << num << " occurred " << count << " times" << endl;
    }
    return count;
}

void print_menu(){
    cout << "\nP - Print list" << endl;
    cout << "A - Add a number to list" << endl;
    cout << "C - Clear list" << endl;
    cout << "M - Display mean of the numbers" << endl;
    cout << "S - Display the smallest number" << endl;
    cout << "L - Display the largest number"<< endl;
    cout << "Q - Quit" << endl;
}

int main(){
    char choice{};
    vector<int> vec;
    do{
        print_menu();
        cout << "Enter your choice :";
        cin >> choice;
        choice = tolower(choice);
        if(choice=='p')
            print_list(vec);
        else if(choice=='a')
            add_list(vec);
        else if(choice=='c')
            clear_list(vec);
        else if(choice=='m')
            mean_list(vec);
        else if(choice=='s')
            smallest_list(vec);
        else if(choice=='l')
            largest_list(vec);
        else if(choice=='f')
            occurance_list(vec);
        else if(choice=='q') {
            cout << "Goodbye" << endl;
        } else {
            cout << "Unknown selection, please try again" << endl;
        }
    } while (choice!='q');
    cout << endl;
    return 0;
}