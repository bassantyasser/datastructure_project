#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <algorithm>
#include <vector>
#include <cstdio>
#include "formattingCons.h"

using namespace std;

typedef long long ll;


void indent(int n, fstream& file)  //tested
{
    file << string(n * 4, ' ');
}


void data_to_file(int indentation, fstream& file, string& line, int& i, string& data)
{
    if (data != "")
    {
        indent(indentation, file);
        file << data;
        file << endl;
    }
    data = "";
}

void file_string(fstream& file, vector<string>& result)
{
    string line;
    while (getline(file, line))
        result.push_back(line);
}

void Parse_data(int indentation, fstream& file, string& line, int& i, string& data)
{
    // remove_space (line, i);
    // if (i >= line.size ())
    //     return;

    while (line[i] != '<' && i < line.size())
    {
        // indent (indentation, file);
        data += line[i++];
    }
    if (line[i] == '<')  //data is finished
        data_to_file(indentation, file, line, i, data);

    // file << endl;
    i--;
}



void Print_tag(int indentation, fstream& file, string& line, int& i) //tested
{
    // if (i == line.size ())
    //     return;

    indent(indentation, file);
    while (line[i] != '>')
    {
        if (line[i] != ' ')
            file << line[i];
        i++;
    }
    file << line[i];
    file << endl;
}



void remove_space(string& line, int& i)
{
    for (; i < line.size(); i++)
    {
        if (line[i] != ' ')
            return;
    }
}

void Print_line(int indentation, fstream& file, string& line, int& i)
{
    indent(indentation, file);
    while (i != line.size())
    {
        file << line[i++];
    }
    file << line[i];
    file << endl;
}
string test(vector<string> text)
{
    string output = "";
    for (int i = 0; i < text.size(); i++)
    {
        output += text.at(i) + "\n";

    }
    return output;
}
//string formatting (fstream& my_file, string path)
//{
//    fstream temp_file;
//    vector<string> result;
//    static string data = "";
//    // my_file.open (path, ios::in);
//    temp_file.open ("temp.xml", ios::out);
//
//    if (my_file.is_open () && temp_file.is_open ())
//    {
//        int indentation = 0;
//        string line; //take the file line by line
//        while (getline (my_file, line))
//        {
//            // line = ltrim (line);
//            for (int i = 0; i < line.size (); i ++)
//            {
//                remove_space (line, i);
//                if (i < line.size ())
//                {
//                    if (line[i] == '<') //tag
//                    {
//                        if (line[i + 1] == '/') //closing
//                        {
//                            data_to_file (indentation, temp_file, line, i, data);
//                            indentation --;
//                            //print the tag
//                            Print_tag (indentation, temp_file, line, i);
//                        } else  //opening
//                        {
//                            //print the tag
//                            Print_tag (indentation, temp_file, line, i);
//                            indentation ++;
//                        }
//                    } else //data
//                    {
//                        //print data
//                        Parse_data (indentation, temp_file, line, i, data);
//                    }
//                }
//            }
//            //convert the file to array of strings
//            // for (int i = 0; i < (int)result.size (); i ++)
//            // {
//            //     cout << result[i];
//            // }
//            // cout << result.at (2);
//            // my_file.close ();
//
//            // int ans = remove ("temp.xml");
//            // cout << endl << ans << endl;
//
//        }
//        temp_file.close ();
//    }
//    temp_file.open ("temp.xml");
//    file_string (temp_file, result);
//    //cout << result.size ();
//    temp_file.close ();
//    string output = test (result);
//    //read from temp file and overwrite the original file????
//    return output;
//}

string formatting(fstream& my_file, vector<string>& res_vector)
{
    fstream temp_file;
    string result;
    static string data = "";
    // my_file.open ("C:\\Users\\hecker\\Desktop\\hello.xml", ios::in);
    temp_file.open("temp.xml", ios::out);

    if (my_file.is_open() && temp_file.is_open())
    {
        int indentation = 0;
        string line; //take the file line by line
        while (getline(my_file, line))
        {
            // line = ltrim (line);
            for (int i = 0; i < line.size(); i++)
            {
                remove_space(line, i);
                if (i < line.size())
                {

                    if (line[i] == '<') //tag
                    {
                        //< user > || < /user > //make the code
                        if (line[i + 1] == ' ')
                        {
                            remove_space(line, ++i);
                            i--;
                            line[i] = '<';
                        }
                        if (line[i + 1] == '/') //closing
                        {
                            data_to_file(indentation, temp_file, line, i, data);
                            indentation--;
                            //print the tag
                            Print_tag(indentation, temp_file, line, i);
                        }
                        else  //opening
                        {
                            //print the tag
                            Print_tag(indentation, temp_file, line, i);
                            indentation++;
                        }
                    }
                    else //data
                    {
                        //print data
                        Parse_data(indentation, temp_file, line, i, data);
                    }
                }
            }
            //convert the file to array of strings
           // for (int i = 0; i < (int)result.size (); i ++)
           // {
           //     cout << result[i];
           // }
           // cout << result.at (2);

           // int ans = remove ("temp.xml");
           // cout << endl << ans << endl;

        }
        my_file.close();
        temp_file.close();
    }
    temp_file.open("temp.xml");
    file_string(temp_file, res_vector);
    result = test(res_vector);
    // cout << result.size ();

    //read from temp file and overwrite the original file????
    return result;
}
string mediator(string text, vector<string>& tree)
{
    fstream my_file;
    my_file.open("sample.xml", ios::out);
    if (my_file.is_open())
    {
        for (int i = 0; i < text.size(); i++)
            my_file << text[i];

        my_file.close();
    }
    my_file.open("sample.xml");
    string output; //tested
    output = formatting(my_file, tree);
    // my_file.close ();
    return output;
}
//
//int main()
//{
//    string xml = "<users>\n"
//        "< user >\n"
//        "< id>1 < / id >\n"
//        "<name>Ahmed Ali</ name>\n"
//        "< / user>\n"
//        "<   /users>\n";
//    //cout << mediator (xml, "");
//    vector<string> data;
//    string text = mediator(xml, data);
//    cout << text << endl;
//}