#include <iostream>
#include <string>
#include <map>

using namespace std;


struct minHeapNode
{

    char c;
    int freq;
    minHeapNode *left;
    minHeapNode *right;

};

struct compare
{

    bool operator()(minHeapNode* l, minHeapNode* r)
    {
        return l->freq > r->freq;
    }

};


minHeapNode* getNode(char c, int freq, minHeapNode* left, minHeapNode* right);

int length(string str);

void encode(minHeapNode* root, string s , map<char, string> &huffmanCode);

int HuffmanCoding(string text);



