/*************************************************************************
    This is the implementation file for the Check class. For more 
		information about the class see check.h.
    Students are expected to implement some of the functions shown 
		below.
	John Dolan			Ohio University EECS	September 2019
	Patricia Lindner	Ohio University EECS	August 2021
*************************************************************************/
#include "check.h"
using namespace std;

Check::Check(Date d, string p, int num, double amt){
	checknum = num;
	date = d;
	payto = p;
	amount = amt;
}

// Input and output functions
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

void Check::output(std::ostream& outs)const{
	/* You are to write the implementation of this function to write 
	to the monitor or to a file. Remember not to put labels into the 
	file.*/

}

ostream& operator << (ostream& outs, const Check& c){
	c.output(outs);
	return outs;
}

istream& operator >> (istream& ins, Check& c){
	c.write_check(ins);
	return ins;
}

/**
 * @brief Clears out any newline characters at the beginning of the stream
 * 
 * @param ins the stream to be cleared of newlines
 */
void Check::clearNewlines(std::istream& ins) {
    while (cin.peek() == '\n' || cin.peek() == '\r') {
        cin.ignore();
    }
}