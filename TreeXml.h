#pragma once
#include <string>
#include <stack>
#include <iostream>
#include <vector>
#include <string.h>
#include <string>
#include <vector>
using namespace std;

class Node
{
	//each node have a tagname,  data
	//each node may be a parent or child in the tree
private:
	string tagname;
	string data;
	vector <Node*> children;


public:

	Node() {
		tagname = "";
		data = "";
	}
	Node(string tagname, string data) {
		this->tagname = tagname;
		this->data = data;

	}

	vector <Node*> getchildren() {
		return children;
	}



	string gettagname() {
		return tagname;
	}

	string getdata() {
		return data;
	}

	void settagname(string tagname) {
		this->tagname = tagname;
	}

	void setdata(string data) {
		this->data = data;
	}
	void addchild(Node* child, int& i) {
		this->children.push_back(child);
		i++;
		return;

	}

	static void addsamechild(Node* node, Node* child) {

		Node* samechild;
		node->getchildren().push_back(samechild);
		int static x = 0;
		node->addchild(child, x);


	};
};

class Tree
{
private:
	Node root;
public:
	Node getroot() {
		return root;
	}

};
