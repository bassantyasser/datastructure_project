#include <iostream>
#include <string>
#include <queue>
#include <map>
#include <math.h>
#include <compression.h>

using namespace std;

int compvalue =0;


minHeapNode* getNode(char c, int freq, minHeapNode* left, minHeapNode* right)
{
    minHeapNode* node = new minHeapNode();

    node->c = c;
    node->freq = freq;
    node->left = left;
    node->right = right;

    return node;
}



// this is used to calculate the length of the string.
int length(string str){
    int size =str.length();
    return size;
}



void encode(minHeapNode* root, string s , map<char, string> &huffmanCode)
{
    if (root == nullptr)
        return;

    if (!root->left && !root->right) {
        huffmanCode[root->c] = s;
    }

    encode(root->left, s + "0", huffmanCode);
    encode(root->right, s + "1", huffmanCode);
}


int HuffmanCoding(string text)
{
    map<char, int> freq_arr;

    compvalue =0;

    for(int i=0; i<text.length(); i++)
    {
        char ch = text[i];
        freq_arr[ch] += 1;
    }


    priority_queue<minHeapNode*, vector<minHeapNode*>, compare> perQUEUE;


    for (auto pair: freq_arr) {
        perQUEUE.push(getNode(pair.first, pair.second, nullptr, nullptr));
    }

    while (perQUEUE.size() != 1)
    {

        minHeapNode *left = perQUEUE.top();
        perQUEUE.pop();
        minHeapNode *right = perQUEUE.top();
        perQUEUE.pop();

        int sum = left->freq + right->freq;
        perQUEUE.push(getNode('\0', sum, left, right));
    }


    minHeapNode* root = perQUEUE.top();

    map<char, string> huffmanCode;
    encode(root, "", huffmanCode);




    //cout << "Number of bit in the original text is : " << (text.length())*8 << " bit." << endl;

    auto f1 = freq_arr.begin();
    auto f2 = huffmanCode.begin();

    auto e1 = freq_arr.end();
    auto e2 = huffmanCode.end();


    for(;f1 != e1 && f2 != e2 ; ++f1 , ++f2 ){
        compvalue += f1->second * length(f2->second);

    }
    /*for(auto pair: huffmanCode)
    {
        cout << pair.first << ":" << pair.second << endl;
    }
    cout << "_________________" << endl;
    for(auto pair: freq_arr)
    {
        cout << pair.first << ":" << pair.second << endl;
    }*/
    return compvalue;
}



