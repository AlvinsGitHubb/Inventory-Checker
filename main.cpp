/*
  Author: Alvin Mathew
  Description: This code checks if the content of the inventory is correct. This program checks a txt file named in.txt,in0.txt,in1.txt...in7.txt.
*/
#include <iostream>
#include <fstream>
using namespace std;

bool FileValidation(string);
bool PLUValidation(string);
bool NameValidation(string);
bool ProdTypeValidation(string);
bool isValidPrice(string); 
bool InventoryValidation(string);
string tokenize(string &);
int CountWords(string);


int main()
{

    string filename;
    
    cout << "Enter input file:";
    cin >> filename;
    
    cout << "\nChecking " << filename << endl;
    if(filename=="in.txt")
    cout << "---------------" << endl;
    else if(filename=="in0.txt" || filename=="in1.txt" || filename=="in2.txt" || filename=="in3.txt" || filename=="in4.txt" || filename=="in5.txt" || filename=="in6.txt" || filename=="in7.txt")
    cout << "----------------" << endl;
    
    
    if (FileValidation(filename))
        cout << endl << "######## " << filename << " has valid content ########" << endl;
    else
        cout << endl << "######## " << filename << " has invalid content ########" << endl;

    return 0;
}

bool FileValidation(string filename) {

    ifstream inFile(filename.c_str());
    string line;
    string token;

    if (inFile.is_open())
    {

        while (getline(inFile, line))
        {
            cout << endl;

            int i = 1;
            int c = CountWords(line);

            while (line.length() != 0 && i < c+2)
            {
                token = tokenize(line);

                if (i == 1)
                {
                    if (PLUValidation(token))
                    {
                        cout << "Token #1 is " <<token << ", PLU is valid" << endl;
                    } else
                    {
                        cout << "Token #1 is " << token << ", PLU is invalid" << endl;
                        return false;
                    }

                } else if (i == 2)
                {
                    if (NameValidation(token))
                    {
                        cout << "Token #2 is " << token << ", Product name is valid" << endl;
                    } else
                    {
                        cout << "Token #2 is " << token << ", Product name is invalid" << endl;
                        return false;
                    }

                } else if (i == 3) {
                    if (ProdTypeValidation(token))
                    {
                        cout << "Token #3 is " << token << ", Sales type is valid" << endl;
                    } else
                    {
                        cout << "Token #3 is " << token << ", Sales type is invalid" << endl;
                        return false;
                    }

                } else if (i == 4)
                {
                    if (isValidPrice(token))
                    {
                        cout << "Token #4 is " <<token << ", Price is valid" << endl;
                    } else
                    {
                        cout << "Token #4 is "  <<token << ", Price is invalid" << endl;
                        return false;
                    }

                } else if (i == 5) {
                    if (InventoryValidation(token))
                    {
                        cout << "Token #5 is " << token << ", Inventory is valid" << endl;
                    } else
                    {
                        cout << "Token #5 is " << token << ", Inventory is invalid" << endl;
                        return false;
                    }

                } else if (i == 6 && !token.empty())
                {
                    cout << "Token #6 is " << token << ", Too many items in record" << endl;
                    return false;
                }

                i++;
            }
        }
    } else {
        cout << "Unable to open the file" << endl;
    }
    return true;
}

string tokenize(string &line)
{`
    //return empty string if no token is found
    //store all delimiters in a string and only return the expected output
    //the guided code was useless, but at least while loops work
    string token="";
    //just think simple, and keep going to complex, dont start thinking complex
    while(!line.empty() && (line.at(0)==' ' || line.at(0)=='\n' || line.at(0)=='\r' || line.at(0)=='\t')) //line.at can only take chars
    //erases char while line is a space or empty
    {
            line.erase(0,1); //erases first char
    }
    while(!line.empty() && line.at(0)!=' ' && line.at(0)!='\n' && line.at(0)!='\r' && line.at(0)!='\t')
    { //while the token isnt empty and is not a delimeter it adds onto the token string
        token = token+line.at(0);
        line.erase(0,1);
    }

    return token;
    
}

bool PLUValidation(string s)
{
    bool boolPLU = false;

    if (s.length() != 4) { //if its not 4 then false
        return false;
    } else {
        for (size_t i = 0; i < s.length(); i++) {

            char ch = s[i];

            if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))//returns true if capital or lowercase or a num
            {
            boolPLU = true;
            } else if (ch >= '0' && ch <= '9')
            {
            boolPLU = true;
            } else
            {
            return false;
            }

        }
        
    }

    return boolPLU;
}

bool NameValidation(string s) {
    char ch = s[0];

    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
        return true;
    else
        return false;
}

bool ProdTypeValidation(string s) {
    if (s.length() == 1 && (s[0] == '0' || s[0] == '1'))
        return true;
    else
        return false;
}

bool isValidPrice(string s) {
    bool boolPrice = false;
    int dot = 0;

    for (size_t i = 0; i < s.length(); i++) {
        char ch = s[i];
        if (ch >= '0' && ch <= '9') { //accounts for space, not just the actual price
            boolPrice = true;
        } else if (ch == '.') { //counts how many dots and if theres>1 then its invalid
            dot++;
            if (dot > 1)
                return false;
            else {
                boolPrice = true;
                string str2 = s.substr(i, s.length());

                if (str2.length() > 3)
                    return false;
            }
        } else {
            return false;
        }
    }

    return boolPrice;
}

bool InventoryValidation(string s)
{
    bool boolInv = true;

    for (size_t i = 0; i < s.length(); i++)
    {
        char ch = s[i];
        if (ch < '0' || ch > '9')
        {
            boolInv = false;
        }
    }

    return boolInv;
}

int CountWords(string s)
{
    
    int words = 0; // Holds number of words

    for (int i = 0; s[i] != '\0'; i++)
    {

        if (s[i] == ' ') //Checking for spaces
        {
        words++;
        }

    }

    return words;
}
