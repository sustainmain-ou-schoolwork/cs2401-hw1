#include "checkbook.h"
using namespace std;


// default constructor
Checkbook::Checkbook() {
    used = 0;
    nextCheckNum = 1;
    balance = 0;
}

// modifier
void Checkbook::write_check(std::istream& ins) {

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