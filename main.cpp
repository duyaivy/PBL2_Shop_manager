#include "person.h"
#include <iostream>
int person::nextID = 1;  // Start IDs from 1

int main() {
    person person1("John Doe", "123456789", "john@example.com", "password123");
    person person2("Jane Smith", "987654321", "jane@example.com", "password456");

    // Display details of all persons
    // std::cout << "Displaying all persons:" << std::endl;
    person1.display();

    return 0;
}
