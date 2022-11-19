#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
using namespace std;

string createString(vector<char> a);
vector<int> LZWCompressor(string a, map<string, int>& Dictionary);
string LZWDecompressor(vector<int> code, map<int, string>& Dictionary);
string toBinary(int n);
long GetFileSize(std::string filename);