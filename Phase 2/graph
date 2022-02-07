vector <vector <int>> MakeList(vector <Node*> tr)
{   
    vector <vector <int>> list;
    list.resize(10, vector <int>());
    int l = 0;
    int i = 0;
    while (i < tr.size() -1 )
    {
        if (tr[i]->gettagname() == "<user>")
        {
            while (i < tr.size() - 1 && tr[i + 1]->gettagname() != "<user>" )
            {
                
                if (tr[i + 1]->gettagname() == "<id>" )
                {
                    
                    list[l].push_back(stoi(tr[i + 1]->getdata()));
                   
                }
                i++;
                
            }
            l++;
        }
        else { i++; }
    }
    return list;
}

void graph(string s)
{
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
    vector <Node*> t = preorderTraversal(root);
    vector <vector <int>> v = MakeList(t);


}
