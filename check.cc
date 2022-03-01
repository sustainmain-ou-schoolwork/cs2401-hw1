/*************************************************************************
    This is the implementation file for the Check class. For more 
		information about the class see check.h.
    Students are expected to implement some of the functions shown 
		below.
	John Dolan			Ohio University EECS	September 2019
	Patricia Lindner	Ohio University EECS	August 2021
*************************************************************************/
#include "check.h"
#include <iomanip>
using namespace std;


/**
 * @brief Check constructor
 * 
 * @param d the date the check was written
 * @param p the payto (recipient) of the check
 * @param num the number of the check (used in checkbooks)
 * @param amt the amount the check was written for
 */
Check::Check(Date d, string p, int num, double amt){
	checknum = num;
	date = d;
	payto = p;
	amount = amt;
}


// Input and output functions

/**
 * @brief Sets the data values for a check based on stream input.
 * 
 * @param ins the stream to get check data from
 */
void Check::write_check(std::istream& ins){
    // if the check is being entered manually, don't let the user enter the check number
    if (&ins == &cin) {
        cout << "Enter the date, the recipient, and the amount: ";
    }
    else {
        ins >> checknum;
        clearNewlines(ins);
    }

    // get the other values
    ins >> date;
    clearNewlines(ins);
    getline(ins, payto);
    ins >> amount;
}

/**
 * @brief Outputs the data for a check line-by-line.
 * 
 * @param outs the stream to output the data to
 */
void Check::output(std::ostream& outs)const{
	outs << checknum << '\n';
    outs << date << '\n';
    outs << payto << '\n';
    outs << fixed << setprecision(2) << amount << endl;
}

/**
 * @brief Outputs the data for a check line-by-line.
 * 
 * @param outs the stream to output the data to
 * @param c the check to read data from
 */
ostream& operator << (ostream& outs, const Check& c){
	c.output(outs);
	return outs;
}

/**
 * @brief Sets the data values for a check based on stream input.
 * 
 * @param ins the stream to get check data from
 * @param c the check whose values will be set
 */
istream& operator >> (istream& ins, Check& c){
	c.write_check(ins);
	return ins;
}

/**
 * @brief Clears out any newline characters at the beginning of the stream.
 * 
 * @param ins the stream to be cleared of newlines
 */
void Check::clearNewlines(std::istream& ins) {
    while (ins.peek() == '\n' || ins.peek() == '\r') {
        ins.ignore();
    }
}