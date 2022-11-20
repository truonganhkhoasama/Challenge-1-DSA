#include "Header.h"

int main(int argc, char** argv)
{
    if(strcmp(argv[1], "-e") == 0) //Encode
    {
        cout << "\nENCODE: \n";

        ifstream filenameinput;
        filenameinput.open(argv[2]); //Open .txt input file to read input data

        string inputdata;
        getline(filenameinput, inputdata); //Get data from input file

        filenameinput.close();


        map<string, int> Dictionary;
        vector<int> code = LZWCompressor(inputdata, Dictionary); //Encode


        ofstream filenameoutput;
        filenameoutput.open(argv[3], ios::binary); //Open .lzw output binary file to write encoded data

        for(int i = 0; i < code.size(); i++)
        {
            filenameoutput.write((char*)&code[i], sizeof(code[i])); //Write into output binary file
        }
        filenameoutput.flush();
        filenameoutput.close();

        int inputsize = GetFileSize(argv[2]) * 8;
        int outputsize = code.size() * 10;

        cout << endl;
        if(strcmp(argv[4], "-i") == 0)
        {
            cout << "Input size: " << inputsize << " bits" << endl;
            cout << "Output size: " << outputsize << " bits" << endl;
            cout << "Space saved: " << (inputsize - outputsize) * 100.00 / (inputsize) <<"%"<<endl;
        }
        if(strcmp(argv[4], "-d") == 0)
        {
            cout << "Dictionary:\n";
            for(auto i : Dictionary)
                cout<< i.first << ": " << i.second << endl;
        }
        if(strcmp(argv[4], "-ind") == 0)
        {
            cout << "Input size: " << inputsize << " bits" << endl;
            cout << "Output size: " << outputsize << " bits" << endl;
            cout << "Space saved: " << (inputsize - outputsize) * 100.00 / (inputsize) <<"%"<<endl;
            cout << "\nDictionary:\n";
            for(auto i : Dictionary)
                cout<< i.first << ": " << i.second << endl;
        }
    }
    else if(strcmp(argv[1], "-d") == 0) //Decode
    {
        cout << "\nDECODE: \n";

        ifstream filenameinput;
        filenameinput.open(argv[2], ios::binary); //Open .lzw input binary file to read encoded data

        vector<int> code;
        auto i = GetFileSize(argv[2]); //Get size of input binary file

        int encodedNumber;
        while(i != 0)
        {
            filenameinput.read((char*)&encodedNumber, sizeof(encodedNumber)); //Read binary data into integer
            code.push_back(encodedNumber); //Create encoded data
            i -= sizeof(encodedNumber);
        }
        
        ofstream filenameoutput;
        filenameoutput.open(argv[3]); //Open .txt output file to write decoded data

        map<int, string> Dictionary;
        string res = LZWDecompressor(code, Dictionary); //Decode
        filenameoutput << res;
        filenameoutput.close();

        int inputsize = code.size() * 10;
        int outputsize = GetFileSize(argv[3]) * 8;

        cout << "\n";
        if(strcmp(argv[4], "-i") == 0)
        {
            cout << "Input size: " << inputsize << " bits" << endl;
            cout << "Output size: " << outputsize << " bits" << endl;
            cout << "Space saved: " << (outputsize - inputsize) * 100.00 / (outputsize) <<"%"<<endl;
        }
        else if(strcmp(argv[4], "-d") == 0)
        {
            cout << "Dictionary:\n";
            for(auto i : Dictionary)
                cout<< i.second << ": " << i.first << endl;
        }
        else if(strcmp(argv[4], "-ind") == 0)
        {
            cout << "Input size: " << inputsize << " bits" << endl;
            cout << "Output size: " << outputsize << " bits" << endl;
            cout << "Space saved: " << (outputsize - inputsize) * 100.00 / (outputsize) <<"%"<<endl;
            cout << "\nDictionary:\n";
            for(auto i : Dictionary)
                cout<< i.second << ": " << i.first << endl;
        }
    }
}