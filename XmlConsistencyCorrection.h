#pragma once
#include <string>
#include <stack>
#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <string>
#include <vector>
#include "TreeXml.h"
#include "weza.h"
stack <string> tags;
using namespace std;
string CheckConsistency(fstream& xmlFile);
fstream getFile(string input)
{
	fstream my_file;
	my_file.open("wrongXml.xml", ios::out);
	if (my_file.is_open())
	{
		for (int i = 0; i < input.length(); i++)
			my_file << input[i];


		my_file.close();
	}
	return my_file;
}
string detect(string s)
{
	fstream m = getFile(s);
	string x = CheckConsistency(m);
	return x;
}
void printXml(Node* node, vector<string>& XmlString)
{
	string t1 = (node->gettagname());
	t1.erase(remove(t1.begin(), t1.end(), '<'), t1.end());
	t1.erase(remove(t1.begin(), t1.end(), '>'), t1.end());
	XmlString.push_back("<" + t1 + ">");
	XmlString.push_back("\n");
	XmlString.push_back(node->getdata());
	XmlString.push_back("\n");

	for (int x = 0; x < node->getchildren().size(); x++)
	{
		printXml((node->getchildren()[x]), XmlString);
	}

	XmlString.push_back("</" + t1 + ">");
	XmlString.push_back("\n");

}
string VectToStr(vector <string> vect)
{
	string s;
	for (int i = 0; i < vect.size(); i++)
	{
		s = s + vect[i] ;
	}
	return s;
}
void find_and_replace(std::string& file_contents, const std::string& s1, const std::string& s2)
{//This searches the file for the first occurence of the morn string.
	auto pos = file_contents.find(s1);
	while (pos != std::string::npos) {
		file_contents.replace(pos, s1.length(), s2);
		//Continue searching from here.
		pos = file_contents.find(s1, pos);
	}
}
string no_space (string& s)
{
    string result = "";
    int i = 0;
    for (; i < s.size ();i ++)
        if (s[i] != ' ')
            break;

    for (; i < s.size (); i ++)
        result += s[i];
    return result;
}
string CheckConsistency(fstream& xmlFile)
{

	xmlFile.open("wrongXml.xml", ios::in);
	string flag;
	string errors;
	//create count for line number 
	int count;
	//flag for file consistency
	bool good = true;

	if (xmlFile.is_open())
	{
		//take the file line by line
		string line;

		count = 0;
		while (getline(xmlFile, line))
		{
			count++;
			int i = 0;
			//take length of line and copy of line to work on
			int len = line.length();
			string nline = line;
			while (i < len)
			{
				if (line[i] == '<')
				{
					//check closing or opening tag
					if (line[i + 1] == '/')
						//closing tag
					{
						//get closing tag
						int x = 0;
						int temp = i;
						while (line[i] != '>')
						{
							x++;
							i++;
						}
						string t = line.substr(temp + 2, x - 2);
						//check that stack is not empty (case 1 error)
						if (tags.empty())
						{
							string s = "Closed tag " + t + " in line" + to_string(count) + " before opening it.";
							errors += s;
							errors += "\n";
							good = false;
							//add opening tag before this closing one
							/*good = false;
							string tt = "</" + t + ">";
							string fix = " ";
							find_and_replace(nline, tt, fix);*/
							i++;
							//errors += "Removed closing tag.";
							//errors += "\n";
							continue;
						}


						//check that closing tag is same as top opening tag
						{
							if (t == tags.top())
							{
								tags.pop();
							}
							else
								//tags are not the same (case 2 error)
							{
							
									string s = "Mismatch in tags in line " + to_string(count) + ".";
									errors += s;
									errors += "\n";
									while (t != tags.top())
									{
										errors += "Tag <" + tags.top() + "> has an error.\n";
										good = false;
										tags.pop();
									}
									tags.pop();

								/*string tt = "</" + t + ">";
								string fix2 = "</" + tags.top() + ">";
								good = false;
								find_and_replace(nline, tt, fix2);
								std::cout << "Mismatch fixed." << endl;*/
							}
						}
					}

					else
						//opening tag
					{
						int x = 0;
						int temp = i;
						while (line[i] != '>')
						{
							x++;
							i++;
						}
						string t = (line.substr(temp + 1, x - 1));
						remove(t.begin(), t.end(), ' ');
						tags.push(t);

					}

				}
				i++;

			}
			//correctFile << nline << endl;;
		}
		if (!(tags.empty()))
		{
			while (!(tags.empty()))
			{
				//stack is not empty after ending file (case 3 error)
				errors = errors + "Tag <" + tags.top() + "> has an error.\n";
				//insert the closing tag of last tag in stack at the end of the file
				good = false;
				//correctFile << fix3 << endl;
				//errors = errors + "Closed the open tag.\n";
				tags.pop();
			}
		}
		
	}
	xmlFile.close();
	//correctFile.close();
	if (good)
	{
		flag = "File is consistent!!\n";
		return flag;
	}
	else
	{
		flag = "File is not consistent!!\n";
			return errors + flag ;
	}
	
}
static void xmltree(Node* node, vector <string> xml, int& i, Node* root) {


	for (; i < xml.size(); i++)
	{

		//if the string hasn't open tag, store the data of the next node
		if (xml[i].at(0) != '<') {
			node->setdata(xml[i]);
			i++;
			return;
		}
		else if (xml[i].at(1) == '/')  //base case when we have a closedtag
			return;

		else {

			Node* child = new Node(xml[i], " ");
			if (root->getchildren().size() > 0 && xml[i] == root->getchildren()[0]->gettagname())
			{
				root->addsamechild(root, child);
				i++;
			}

			else
			{
				node->addsamechild(node, child);
				i++;

			}
			xmltree(child, xml, i, root);
		}

	}

}
string XmlOutput(string s) 
{
	fstream file = getFile(s);
	vector <string> data;
	mediator(s, data);
	for (int i = 0; i < data.size(); i++)
	{
		data[i]  = no_space(data[i]);
	}
	Node* root = new Node();
	root->settagname(data[0]);
	int i{ 1 };
	xmltree(root, data, i, root);
	vector <string> outputXml;
	printXml(root, outputXml);
	vector <string> h;
	string out = VectToStr(outputXml);
	return mediator(out, h);
}
//int main()
//{
//	fstream my_file;
//	vector<string> data;
//	data = formatting(my_file);
//
//	for (int i = 0; i < (int)data.size(); i++)
//		cout << data[i] << endl;
//}

