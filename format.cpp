#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

void indent (int n, fstream& file);
void Print_tag (int indentation, fstream& file, string& line, int& i);


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
            for (int i = 0; i < line.size (); i ++)
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

                }
            }
        }
        my_file.close ();
        temp_file.close ();
    }

    //read from temp file and overwrite the original file

}

void Print_tag (int indentation, fstream& file, string& line, int& i) //tested
{
    indent (indentation, file);
    while (line[i] != '>')
    {
        file << line[i++];
    }
    file << line[i] << endl;
}

void indent (int n, fstream& file)  //tested
{
    file << string (n * 4, ' ');
}
