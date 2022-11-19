#include "Header.h"

int main(int argc, char** argv)
{
    if(strcmp(argv[1], "-e") == 0)
    {
        ifstream filenameinput;
        filenameinput.open(argv[2]);

        string inputdata;
        getline(filenameinput, inputdata);

        filenameinput.close();


        map<string, int> Dictionary;
        vector<int> code = LZWCompressor(inputdata, Dictionary);


        ofstream filenameoutput;
        filenameoutput.open(argv[3], ios::binary);

        // // map<int, string> Dictionary1;
        // // string res = LZWDecompressor(b, Dictionary1);

        // cout << res << endl << endl;

        for(int i = 0; i < code.size(); i++)
        {
            filenameoutput.write((char*)&code[i], sizeof(code[i]));
        }
        filenameoutput.flush();
        filenameoutput.close();

        // // ifstream filename;
        // // filename.open(argv[3]);
        // // getline(filename,a);
        // // cout << a << endl;
        // // filename.close();

        if(strcmp(argv[4], "-i") == 0)
        {
            cout << "Input size: " << inputdata.length()*8 << endl;
            cout << "Output size: " << code.size()*10 << endl;
            cout << "Space saved: " << (inputdata.length()*8 - (code.size()*10)) * 100.00 / (inputdata.length()*8) <<"%"<<endl;
        }
        if(strcmp(argv[4], "-d") == 0)
        {
            cout << "\nDictionary:\n";
            for(auto i : Dictionary)
                cout<< i.first << ": " << i.second << endl;
        }
        if(strcmp(argv[4], "-ind") == 0)
        {
            cout << "Input size: " << inputdata.length()*8 << endl;
            cout << "Output size: " << code.size()*10 << endl;
            cout << "Space saved: " << (inputdata.length()*8 - (code.size()*10)) * 100.00 / (inputdata.length()*8) <<"%"<<endl;
            cout << "\nDictionary:\n";
            for(auto i : Dictionary)
                cout<< i.first << ": " << i.second << endl;
        }
    }
    else if(strcmp(argv[1], "-d")==0)
    {
        ifstream filenameinput;
        filenameinput.open(argv[2], ios::binary);

        vector<int> code;
        auto i = GetFileSize(argv[2]);

        int a;
        while(i != 0)
        {
            filenameinput.read((char*)&a, sizeof(a));
            code.push_back(a);
            i-=sizeof(a);
        }

        map<int, string> Dictionary;
        
        ofstream filenameoutput;
        filenameoutput.open(argv[3]);
        string res = LZWDecompressor(code, Dictionary);
        filenameoutput << res;

        if(strcmp(argv[4], "-i") == 0)
        {
            cout << "Input size: " << code.size()*10 << endl;
            cout << "Output size: " << res.length()*8 << endl;
            cout << "Space saved: " << (res.length()*8 - (code.size()*10)) * 100.00 / (res.length()*8) <<"%"<<endl;
        }
        if(strcmp(argv[4], "-d") == 0)
        {
            cout << "\nDictionary:\n";
            for(auto i : Dictionary)
                cout<< i.first << ": " << i.second << endl;
        }
        if(strcmp(argv[4], "-ind") == 0)
        {
            cout << "Input size: " << code.size()*10 << endl;
            cout << "Output size: " << res.length()*8 << endl;
            cout << "Space saved: " << (res.length()*8 - (code.size()*10)) * 100.00 / (res.length()*8) <<"%"<<endl;
            cout << "\nDictionary:\n";
            for(auto i : Dictionary)
                cout<< i.second << ": " << i.first << endl;
        }
    }

}