#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

void init ();

int main ()
{
    init ();
    fstream my_file;
    my_file.open ("file.xml", ios::app);
    if (my_file.is_open ())
    {

        my_file.close ();
    }

}

void init ()
{
    (std::cin).tie (0);
    (std::cin).sync_with_stdio (0);
}