
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

vector <Node*> preorderTraversal(Node* root)                     //depth traversal but we called it pre-order
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
string VectToStr(vector <string> vect)
{
    string s;
    for (int i = 0; i < vect.size(); i++)
    {
        s = s + vect[i];
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
string no_space(string& s)
{
    string result = "";
    int i = 0;
    for (; i < s.size(); i++)
        if (s[i] != ' ')
            break;

    for (; i < s.size(); i++)
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
        return errors + flag;
    }

}
string XmlOutput(string s)
{
    //fstream file = getFile(s);
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
    printXml(root, outputXml);
    vector <string> h;
    string out = VectToStr(outputXml);
    return mediator_to_consist(out, h);
}


