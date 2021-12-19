#include <string>
#include <vector>
#include <fstream>
#include <stack>
#include "formatting.h"




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


string CheckConsistency(fstream& xmlFile);

fstream getFile(string input);

string VectToStr(vector <string> vect);

string no_space(string& s);

static void xmltree(Node* node, vector <string> xml, int& i, Node* root);

void printXml(Node* node, vector<string>& XmlString);

vector <Node*> preorderTraversal(Node* root);

string replace(string t1);

void printJson(Node* root, vector <string>& JsonString);

string JsonOutput(string s);

fstream getFile(string input);

string detect(string s);

string VectToStr(vector <string> vect);

void find_and_replace(std::string& file_contents, const std::string& s1, const std::string& s2);

string no_space(string& s);

string CheckConsistency(fstream& xmlFile);

string XmlOutput(string s);

