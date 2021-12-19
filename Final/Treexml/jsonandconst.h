
#include "Treexml.h"
#include <string>
#include <vector>
#include <fstream>
#include <stack>
#include "formatting.h"
#include <consistency.h>

using namespace std;

string replace(string t1) {        //to replace the open and closing tages with (")
    t1.replace(0, 1, "\"");
    t1.replace(t1.length() - 1, 1, "\"");
    t1 = t1 + ":";
    return t1;
}

static void xmltree(Node* node, vector <string> xml, int& i, Node* root) {     //the function that transfer the xml file to tree of nodes of parents and childs with recursion


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
void printJson(Node* root, vector <string>& JsonString)         //takes an input vector of string and return it 
{


    vector <Node*> x = preorderTraversal(root);
    stack <string> s;   //stack for closing brackets
    stack <int> childrensize;    //stack for children size of the node
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
            if (x[i]->getchildren().size() > 1 && x[i]->getchildren()[0]->gettagname() != x[i]->getchildren()[1]->gettagname() && (x[i] != root)) {     //check if they don't have the same tagname
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

                if ((x[i]->getchildren()[0]->gettagname() == x[i]->getchildren()[1]->gettagname()) || (x[i] == root))          //check if they have the same tagname to create array of children
                {
                    /*if (x[i]->gettagname() == "<follower>") {
                        JsonString.push_back("follower");
                    }*/
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
            for (int j = 0; j < childrensize.size(); j++) {
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

    }



    while (!s.empty()) {
        JsonString.push_back(s.top());
        JsonString.push_back("\n");

        s.pop();
    }

    JsonString.push_back("}");
    JsonString.push_back("\n");

}

string JsonOutput(string s)                             //takes the output from print json and convert it to a string that can be called using the gui
{
    fstream file = getFile(s);
    vector <string> data;
    string klk = mediator_to_consist(s, data);
    for (int i = 0; i < data.size(); i++)
    {
        data[i] = no_space(data[i]);
    }
    Node* root = new Node();
    root->settagname(data[0]);
    int i{ 1 };
    xmltree(root, data, i, root);
    vector <string> outputXml;
    printJson(root, outputXml);
    vector <string> h;
    string out = VectToStr(outputXml);
    return out;

}

stack <string> tags;
