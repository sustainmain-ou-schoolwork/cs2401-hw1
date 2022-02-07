#include "checkbook.h"
using namespace std;


Checkbook::Checkbook() {
    used = 0;
    nextCheckNum = 1;
    balance = 0;
}


// modifier

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
    for (size_t i = 0; i < used; i++) {
        cout << '\n' << checks[i] << endl;
    }
}

void Checkbook::show(std::string payto_query) const {
    for (size_t i = 0; i < used; i++) {
        // if the check matches the query
        if (checks[i].get_payto() == payto_query) {
            cout << '\n' << checks[i] << endl;
        }
    }
}

double Checkbook::average() const {
    double total = 0;
    for (size_t i = 0; i < used; i++) {
        total += checks[i].get_amount();
    }

    return total / used;
}


// helper

void Checkbook::clearNewlines(std::istream& ins) {
    while (ins.peek() == '\n' || ins.peek() == '\r') {
        ins.ignore();
    }
}

std::string Checkbook::stringToUpper(std::string input) const {
    string output = "";
    for (size_t i = 0; i < input.length(); i++) {
        output += toupper(input.at(i));
    }

    return output;
}