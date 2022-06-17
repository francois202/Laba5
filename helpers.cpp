#include "helpers.h"
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

double str_to_double(const char* str) {
    string conv(str);
    size_t comma = conv.find(',');
    if (comma != -1) {
        conv[comma] = '.';
    }
    double num = atof(conv.c_str());
    return num;
}

string tostring(double n)
{
    ostringstream oss;
    oss << n;
    string s = oss.str();
    int dotpos = s.find_first_of('.');
    if(dotpos != string::npos)
    {
        int ipos = s.size() - 1;
        while(s[ipos] == '0' && ipos > dotpos)
        {
            --ipos;
        }
        s.erase (ipos + 1, std::string::npos);
    }
    return s;
}

bool is_double(const char* str)
{
    int i = 1;
    if (str[0] == '-' and str[1] == '\0')
    {
        return false;
    }
    while (str[i] != '\0')
    {
        if (!(isdigit(str[i]) or str[i] == '.' or str[i] == ','))
        {
            cout << str << endl;
            return false;
        }
        i++;
    }
    return true;
}