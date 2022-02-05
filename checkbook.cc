#include "checkbook.h"
using namespace std;


// default constructor
Checkbook::Checkbook() {
    used = 0;
    nextCheckNum = 1;
    balance = 0;
}

// modifier

/**
 * @brief Adds a check to the checkbood.
 * 
 * @param ins stream to read check data from
 */
void Checkbook::write_check(std::istream& ins) {
    if (used >= SIZE) {
        cout << "Checkbook is full." << endl;
        return;
    }

    // create a check
    Check tmp;
    tmp.write_check(ins);

    // set the check number if it wasn't previously set
    if (&ins == &cin) {
        tmp.set_check_num(used);
    }

    // add the check to the checkbook
    checks[used] = tmp;
    used++;
    nextCheckNum++;
}

void Checkbook::remove(size_t checkNum) {

}

// sorter
void Checkbook::number_sort() {

}

void Checkbook::payto_sort() {

}

void Checkbook::date_sort() {

}

// file operation
void Checkbook::load_from_file(std::ifstream& fileStream) {

}

void Checkbook::save(std::ofstream& fileStream) const {

}

// display or calculate info
void Checkbook::show_all(std::ostream& outs) const {

}

void Checkbook::show(std::string payto_query) const {

}

/**
 * @brief Returns the average amount of all checks in the checkbook.
 * 
 * @return the average
 */
double Checkbook::average() const {
    int total = 0;
    for (size_t i = 0; i < used; i++) {
        total += checks[i].get_amount();
    }

    return total / used;
}

/**
 * @brief Clears out any newline characters at the beginning of the stream
 * 
 * @param ins the stream to be cleared of newlines
 */
void Checkbook::clearNewlines(std::istream& ins) {
    while (cin.peek() == '\n' || cin.peek() == '\r') {
        cin.ignore();
    }
}