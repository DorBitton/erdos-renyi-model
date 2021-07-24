// Algorithm2 hw.cpp : This file contains the 'main' function. Program execution begins and ends there.
/*
--------------------------------------------------------------------------------------------------------------
                            Declaration:
            This work was made by Dor Bitton, HIT student.
I took some of the ideas on how to approach this from Web searchs, but the program was written by me manualy.

--------------------------------------------------------------------------------------------------------------
*/

#include <iostream>
#include <math.h>
#include <random>
#include <fstream>
#include "GraphHeader.h"


std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<> options_of_prob(0, 1); // 0.0 <= options_of_prob < 1 ( = 0.999...)

using namespace std;

//Functions declaration:
void firstOption(int);
void secondOption(int);
void thirdOption(int);
void exprotResultToCSV(double*, double*, string);
Graph build_random_graph(int, double);
int connectivity(Graph);
int is_isolated(Graph);
int diamater(Graph);
double oneAndThreeThreshold(Graph);
double secondThreshold(Graph);
bool check_random_with_prob(double);
int checkFirstOption(Graph, double);
int checkThirdOption(Graph, double);
int checkSecondOption(Graph, double);






void main()
{
    int samplesNumber = 500; //According to exercise
    int option = 0, flag = 0;
    cout << endl << endl << endl;
    cout << "Aglorithms 2 - Erdos-Renyi model" << endl;
    cout << endl << endl << endl;
    do {
        cout << "Choose which option you would like to check: 1, 2, 3. \n\tType 0 if you want to exit." << endl;
        cin >> option;

        switch (option)
        {
        case 1: firstOption(samplesNumber);
            break;
        case 2: secondOption(samplesNumber);
            break;
        case 3: thirdOption(samplesNumber);
            break;
        case 0: flag = -1;
            break;
        }

    } while (flag == 0);

}


//          Main part

void firstOption(int samplesNumber)
{
    //Vertex = 1000 --> threshold1 = lnV / V = ln(1000) / 1000 = 0.00690775...

    cout << endl;
    cout << "You chose the first option." << endl << "Here we will check the probabilty of graph connectivity." << endl;
    cout << endl;

    double firstOptionProbList[] = { 0.001, 0.002, 0.003, 0.004 , 0.005, 0.007, 0.0075, 0.008, 0.0085, 0.009 };
    double* firstOptionResult = new double[10];
    int returnF;

    for (int i = 0; i < 10; i++)
    {
        pBar bar; //ProgressBar
        cout << "Number of samples: "<< samplesNumber << ", in Probabilty: " << firstOptionProbList[i] << endl;
        double resultCounter = 0;
        for (int j = 0; j < samplesNumber; j++)
        {
            //ProgressBar
            bar.update(1);
            bar.print();
            cout << " " << j + 1 << "/" << samplesNumber << "\r";
            Graph g = build_random_graph(1000, firstOptionProbList[i]);
            returnF = checkFirstOption(g, firstOptionProbList[i]);
            if (returnF == 1)
                resultCounter++;
        }
        cout << endl;
        firstOptionResult[i] = resultCounter / samplesNumber; // Ratio of available graphs / existing graphs
    }
    exprotResultToCSV(firstOptionProbList, firstOptionResult, "firstThresholdResults.csv");
}

void secondOption(int samplesNumber)
{
    //Vertex = 1000 --> threshold2 = sqrt(2ln(V) / V) = sqrt(2ln(1000) / 1000) = 0.117539

    cout << endl;
    cout << "You chose the third option." << endl << "Here we will check the probabilty if graph diameter is equal to 2 or higher." << endl;
    cout << endl;

    double secondOptionProbList[] = { 0.03, 0.04, 0.05, 0.06, 0.07, 0.13, 0.16, 0.19, 0.2, 0.3 };
    double* secondOptionResult = new double[10];
    int returnF;
    for (int i = 0; i < 10; i++)
    {
        pBar bar; //ProgressBar
        cout << "Number of samples: " << samplesNumber << ", in Probabilty: " << secondOptionProbList[i] << endl;
        double resultCounter = 0;

        for (int j = 0; j < samplesNumber; j++)
        {
            //ProgressBar
            bar.update(1);
            bar.print();
            cout << " " << j + 1 << "/" << samplesNumber << "\r";
            Graph g = build_random_graph(1000, secondOptionProbList[i]);
            returnF = checkSecondOption(g, secondOptionProbList[i]);
            if (returnF == 1)
                resultCounter++;
        }
        secondOptionResult[i] = resultCounter / samplesNumber; // Ratio of available graphs / existing graphs
    }
    exprotResultToCSV(secondOptionProbList, secondOptionResult, "secondThresholdResults.csv");

}

