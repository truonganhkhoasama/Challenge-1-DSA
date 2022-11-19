#include "Header.h"

string createString(vector<char> a)
{
    string key = "";
    for (int i = 0; i < a.size(); i++)
    {
        key.push_back(a[i]);
    }
    return key;
}

vector<int> LZWCompressor(string a, map<string, int>& Dictionary)
{
    vector<int> code; //Initialse vector to contain compressed code
    vector<char> charvec; //Vector containing characters to form string

    int index = 256; //Values from 0 to FF belong to ASCII set and present set that has only one character

    string keyin;
    string keyout;

    for (int i = 0; i <= a.size(); i++)
    {
        charvec.push_back(a[i]);
        keyin = createString(charvec);

        if (keyin.length() > 1)
        {
            if (Dictionary.count(keyin) == 0)
            {
                //Insert into Dictionary
                if (keyin[keyin.length() - 1] != '\0')
                    Dictionary.insert(make_pair(keyin, index++));

                //Take keyout
                while (charvec.size() != 1)
                {
                    keyout.push_back(charvec[0]);
                    charvec.erase(charvec.begin());
                }

                //Insert ASCII into Dictionary
                //if (keyout.length() == 1)
                //{
                //    if (Dictionary.count(keyout) == 0)
                //        Dictionary.insert(make_pair(keyout, int(keyout[0])));
                //}

                //Insert into CODE
                if (keyout.length() == 1)
                    code.push_back(int(keyout[0]));
                else
                {
                    auto it = Dictionary.find(keyout);
                    if (it != Dictionary.end())
                        code.push_back(it->second);
                }
                keyout = "";
            }
        }
    }
    return code;
}

string LZWDecompressor(vector<int> code, map<int, string>& Dictionary)
{
    string res;
    string PartialEntry;
    int index = 256;
    string decode;
    for (int i = 0; i < code.size(); i++)
    {
        if (code[i] < 256)
        {
            decode.push_back(char(code[i]));
            PartialEntry.push_back(char(code[i]));
        }
        else
        {
            auto it = Dictionary.find(code[i]);
            if (it != Dictionary.end())
            {
                decode = it->second;
                PartialEntry.push_back(it->second[0]);
            }
        }

        if (PartialEntry.length() > 1)
        {
            Dictionary.insert(make_pair(index++, PartialEntry));
        }

        res += decode;
        PartialEntry = decode;
        decode = "";
    }

    return res;
}

string toBinary(int n)
{
    string r;
    while(n!=0)
    {
        r = (n % 2 == 0 ? "0" : "1") + r;
        n/=2;
    }
    while(r.length()<10)
    {
        r = "0" + r;
    }
    return r;
}

long GetFileSize(std::string filename)
{
    struct stat stat_buf;
    int rc = stat(filename.c_str(), &stat_buf);
    return rc == 0 ? stat_buf.st_size : -1;
}
