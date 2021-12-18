#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <cstdio>


using namespace std;


void indent (int n, fstream& file);

void data_to_file (int indentation, fstream& file, string& line, int& i, string& data);

void file_string (fstream& file, vector<string>& result);

void Parse_data (int indentation, fstream& file, string& line, int& i, string& data);

void Print_tag (int indentation, fstream& file, string& line, int& i);

void remove_space (string& line, int& i);

string formatting (fstream& my_file);

string mediator (string text);

string test (vector<string> text);