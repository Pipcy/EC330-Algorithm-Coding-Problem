/*
 * need to download "BigData.txt" from https://drive.google.com/file/d/0B2H-ZCNPqkX2bzhxUlRVdHg4cVE/view?usp=sharing&resourcekey=0-feWTz4uAWol9e5qOz6_b7w
 * be sure to put it on the same path
 * expected output:
 *      The number of BU-IDs whose digits add to a number greater than 28: 49323
 *      Number of valid dictionary words that don't end with last letter of last name: 450789269
 *      Longest palindrome: 11
 */
#include <iostream>
#include "Problem5.h"

using namespace std;

int main()
{
    cout << "The number of BU-IDs whose digits add to a number greater than 28: " << fiveA() << endl;
    cout << "Number of valid dictionary words that don't end with last letter of last name: " << fiveB() << endl;
    cout << "Longest palindrome: " << fiveC() << endl;

}
