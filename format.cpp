#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
#include "format.h"
using namespace std;

string format (string xml, vector<string>& to_json) // time O(n) // space O(n)
{
    queue<string> data;
    static int indentation = 0;
    string s = remove (&xml);
    for (int i = 0; i < s.size (); i++)
    {
        string temp = "";
        if (s[i] == '<') //tag
        {
            if (s[i + 1] == '/') //closing tag
            {
                indentation --;
                indent (temp, indentation);
                for (; s[i] != '>'; i ++)
                    temp += s[i];
                temp += s[i];
                data.push (temp);
            } else //opening tag
            {
                indent (temp, indentation);
                for (; s[i] != '>'; i ++)
                    temp += s[i];
                temp += s[i];
                data.push (temp);
                indentation++;
            }
        } else //values
        {
            indent (temp, indentation);
            for (; s[i] != '<'; i ++)
            {
                temp += s[i];
            }
            // string res = oneline (temp);
            i--;
            data.push (temp);
        }
    }
    return queue_string (data, to_json);
}

void indent (string& temp, int indentation)
{
    for (int j = 0; j < indentation * 4; j ++)
        temp += ' ';
}


string queue_string (queue<string>& data, vector<string>& to_json) //time O(n) // space O(1)
{
    string ans = "";
    while (!data.empty ())
    {
        ans += data.front ();
        to_json.push_back (data.front ());
        ans += '\n';
        data.pop ();
    }
    return ans;
}

string remove (string* file)  //time O(N) //space O(1)
{
    string output = "";
    //to clear the white spaces and remove new lines:
    size_t i = 0;
    for (; i < file->size (); i++)
    {
        if ((*file)[i] == ' ')
            continue;
        else
            break;
    }
    for (; i < file->size (); i++)
    {
        if ((*file)[i] == '\t' || (*file)[i] == '\n' || ((*file)[i] == ' ' && (*file)[i + 1] == ' ') || ((*file)[i] == ' ' && (*file)[i + 1] == '<'))
            continue;
        else
        {
            output = output + (*file)[i];
        }
    }
    string res = "";
    for (size_t j = 0; j < output.size (); j++)
    {
        if (output[j] == '<') //opening tag
        {
            for (; output[j] != '>'; j++)
            {
                if (output[j] == ' ')
                    continue;
                else
                    res += output[j];
            }
        }
        res += output[j];
    }
    return *file = res;
}
