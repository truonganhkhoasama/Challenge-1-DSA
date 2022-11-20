#include "Header.h"

vector<int> LZWCompressor(string inputdata, map<string, int>& Dictionary)
{
    vector<int> code; //Initialse integer vector to contain encoded code

    int index = 256; //Values from 0 to FF belong to ASCII table and present sets of charater that has only one character
                    // Values from 100 are thus used to present sets of character that has more than one character

    string keyin; //used to form new words in dictionary
    string keyout; //used to input into encoded data

    for (int i = 0; i <= inputdata.size(); i++)
    {
        keyin.push_back(inputdata[i]); //Input each character of inputdata

        if (keyin.length() > 1) //if keyin has more than 1 character then decide whether to form a new word in dictionary
        {
            if (Dictionary.count(keyin) == 0) //Check if there exists already a same word in dictionary
            {
                //Add new word into Dictionary
                if (keyin[keyin.length() - 1] != '\0')
                    Dictionary.insert(make_pair(keyin, index++));

                //Take keyout from keyin
                keyout = keyin.substr(0, keyin.length() -1);
                keyin.erase(0, keyin.length() - 1);

                //Insert data into code
                if (keyout.length() == 1)
                    code.push_back(int(keyout[0])); //insert the ASCII value of the character
                else
                {
                    auto it = Dictionary.find(keyout); //Look the word up in dictionary and
                    if (it != Dictionary.end())
                        code.push_back(it->second);  //insert the corresponding integer value into code
                }
                keyout = ""; //reset keyout
            }
        }
    }
    return code;
}

string LZWDecompressor(vector<int> code, map<int, string>& Dictionary)
{
    string res; //output data
    string PartialEntry; //string used to form new words

    int index = 256; //Values from 0 to FF belong to ASCII table and present sets of charater that has only one character
                    // Values from 100 are thus used to present sets of character that has more than one character

    string decode; //used to grab each sets of character to insert into res

    for (int i = 0; i < code.size(); i++)
    {
        if (code[i] < 256) //if less than 100 then belong to ASCII table
        {
            decode.push_back(char(code[i])); 
            PartialEntry.push_back(char(code[i]));
        }
        else
        {
            auto it = Dictionary.find(code[i]); //Look the number up in dictionary and
            if (it != Dictionary.end())
            {
                decode = it->second; //insert the corresponding string value into decode
                PartialEntry.push_back(it->second[0]); 
            }
        }

        if (PartialEntry.length() > 1)
        {
            Dictionary.insert(make_pair(index++, PartialEntry)); //Add new word into Dictionary
        }

        res += decode; //attach decode to output data
        PartialEntry = decode;
        decode = "";
    }

    return res;
}

long GetFileSize(std::string filename)
{
    struct stat stat_buf;
    int rc = stat(filename.c_str(), &stat_buf);
    return rc == 0 ? stat_buf.st_size : -1;
}
