#include <iostream>
#include <fstream>
#include <string>

using namespace std;

typedef long long ll;


void indent (int n, fstream& file);
void Print_tag (int indentation, fstream& file, string& line, int& i);
void Print_data (int indentation, fstream& file, string& line, int& i);
void remove_space (string& line, int& i);


int main ()
{
    fstream my_file, temp_file;
    my_file.open ("file.xml", ios::in);
    temp_file.open ("temp.xml", ios::out);

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
                        Print_data (indentation, temp_file, line, i);
                    }
                }
            }
        }
        my_file.close ();
        temp_file.close ();
    }

    //read from temp file and overwrite the original file????

}


void Print_data (int indentation, fstream& file, string& line, int& i)
{
    // remove_space (line, i);
    // if (i >= line.size ())
    //     return;

    indent (indentation, file);
    while (line[i] != '<' && i < line.size ())
    {
        file << line[i++];
    }
    file << endl;
    i --;
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
