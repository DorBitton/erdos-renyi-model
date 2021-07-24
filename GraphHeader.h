
#pragma once
#include <iostream>
#include <set>
using namespace std;




class Graph
{
private:
    int V;    // No. of vertices
    //We use set because we dont need duplicate edges.
    set<int>* edges;

public:
    //Constructors
    Graph();
    Graph(int V);
    Graph(const Graph& lastG);
    Graph& operator= (const Graph& lastG);


    //Destructor
    ~Graph();


    //Functions declaration
    int addEdge(int sourceVertex, int nextE); // function to add an edge to graph
    int getV() const;
    int* BFS(int sourceVertex) const; // BFS traversal from a given source 
    set<int>& checkVertexEdge(int vertex) const;


};

//This class is just for output cosmetics. (most of the credit goes to StackOverflow)
class pBar {
public:
    void update(double newProgress) {
        currentProgress += newProgress;
        amountOfFiller = (int)((currentProgress / neededProgress) * (double)pBarLength);
    }
    void print() {
        currUpdateVal %= pBarUpdater.length();
        cout << "\r" //Bring cursor to start of line
            << firstPartOfpBar; //Print out first part of pBar
        for (int a = 0; a < amountOfFiller; a++) { //Print out current progress
            cout << pBarFiller;
        }
        cout << pBarUpdater[currUpdateVal];
        for (int b = 0; b < pBarLength - amountOfFiller; b++) { //Print out spaces
            cout << " ";
        }
        cout << lastPartOfpBar //Print out last part of progress bar
            << " (" << (int)(100 * (currentProgress / neededProgress)) << "%)" //This just prints out the percent
            << flush;
        currUpdateVal += 1;
    }
    std::string firstPartOfpBar = "[", //Change these at will (that is why I made them public)
        lastPartOfpBar = "]",
        pBarFiller = "|",
        pBarUpdater = "/-\\|";
private:
    int amountOfFiller,
        pBarLength = 50, 
        currUpdateVal = 0; 
    double currentProgress = 0, 
        neededProgress = 500; //We check 500 options, we can change it accordingly. 
};