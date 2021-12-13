#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <cstdio>

using namespace std;

typedef long long ll;


void indent (int n, fstream& file);
void Print_tag (int indentation, fstream& file, string& line, int& i);
void Parse_data (int indentation, fstream& file, string& line, int& i, string& data);
void remove_space (string& line, int& i);
void data_to_file (int indentation, fstream& file, string& line, int& i, string& data);
void file_string (fstream& file, vector<string>& result);
// void erase_newLine (string& str);


int main ()
{
    fstream my_file, temp_file;
    vector<string> result;
    static string data = "";
    my_file.open ("D:\\CSE\\Senior 1\\Data\\Data_Project\\project\\file.xml", ios::in);
    temp_file.open ("D:\\CSE\\Senior 1\\Data\\Data_Project\\project\\temp.xml");

    if (my_file.is_open () && temp_file.is_open ())
    {
        int indentation = 0;
        string line; //take the file line by line
        while (getline (my_file, line))
        {
            // line = ltrim (line);
            for (int i = 0; i < line.size (); i ++)
            {
                remove_space (line, i);
                if (i < line.size ())
                {
                    if (line[i] == '<') //tag
                    {
                        if (line[i + 1] == '/') //closing
                        {
                            data_to_file (indentation, temp_file, line, i, data);
                            indentation --;
                            //print the tag
                            Print_tag (indentation, temp_file, line, i);
                        } else  //opening
                        {
                            //print the tag
                            Print_tag (indentation, temp_file, line, i);
                            indentation ++;
                        }
                    } else //data
                    {
                        //print data
                        Parse_data (indentation, temp_file, line, i, data);
                    }
                }
            }
             //convert the file to array of strings
            // for (int i = 0; i < (int)result.size (); i ++)
            // {
            //     cout << result[i];
            // }
            // cout << result.at (2);
            my_file.close ();
            temp_file.close ();
            // int ans = remove ("temp.xml");
            // cout << endl << ans << endl;

        }

    }
    temp_file.open ("D:\\CSE\\Senior 1\\Data\\Data_Project\\project\\temp.xml");
    file_string (temp_file, result);
    cout << result.size ();

    //read from temp file and overwrite the original file????

}

void file_string (fstream& file, vector<string>& result)
{
    string line;
    while (getline (file, line))
        result.push_back (line);
}

void Parse_data (int indentation, fstream& file, string& line, int& i, string& data)
{
    // remove_space (line, i);
    // if (i >= line.size ())
    //     return;

    while (line[i] != '<' && i < line.size ())
    {
        // indent (indentation, file);
        data += line[i++];
    }
    if (line[i] == '<')  //data is finished
        data_to_file (indentation, file, line, i, data);

    // file << endl;
    i --;
}

void data_to_file (int indentation, fstream& file, string& line, int& i, string& data)
{
    if (data != "")
    {
        indent (indentation, file);
        file << data;
        file << endl;
    }
    data = "";
}
void Print_tag (int indentation, fstream& file, string& line, int& i) //tested
{
    // if (i == line.size ())
    //     return;

    indent (indentation, file);
    while (line[i] != '>')
    {
        if (line[i] != ' ')
            file << line[i++];
    }
    file << line[i];
    file << endl;
}

void indent (int n, fstream& file)  //tested
{
    file << string (n * 4, ' ');
}

void remove_space (string& line, int& i)
{
    for (; i < line.size (); i ++)
    {
        if (line[i] != ' ')
            return;
    }
}

void Print_line (int indentation, fstream& file, string& line, int& i)
{
    indent (indentation, file);
    while (i != line.size ())
    {
        file << line[i++];
    }
    file << line[i];
    file << endl;
}

// void erase_newLine (string& str)
// {
//     str.erase (remove (str.begin (), str.end (), '\n'), str.end ());
// }