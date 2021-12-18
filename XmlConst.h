//#pragma once
//#include <iostream>
//#include <fstream>
//#include <string>
//#include <stdio.h>
//#include <stack>
//#include <xtree>
//using namespace std;
//stack <string> tags;
//void printXml(Node* node, vector<string>& XmlString);
//
//void find_and_replace(std::string& file_contents, const std::string& s1, const std::string& s2) {
//	//This searches the file for the first occurence of the morn string.
//	auto pos = file_contents.find(s1);
//	while (pos != std::string::npos) {
//		file_contents.replace(pos, s1.length(), s2);
//		//Continue searching from here.
//		pos = file_contents.find(s1, pos);
//	}
//}
//
//void CheckConsistency(fstream& xmlFile, ofstream& correctFile)
//{
//	//create count for line number 
//	int count;
//	//flag for file consistency
//	bool good = true;
//
//	if (xmlFile.is_open())
//	{
//		//take the file line by line
//		string line;
//
//		count = 0;
//		while (getline(xmlFile, line))
//		{
//			count++;
//			int i = 0;
//			//take length of line and copy of line to work on
//			int len = line.length();
//			string nline = line;
//			while (i < len)
//			{
//				if (line[i] == '<')
//				{
//					//check closing or opening tag
//					if (line[i + 1] == '/')
//						//closing tag
//					{
//						//get closing tag
//						int x = 0;
//						int temp = i;
//						while (line[i] != '>')
//						{
//							x++;
//							i++;
//						}
//						string t = line.substr(temp + 2, x - 2);
//						//check that stack is not empty (case 1 error)
//						if (tags.empty())
//						{
//							std::cout << "Closed tag " << t << " in line" << count << " before opening it." << endl;
//							//add opening tag before this closing one
//							good = false;
//							string tt = "</" + t + ">";
//							string fix = " ";
//							find_and_replace(nline, tt, fix);
//							i++;
//							std::cout << "Removed clsosing tag." << endl;
//							continue;
//						}
//
//
//						//check that closing tag is same as top opening tag
//						{
//							if (t == tags.top())
//							{
//								tags.pop();
//							}
//							else
//								//tags are not the same (case 2 error)
//							{
//								std::cout << "Mismatch in tags in line " << count << "." << endl;
//								/*string tt = "</" + t + ">";
//								string fix2 = "</" + tags.top() + ">";
//								good = false;
//								find_and_replace(nline, tt, fix2);
//								tags.pop();
//								std::cout << "Mismatch fixed." << endl;*/
//							}
//						}
//					}
//
//					else
//						//opening tag
//					{
//						int x = 0;
//						int temp = i;
//						while (line[i] != '>')
//						{
//							x++;
//							i++;
//						}
//						string t = (line.substr(temp + 1, x - 1));
//						remove(t.begin(), t.end(), ' ');
//						tags.push(t);
//
//					}
//
//				}
//				i++;
//
//			}
//			correctFile << nline << endl;;
//		}
//		if (!(tags.empty()))
//		{
//			while (!(tags.empty()))
//			{
//				//stack is not empty after ending file (case 3 error)
//				std::cout << "Tag <" << tags.top() << "> is not closed." << endl;
//				//insert the closing tag of last tag in stack at the end of the file
//				good = false;
//				string fix3 = "</" + tags.top() + ">";
//				correctFile << fix3 << endl;
//				std::cout << "Closed the open tag." << endl;
//				tags.pop();
//			}
//		}
//	}
//	xmlFile.close();
//	correctFile.close();
//	if (good)
//	{
//		std::cout << "File is consistent!!" << endl;
//	}
//	else
//	{
//		std::cout << "File fixed & is now consistent!!" << endl;
//	}
//
//}
//
//void printXml(Node* node, vector<string>& XmlString)
//{
//	string t1 = (node->gettagname());
//	t1.erase(remove(t1.begin(), t1.end(), '<'), t1.end());
//	t1.erase(remove(t1.begin(), t1.end(), '>'), t1.end());
//	XmlString.push_back("<" + t1 + ">");
//	XmlString.push_back("\n");
//	XmlString.push_back(node->getdata());
//	XmlString.push_back("\n");
//
//	for (int x = 0; x < node->getchildren().size(); x++)
//	{
//		printXml((node->getchildren()[x]), XmlString);
//	}
//
//	XmlString.push_back("</" + t1 + ">");
//	XmlString.push_back("\n");
//
//}
//vector <Node*> preorderTraversal(Node* root)
//{
//	stack <Node*> Stack;
//	stack <string> brackets;
//	// 'Preorder'-> contains all the
//	// visited nodes
//	vector < Node* > Preorder;
//
//	Stack.push(root);
//
//	while (!Stack.empty()) {
//		Node* temp = Stack.top();
//		Stack.pop();
//		// store the key in preorder vector(visited list)
//		int maxSize; 
//		Preorder.push_back(temp);
//		// Push all of the child nodes of temp into
//		// the stack from right to left.
//		for (int i = (temp->getchildren()).size() -1; i>=0 ; i--) {
//			Stack.push((temp->getchildren())[i]);
//		}
//	}
//	return Preorder;
//}
//
//
//
//void printJson(Node* root, vector <string>& JsonString)
//{
//
//	//string t1 = (node->gettagname());
//	////t1 = replace(t1);
//	//JsonString.push_back("{");
//	//JsonString.push_back("\n");
//	//JsonString.push_back(t1);
//
//	////(CheckData(node, JsonString));
//	//for (int x = 0; x < node->getchildren().size(); x++)
//	//{
//	//	printJson((node->getchildren()[x]), JsonString);
//	//}
//	//JsonString.push_back("}");
//	vector <Node*> x = preorderTraversal(root);
//	stack <string> s;
//	
//	bool rep = false;
//	for (int i = 0; i < x.size(); i++)
//	{
//		if (i == 0)
//		{
//			JsonString.push_back("{");
//			s.push("}");
//
//		}
//		
//		if (x[i]->getchildren().size() != 0 && x[i]->getchildren()[0]->gettagname() != x[i]->getchildren()[1]->gettagname())
//		{
//			JsonString.push_back("{");
//			s.push("}");
//		}
//		if (x[i]->getchildren().size() != 0)
//		{
//
//			if (x[i]->getchildren()[0]->gettagname() == x[i]->getchildren()[1]->gettagname())
//			{
//				JsonString.push_back(x[i]->gettagname());
//				JsonString.push_back("{");
//				s.push("}");
//				JsonString.push_back(x[i]->getchildren()[0]->gettagname());
//				JsonString.push_back("[");
//				s.push("]");
//				rep = true;
//			}
//			else
//			{
//				rep = false;
//			}
//		}
//		
//		if (x[i]->getchildren().size() == 0)
//		{
//			if (!rep)
//			{
//				JsonString.push_back(x[i]->gettagname());
//			}
//			JsonString.push_back(x[i]->getdata());
//			JsonString.push_back(",");
//		}
//		
//	}
//}
//
//
