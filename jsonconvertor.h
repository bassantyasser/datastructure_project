#include "c:\users\world\Downloads\Caty.h"

vector <Node*> preorderTraversal(Node* root)
{
	stack <Node*> Stack;
	stack <string> brackets;
	// 'Preorder'-> contains all the
	// visited nodes
	vector < Node* > Preorder;

	Stack.push(root);

	while (!Stack.empty()) {
		Node* temp = Stack.top();
		Stack.pop();
		// store the key in preorder vector(visited list)
		int maxSize;
		Preorder.push_back(temp);
		// Push all of the child nodes of temp into
		// the stack from right to left.
		for (int i = (temp->getchildren()).size() - 1; i >= 0; i--) {
			Stack.push((temp->getchildren())[i]);
		}
	}
	return Preorder;
}

string replace(string t1) {
	t1.replace(0, 1, "\"");
	t1.replace(t1.length() - 1, 1, "\"");
	t1 = t1 + ":";
	return t1;
}

void printJson(Node* root, vector <string>& JsonString)
{


	vector <Node*> x = preorderTraversal(root);
	stack <string> s;
	stack <int> childrensize;
	string close;

	bool rep = false;
	for (int i = 0; i < x.size(); i++)
	{
		if (i == 0)
		{
			JsonString.push_back("{");
			JsonString.push_back("\n");


		}

		if (x[i]->getchildren().size() > 0)
		{

			if (x[i]->getchildren().size() == 1) {

				JsonString.push_back(replace(x[i]->gettagname()));
				JsonString.push_back("{");
				JsonString.push_back("\n");
				JsonString.push_back(replace(x[i]->getchildren()[0]->gettagname()));

				s.push("}");

			}
			if (x[i]->getchildren().size() > 1 && x[i]->getchildren()[0]->gettagname() != x[i]->getchildren()[1]->gettagname() && (x[i] != root)) {
				JsonString.push_back("{");
				JsonString.push_back("\n");
				JsonString.push_back(replace(x[i]->getchildren()[0]->gettagname()));


				s.push("}");
			}
		}

		if (x[i]->getchildren().size() != 0)
		{
			if (i == 0) {
				childrensize.push(x[i]->getchildren().size());
			}
			if (i != 0) {
				int z = childrensize.top() - 1;
				childrensize.pop();
				childrensize.push(z);
				childrensize.push(x[i]->getchildren().size());

			}
			if (x[i]->getchildren().size() > 1) {

				if ((x[i]->getchildren()[0]->gettagname() == x[i]->getchildren()[1]->gettagname()) || (x[i] == root))
				{
					if (x[i]->gettagname() == "<follower>") {
						JsonString.push_back("follower");
					}
					JsonString.push_back(replace(x[i]->gettagname()));

					JsonString.push_back("{");
					JsonString.push_back("\n");

					s.push("}");
					JsonString.push_back(replace(x[i]->getchildren()[0]->gettagname()));

					JsonString.push_back("[");
					JsonString.push_back("\n");

					s.push("]");

					rep = true;
				}

			}
			else
			{
				rep = false;
			}
		}

		if (x[i]->getchildren().size() == 0)
		{
			JsonString.push_back(x[i]->getdata());



			int z = childrensize.top() - 1;
			if (z == 0) {
				string t = s.top();
				JsonString.push_back(s.top());
				JsonString.push_back("\n");
				s.pop();
				if (t == "]") {
					JsonString.push_back(s.top());
					JsonString.push_back("\n");
					s.pop();
				}


			}
			else {

				JsonString.push_back(",");
				JsonString.push_back("\n");

			}
			childrensize.pop();
			childrensize.push(z);
			if (childrensize.top() == 0) {
				childrensize.pop();
				int x = childrensize.top();
				if (childrensize.top() == 0) {
					JsonString.push_back(s.top());
					s.pop();
					JsonString.push_back(",");
					JsonString.push_back("\n");

				}
				else
				{
					childrensize.push(x);
				}

			}

		}


	}
	while (!s.empty()) {
		JsonString.push_back(s.top());
		JsonString.push_back("\n");

		s.pop();
	}

	JsonString.push_back("}");
	JsonString.push_back("\n");

}

//string JsonOutput(string s)
//{
//	fstream file = getFile(s);
//	vector <string> data = formatting(file);
//	Node* root = new Node();
//	root->settagname(data[0]);
//	int i{ 1 };
//	xmltree(root, data, i, root);
//	vector <string> outputJson;
//	printJson (root, outputJson);
//	return VectToStr(outputJson);
//
//}
