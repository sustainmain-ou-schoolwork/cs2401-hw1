#ifndef CHECKBOOK_H
#define CHECKBOOK_H

#include <fstream>
#include <iostream>
#include <string>
#include "check.h"

class Checkbook {
    public:
        // constructor
        Checkbook();

        static const size_t SIZE = 200;  // max number of checks allowed

        // accessor
        int get_balance() const {return balance;}

        // modifier
        void deposit(size_t amount) {balance += amount;}
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
        void show(std::string payto_query) const;
        double average() const;

    private:
        Check checks[SIZE];   // array of all the checks
        size_t used;          // number of checks used
        size_t nextCheckNum;  // number of next available check
        int balance;          // balance of the account

        // helper functions
        void clearNewlines(std::istream& ins);
};

#endif