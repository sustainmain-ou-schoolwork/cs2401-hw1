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

    // only add the check if all the data was read successfully
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

/**
 * @brief Remove a check from the checkbood.
 * 
 * @param checkNum number of the check to remove
 */
void Checkbook::remove(size_t checkNum) {
    for (size_t i = 0; i < used; i++) {
        // if the check at i is the one to remove
        if (static_cast<size_t>(checks[i].get_num()) == checkNum) {
            // move all the remaining checks up one place in the checkbook, effectively deleting the last
            for (size_t j = i; j < (used - 1); j++) {
                checks[j] = checks[j + 1];
            }

            // set the last element of the checkbook to an empty check
            Check tmp;
            checks[used - 1] = tmp;
            
            // decrement counters
            used--;
            nextCheckNum--;
        }
    }
}


// sorter

/**
 * @brief Sort the checks in the checkbook by check number.
 */
void Checkbook::number_sort() {
    bool done = false;
    size_t i;
    Check tmp;

    // bubble sort
    while (!done) {
        done = true;
        for (i = used - 1; i > 0; --i) {
            if (checks[i].get_num() < checks[i - 1].get_num()) {
                done = false;
                tmp = checks[i];
                checks[i] = checks[i - 1];
                checks[i - 1] = tmp;
            }
        }
    }
}

/**
 * @brief Sort the checks in the checkbook by payto value.
 */
void Checkbook::payto_sort() {
    bool done = false;
    size_t i;
    Check tmp;

    // bubble sort
    while (!done) {
        done = true;
        for (i = used - 1; i > 0; --i) {
            if (stringToUpper(checks[i].get_payto()) < stringToUpper(checks[i - 1].get_payto())) {
                done = false;
                tmp = checks[i];
                checks[i] = checks[i - 1];
                checks[i - 1] = tmp;
            }
        }
    }
}

/**
 * @brief Sort the checks in the checkbook by date.
 */
void Checkbook::date_sort() {
    bool done = false;
    size_t i;
    Check tmp;

    // bubble sort
    while (!done) {
        done = true;
        for (i = used - 1; i > 0; --i) {
            if (checks[i].get_date() < checks[i - 1].get_date()) {
                done = false;
                tmp = checks[i];
                checks[i] = checks[i - 1];
                checks[i - 1] = tmp;
            }
        }
    }
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

/**
 * @brief Outputs the checkbook data of all checks.
 * 
 * @param outs the stream to output the data to
 */
void Checkbook::show_all(std::ostream& outs) const {
    for (size_t i = 0; i < used; i++) {
        cout << '\n' << checks[i] << endl;
    }
}

/**
 * @brief Outputs the checkbook data of all checks that have a given payto value.
 * 
 * @param payto_query the payto value to search for
 */
void Checkbook::show(std::string payto_query) const {
    for (size_t i = 0; i < used; i++) {
        // if the check matches the query
        if (checks[i].get_payto() == payto_query) {
            cout << '\n' << checks[i] << endl;
        }
    }
}

/**
 * @brief Returns the average amount of all checks in the checkbook.
 * 
 * @return the average
 */
double Checkbook::average() const {
    double total = 0;
    for (size_t i = 0; i < used; i++) {
        total += checks[i].get_amount();
    }

    return total / used;
}


// helper

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

/**
 *  @brief Converts an entire string to uppercase.
 * 
 *  @param input the string to be converted
 *  @return the string in uppercase
 */
std::string Checkbook::stringToUpper(std::string input) const {
    string output = "";
    for (size_t i = 0; i < input.length(); i++) {
        output += toupper(input.at(i));
    }

    return output;
}