#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
using namespace std;

void indent (string& temp, int indent);
string queue_string (queue<string>& data, vector<string>& to_json);
string format (string xml, vector<string>& to_json);
string remove (string* file);
