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

    // create a check and set values
    Check tmp;
    ins >> tmp;

    // only add the check if all the data was read s
    if (!ins.fail()) {
        // if input is from console
        if (&ins == &cin) {
            // set the check number
            tmp.set_check_num(nextCheckNum);
            nextCheckNum++;

            // subtract check amount from balance
            balance -= tmp.get_amount();
        }

        // add the check to the checkbook
        checks[used] = tmp;
        used++;
    }
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

/**
 * @brief Loads the checkbook data from an ostream.
 * 
 * @param fileStream the stream to read checkbook data from
 */
void Checkbook::load_from_file(std::ifstream& fileStream) {
    string lineIn;

    // get account info
    getline(fileStream, lineIn);
    balance = stod(lineIn);
    fileStream >> nextCheckNum;
    clearNewlines(fileStream);

    // get individual checks
    while (!fileStream.fail()) {
        write_check(fileStream);
    }
}

/**
 * @brief Outputs the checkbook data to an ostream.
 * 
 * @param fileStream the stream to output checkbook data to
 */
void Checkbook::save(std::ofstream& fileStream) const {
    fileStream << balance << '\n';
    fileStream << nextCheckNum << '\n';
    
    for (size_t i = 0; i < used; i++) {
        fileStream << checks[i];
    }
    
    fileStream << flush;
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
    while (ins.peek() == '\n' || ins.peek() == '\r') {
        ins.ignore();
    }
}