#include <iostream>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <cstring>
#include <cctype>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/named_function_params.hpp>

using namespace std;
using namespace boost;

struct wordVertex
{
    string wordName;
    int wordLen;
};

typedef boost::adjacency_list<boost::vecS, boost::vecS,
                            boost::undirectedS,
                            wordVertex,
                            boost::no_property> MyGraphType;

class MyVisitor : public boost::default_bfs_visitor
{
public:
  void discover_vertex(wordVertex v, const MyGraphType& g) const
  {
    return;
  }
};

int main()
{
    //typedef boost::graph_traits<MyGraphType>::vertex_descriptor wordVertex;

    MyGraphType G;
    //file read
    ifstream inFile;
    inFile.open("dictionary.txt");
    if (!inFile)
    {
        cerr << "Unable to open file input-small.txt";
        exit(1);
    }

    //All words are in a Array
    std::map<string,vector<string> > dict;
    string thisWord;
    string wordKey;
    string tempWord;
    wordVertex vd;
    while (getline(inFile, thisWord))
    {
        for(int i =0;i <thisWord.length();i++)
        {
            //get word to be replaced by pos with a wildcard
            for(int i=0;thisWord[i];i++) thisWord[i] = tolower(thisWord[i]);
            tempWord = thisWord;
            thisWord[i] = '*';
            wordKey = thisWord;
            thisWord = tempWord;

            //Adds the key if it doesn't exist and appends
            dict[wordKey].push_back(thisWord);
        }
    }
/*
    //loop through map to print
    for(const auto&pair : dict)
    {
        cout << "key: " << pair.first << " value: [ ";
        for ( size_t i = 0; i < pair.second.size(); ++i)
            cout << pair.second[i] << " ";
        cout << "]" << endl;
    }
*/
    int v1;
    int v2;
    //loop through map for making vertices edges
    for(const auto&pair : dict)
    {
        for ( size_t i = 0; i < 1; ++i)    //loops through words and makes an edge
        {
            vd.wordName = pair.second[i];
            vd.wordLen = pair.second[i].length();
            v1 = add_vertex(G);
            G[v1] = vd;
            for (size_t j = 1; j < pair.second.size(); ++j)
            {
                if (pair.second[i] != pair.second[j])
                {
                    vd.wordName = pair.second[j];
                    vd.wordLen = pair.second[j].length();
                    v2 = add_vertex(G);
                    G[v2] = vd;
                    add_edge(v1, v2, G).first;
                }
            }
        }
    }

    //Prints out vertex and edges
    auto vpair = vertices(G);
    int i = 0;
    for(auto iter=vpair.first; iter!=vpair.second; iter++)
        {
            std::cout << "vertex " << *iter << " " << get(&wordVertex::wordName, G)[i] << std::endl;
            i++;
        }
    auto epair = edges(G);
    for(auto iter=epair.first; iter!=epair.second; iter++) {
    std::cout << "edge " << source(*iter, G) << " - " << target(*iter, G) << std::endl;
  }

    //***Had excessive issues getting Boost to work properly. Could not get BFS to work properly.
    //boost functions were unclear and hard to follow***

    //boost::breadth_first_search(G, a, boost::visitor(vis));


/*
    //Get input file
    ofstream outFile;
    outFile.open("output.txt");

    //Print out short path of each bottom element.
    for (int j = 0; j < col;j++)
    {
        cout << endl;
        pathFinder(newMatrix,row-1,j, outArray);
        for (int j = 0;j<row;j++)
        {
            outFile << outArray[j] << " ";
        }
        outFile << endl;
    }



    outFile.close();
*/
    return 0;
}
