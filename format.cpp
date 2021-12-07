#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

void indent (int n);


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
                        indentation --;
                    else
                    {
                        indentation ++;

                    }
                }
            }
        }
        my_file.close ();
        temp_file.close ();
    }

    //read from temp file and overwrite the original file

}

bool arePair ();
void indent (int n)
{
    cout << string (n * 4, ' ');
}
