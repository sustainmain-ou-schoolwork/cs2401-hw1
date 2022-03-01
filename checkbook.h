#ifndef CHECKBOOK_H
#define CHECKBOOK_H

#include <fstream>
#include <iostream>
#include <string>
#include "check.h"

class Checkbook {
    public:
        // constructor

        /**
         * @brief Construct a new Checkbook object.
         */
        Checkbook();

        static const size_t SIZE = 200;  // max number of checks allowed


        // accessor

        /**
         * @brief Gets the balance of the checkbook.
         * 
         * @return balance of the checkbook
         */
        double get_balance() const {return balance;}


        // modifier

        /**
         * @brief Adds an amount to the balance.
         * 
         * @param amount amount to add
         */
        void deposit(double amount) {balance += amount;}

        /**
         * @brief Adds a check to the checkbood.
         * 
         * @param ins stream to read check data from
         */
        void write_check(std::istream& ins);

        /**
         * @brief Remove a check from the checkbood.
         * 
         * @param checkNum number of the check to remove
         */
        void remove(size_t checkNum);


        // sorter

        /**
         * @brief Sort the checks in the checkbook by check number.
         */
        void number_sort();

        /**
         * @brief Sort the checks in the checkbook by payto value.
         */
        void payto_sort();

        /**
         * @brief Sort the checks in the checkbook by date.
         */
        void date_sort();


        // file operation

        /**
         * @brief Loads the checkbook data from an ostream.
         * 
         * @param fileStream the stream to read checkbook data from
         */
        void load_from_file(std::ifstream& fileStream);

        /**
         * @brief Outputs the checkbook data to an ostream.
         * 
         * @param fileStream the stream to output checkbook data to
         */
        void save(std::ofstream& fileStream) const;


        // display or calculate info

        /**
         * @brief Outputs the checkbook data of all checks.
         * 
         * @param outs the stream to output the data to
         */
        void show_all(std::ostream& outs) const;

        /**
         * @brief Outputs the checkbook data of all checks that have a given payto value.
         * 
         * @param payto_query the payto value to search for
         */
        void show(std::string payto_query) const;

        /**
         * @brief Returns the average amount of all checks in the checkbook.
         * 
         * @return the average
         */
        double average() const;

    private:
        Check checks[SIZE];   // array of all the checks
        size_t used;          // number of checks used
        size_t nextCheckNum;  // number of next available check
        double balance;       // balance of the checkbook


        // helper functions

        /**
         * @brief Clears out any newline characters at the beginning of the stream
         * 
         * @param ins the stream to be cleared of newlines
         */
        void clearNewlines(std::istream& ins);

        /**
         *  @brief Converts an entire string to uppercase.
         * 
         *  @param input the string to be converted
         *  @return the string in uppercase
         */
        std::string stringToUpper(std::string input) const;
};

#endif