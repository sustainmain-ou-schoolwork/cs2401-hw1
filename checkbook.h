#ifndef CHECKBOOK_H
#define CHECKBOOK_H

#include <iostream>
#include <string>
#include "check.h"

class Checkbook {
    public:
        static const size_t SIZE = 200;  // max number of checks allowed

        // accessor
        int get_balance() const {return balance;}

        // modifier
        void deposit(size_t amount);
        void write_check(std::istream& ins);
        void remove(size_t checkNum);

        // sorter
        void number_sort();
        void payto_sort();
        void date_sort();

        // file operation
        void load_from_file(std::ifstream& fileStream);
        void save(std::ofstream& fileStream) const;

        // display or calculate info
        void show_all(std::ostream& outs) const;
        void show(string payto_query) const;
        size_t average() const;

    private:
        size_t checks[SIZE];  // array of all the checks
        size_t used;          // number of checks used
        size_t nextCheckNum;  // number of next available check
        int balance;          // balance of the account
};

#endif