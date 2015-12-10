/* ----------------------------------------------------------------------------
 * Copyright &copy; 2015 Eugine Suh <eugine@csu.fullerton.edu>
 * Released under the [MIT License] (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */

/**
 * A collection of recursive functions.  
 */

#include <cmath>
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

using std::abs;

// ----------------------------------------------------------------------------
// by Euclid's algorithm

int gcd_iterative(int a, int b) {
    a = abs(a);
    b = abs(b);

    while (a && b) {
        if (a > b)
            a -= b;
        else
            b -= a;
    }
    return a+b;  // at least one of these will be 0    
}

int gcd(int a, int b) {
    a = abs(a);
    b = abs(b);

    if (a == 0 || b == 0)
        return a+b;

    if (a > b)
        return gcd(a-b, b);

    return gcd(a, b-a);
}

// ............................................................................

int fibonacci_iterative(int n, int f1 = 1, int f2 = 1) {
    // error check
    if (n < 1)
        return 0;

    if (n == 1)
        return f1;
    if (n == 2)
        return f2;

    while (n > 2) {
        int next = f1+f2;
        f1 = f2;
        f2 = next;
        n--;
    }

    return f2;
}

int fibonacci(int n, int f1 = 1, int f2 = 1) {
    // error check
    if (n < 1)
        return 0;

    if (n == 1)
        return f1;
    if (n == 2)
        return f2;

    return fibonacci(n-1, f2, f1+f2);
}

// ............................................................................

string int_to_roman_iterative(int i) {
    const string numerals[] = {
        "M",  "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I",
    };
    const int values[] = {
        1000, 900,  500, 400,  100, 90,   50,  40,   10,  9,    5,   4,    1,
    };

    if (i < 0)
        return "ERROR: too small";
    if (i >= 4000)
        return "ERROR: too large";

    string ret = "";

    for (int a = 0; a < sizeof(values)/sizeof(int); a++) {
        while (i >= values[a]) {
            ret += numerals[a];
            i -= values[a];
        }
    }

    return ret;
}

string int_to_roman(int i) {
    const string numerals[] = {
        "M",  "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I",
    };
    const int values[] = {
        1000, 900,  500, 400,  100, 90,   50,  40,   10,  9,    5,   4,    1,
    };

    if (i < 0)
        return "ERROR: too small";
    if (i >= 4000)
        return "ERROR: too large";

    if (i == 0)
        return "";

    for (int a = 0; a < sizeof(values)/sizeof(int); a++)
        if (i >= values[a])
            return numerals[a] + int_to_roman(i-values[a]);

    return "ERROR: unable to convert";
}

// ............................................................................

string int_to_words(int i, int suffix = -1) {
    const string sp = "_"; // word separation character ("space")

    const string small[] = {
        "", "one", "two", "three", "four",
        "five", "six", "seven", "eight", "nine",
        "ten", "eleven", "twelve", "thirteen", "fourteen",
        "fifteen", "sixteen", "seventeen", "eighteen", "nineteen",
    };

    const string tens[] = {
        "", "ten", "twenty", "thirty", "forty",
        "fifty", "sixty", "seventy", "eighty", "ninety",
    };

    // indexed by the power of 10 divided by 3 (since in English, numbers are
    // grouped into sets of 3)
    const string suffixes[] = {
        "", sp+"thousand", sp+"million", sp+"billion", sp+"trillion",
        sp+"quadrillion", sp+"quintillion",
    };

    if (suffix < 0) {
        if (i == 0)
            return "zero";
        else
            return int_to_words(i, 0);
    }

    if (i < 0)
        return "negative" + sp + int_to_words(-i);
    if (i < 20)
        return small[i] + suffixes[suffix];
    if (i < 100)
        return tens[i/10] + ( (i%10) ? sp : "" ) + int_to_words(i%10, suffix);
    if (i < 1000)
        return small[i/100] + sp + "hundred"
               + ( (i%100) ? sp : "" ) + int_to_words(i%100, suffix);

    return int_to_words(i/1000, suffix+1)
           + ( (i%1000) ? sp + int_to_words(i%1000, suffix) : "" );
}

// ............................................................................

string magic_number(int i) {
    string current = int_to_words(i);
    string next = int_to_words(current.length());

    if (current.compare(next) == 0)
        return std::to_string(i) + " is the magic number!\n";

    return std::to_string(i) + " is " + std::to_string(current.length()) + "\n"
           + magic_number(current.length());
}

// ----------------------------------------------------------------------------

void test__int_to_words() {
    for (int i = -1; i <= 1; i++)
        cout << int_to_words(i) << endl;
    for (int a = 10; a <= 100000000; a*=10)  // power of 10
        for (int b = 1; b <= 2; b++)  // first number
            for (int c = 0; c <= 1; c++)  // last number
                cout << int_to_words(a * b + c) << endl;
    cout << int_to_words(1001000) << endl;
    cout << int_to_words(1001001) << endl;
}

// ----------------------------------------------------------------------------

int main() {

    return 0;
}

