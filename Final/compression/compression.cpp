#include <iostream>
#include <string>
#include <queue>
#include <map>
#include <math.h>
#include <compression.h>

using namespace std;




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


string decode(minHeapNode* root , string s)
{
    // i passed the encoded string to the function which contains the ones and zeros of the huffman
    // i made a node than iterates through the index and found the suitable one the decompress it
    string decode = "";
    minHeapNode* temp = root;
        for (int i=0;i<s.size();i++)
        {
            if (s[i] == '0')
               temp = temp->left;
            else
               temp = temp->right;

            if (!(temp->left && temp->right))
            {
                decode += temp->c;
                temp = root;
            }
        }
        return decode;
}

string HuffmanCoding(string text)
{
    map<char, int> freq_arr;

    int compvalue =0;

    for(size_t i=0; i<text.length(); i++)
    {
        char ch = text[i];
        freq_arr[ch] += 1;
    }

    // minheap
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


    auto f1 = freq_arr.begin();
    auto f2 = huffmanCode.begin();

    auto e1 = freq_arr.end();
    auto e2 = huffmanCode.end();

    // iterate through the freq and the huffman map
    // multiply the freq of each character by its string
    for(;f1 != e1 && f2 != e2 ; ++f1 , ++f2 ){
        compvalue += f1->second * length(f2->second);

    }
    int defvalue = (text.length())*8;
    
    
    string temp = to_string(defvalue);
    string temp2 = to_string(compvalue);
    string output = "Size before compression is " +temp+ " Bit\n" ;
    output += "Size after compression is " +temp2+ " Bit\n";


    //the compressed number of bits after huffman compression
    string encodedStr;
    for(char i: text){
        encodedStr += huffmanCode[i];
    }
    output += "The encoded string is:\n";
    output += encodedStr;
    output += "\n";
    output += "The decoded string is:\n";

    // the decoded string aka the original text
    string decoded = decode(root , encodedStr);
    output += decoded;


    /*for(auto pair: huffmanCode)
    {
        output += pair.first+ ":"  +pair.second+ "\n";
    }
    cout << "_________________" << endl;
    for(auto pair: freq_arr)
    {
        cout << pair.first << ":" << pair.second << endl;
    }*/
    return output;
    
}



