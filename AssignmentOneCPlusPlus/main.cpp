#include <iostream>
#include <fstream>
#include <ostream>
#include <cstdlib>
#include <regex>
#include <string>
using namespace std;
//prototype
void htmlConversionMethod(ifstream& inStream, ofstream& outStream);
int main() {
    ifstream inStream;
    ofstream outStream;
    string inputFileName;
    string outputFileName;
    /*https://stackoverflow.com/questions/11794144/
     * regular-expression-for-valid-filename
     * regex for proper windows filename, 10 upvote comment.*/
    regex fileNameRegex("^[a-zA-Z0-9](?:[a-zA-Z0-9 ._-]*[a-zA-Z0-9])?$");
    /*Program only functions properly when the same is in the same dir
     * as the executable*/
    cout << "CPP to HTML file converter.\n\n";
    cout << "Enter the name of the .cpp file you wish to convert.\n"
            "Please use the file name without the extension:" << endl;
    cin >> inputFileName;

    do{
        if(!regex_match(inputFileName,fileNameRegex)) {
            cout << "Invalid Windows filename, try again:" << endl;
           cin >> inputFileName;
        }
    }while(!regex_match(inputFileName,fileNameRegex));
    /*variables for .ccp and .html files*/
    outputFileName = inputFileName + ".html";
    inputFileName = inputFileName + ".cpp";

    try{
        inStream.open(inputFileName.c_str());
        if(inStream.fail()){
            throw invalid_argument("Failed to open specified cpp file.");
        }
    }catch(const invalid_argument& e){
        cout << "Failed to open specified cpp file." << endl;
        exit(-1);
    }


    try{
        outStream.open(outputFileName.c_str());
        if(outStream.fail()){
            throw invalid_argument("Failed to make specified html file.");
        }
    }catch(const invalid_argument& e){
        cout << "Failed to make specified html file." << endl;
    }
    /*Alterations to the file done here, adding tags and calling method
     * to change the '<' and '>'*/
    outStream << "<PRE>" << endl;
    htmlConversionMethod(inStream,outStream);
    outStream << "</PRE>" << endl;

    /*close up both streams*/
    inStream.close();
    outStream.close();

    cout << outputFileName + " Created and Altered.";
    return 0;
}
/*method takes the current character in the stream and puts it into the
 * new file, replacing based on business rule*/
void htmlConversionMethod(ifstream& inStream, ofstream& outStream)
{
    char currentChar;
    inStream.get(currentChar);
    /*loops until the whole file has been read*/
    while (!inStream.eof())
    {
        if (currentChar == '<'){
            outStream << "&lt;";
        }
        else if (currentChar == '>') {
            outStream << "&gt;";
        }
        else {
            outStream << currentChar;
        }
        inStream.get(currentChar);
    }
}