void thirdOption(int samplesNumber)
{
    //Vertex = 1000 --> threshold3 = lnV / V = ln(1000) / 1000 = 0.00690775...

    cout << endl;
    cout << "You chose the second option." << endl << "Here we will check the probabilty of isolated vertex in a graph." << endl;
    cout << endl;

    double thirdOptionProbList[] = { 0.001, 0.002, 0.003, 0.004 , 0.005, 0.007, 0.0075, 0.008, 0.0085, 0.009 };
    double* thirdOptionResult = new double[10];
    int returnF;

    for (int i = 0; i < 10; i++)
    {
        pBar bar; //ProgressBar
        cout << "Number of samples: " << samplesNumber << ", in Probabilty: " << thirdOptionProbList[i] << endl;
        double resultCounter = 0;

        for (int j = 0; j < samplesNumber; j++)
        {
            //ProgressBar
            bar.update(1);
            bar.print();
            cout << " " << j + 1 << "/" << samplesNumber << "\r";
            Graph g = build_random_graph(1000, thirdOptionProbList[i]);
            returnF = checkThirdOption(g, thirdOptionProbList[i]);

            if (returnF == 1)
                resultCounter++;
        }
        thirdOptionResult[i] = resultCounter / samplesNumber; // Ratio of available graphs / existing graphs
    }
    exprotResultToCSV(thirdOptionProbList, thirdOptionResult, "ThirdThresholdResults.csv");
}


//          Graph related part


Graph build_random_graph(int v, double p) {
    Graph g(v);
    for (int i = 0; i < v; i++)
    {
        for (int j = i + 1; j < v; j++)
        {
            if (check_random_with_prob(p)) { // If random probabilty is lower or equal to preset probabilty, than add edge
                g.addEdge(i, j);
            }
        }
    }
    return g;
}


int connectivity(Graph g) {
    int* checkDistance = g.BFS(0);
    for (int i = 0; i < g.getV(); i++)
    {
        if (checkDistance[i] == 0)
            return 0;
    }
    return 1;
}

int is_isolated(Graph g)
{
    for (int i = 0; i < g.getV();i++)
        if (g.checkVertexEdge(i).empty()) //empty() checks if array is empty, if so there are no edges to a given vertex -> vertex is isolated.
            return 1;
    return 0; // Else
}

int diamater(Graph g)
{
    //I didnt know how to build this function. I know I need to use BFS algorithm, didnt have enough time to think how.
    //Second option checking is unavailable due to that. 
    return 1;
}

bool check_random_with_prob(double p) //Random a number from 0 to 0.99, if <= p --> need to create edge
{
    double randNumb = options_of_prob(gen);

    if (randNumb <= p)
        return 1;
    else
        return 0;
}


//          Evalutating options + Calculations

int checkFirstOption(Graph g, double p)
{
    int checkConnectivity = connectivity(g);
    double tresholdCalc = oneAndThreeThreshold(g);

    if ((p < tresholdCalc && checkConnectivity == 0) || (p > tresholdCalc && checkConnectivity == 1))
        return 1;
    else
        return 0;

}

int checkSecondOption(Graph g, double p)
{
    int checkDiamater = diamater(g);
    double tresholdCalc = secondThreshold(g);

    if ((p > tresholdCalc && checkDiamater == 2) || (p < tresholdCalc && checkDiamater > 2))
        return 1;
    else
        return 0;
}

int checkThirdOption(Graph g, double p)
{
    int checkIsolated = is_isolated(g);
    double tresholdCalc = oneAndThreeThreshold(g);

    if ((p < tresholdCalc && checkIsolated == 1) || (p > tresholdCalc && checkIsolated == 0))
        return 1;
    else
        return 0;
}

double oneAndThreeThreshold(Graph g)
{
    //Threshold calculations
    int V = g.getV();
    return (log(V) / V);
}

double secondThreshold(Graph g)
{
    //Threshold calculations
    int V = g.getV();
    return (sqrt(2 * log(V) / V));
}





void exprotResultToCSV(double* pList, double* result, string fileName)
{
    ofstream newFile(fileName);
    newFile << "Probabilty: ,";

    for (int i = 0; i < 10; i++)
    {
        newFile << pList[i] << ",";
    }
    newFile << endl;

    newFile << "Evaluation of probablity: ,";
    for (int i = 0; i < 10; i++)
    {
        newFile << result[i] << ",";
    }
    newFile << endl;

    newFile.close();

}
