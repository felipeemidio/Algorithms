#include<iostream>
#include<vector>
#include<climits>
#include<sstream>

using namespace std;
//Defining types
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

// My adjacent list
vector<vii> AdjacentList;
// My vector of distances.
vector<int> vec;
vector<int> parent;

/*
 * Say if the number is equivalent to INT_MAX(in this case our infinite) or not.
 */
string ifINF(int i) {
    if ( i == INT_MAX ) {
        return "INF";
    } else {
        ostringstream convert;
        convert << i;
        return convert.str();
    }
}

/*
 * Print the AdjacentList. (only the nodes without the weight).
 */
void printAL() {
    int i, j;
    cout << "--------------" << endl;
    for(i = 0; i < AdjacentList.size(); ++i) {
        cout << i << "-> ";
        for (j = 0; j < AdjacentList[i].size(); ++j){
            cout << AdjacentList[i][j].second << " ";
        }
        cout << endl;

    }
    cout << "--------------" << endl;
}

/*
 * Print a vector if integer.
 */
void printVec(vector<int> v) {
    int i;
    cout << "vec: ";
    for(i = 0; i < v.size(); ++i){
        cout << ifINF(v[i]) << " ";
    }
    cout << endl;
}

/*
 * print the shortest path.
 */
void printShortestPath(int originNode, int destinyNode){
    vector<int> result;
    int destiny = destinyNode;
    int i;
    for (i = 0; destinyNode != originNode; ++i){
        result.push_back(parent[destinyNode]);  //get the best father.
        destinyNode = parent[destinyNode]; //next we'll get the best father of the best father.

        if (destinyNode == INT_MAX) {
            cout << "Holy shit, it crashed!" << endl;
            return ;
        }
    }
    cout << "Shortest Path "; //printing the way found in the inverse order.
    for(i = result.size()-1; i >= 0; --i) {
        cout << result.at(i) << " ";
    }
    cout << destiny << endl;

}
/*
 * Algorithm of Dijkstra.
 */
void dijkstra(int currentNode) {
    int i;
    for (i = 0; i < AdjacentList[currentNode].size(); ++i){
        int adjNode = AdjacentList[currentNode][i].second; // get the adjacent node.
        int pathWeight = AdjacentList[currentNode][i].first + vec[currentNode]; // get the total cost to reach the adjacent node.

        //cout << "   get node " << adjNode << " / " << pathWeight << endl;

        if(vec[adjNode] > pathWeight){ // if the current total cost is cheap than the old one... change it!.
            //cout << "     CHANGE " << ifINF(vec[adjNode]) << " for " << pathWeight << endl;
            vec[adjNode] = pathWeight;

            parent[adjNode] = currentNode; //hold who is the better father.
        }
        dijkstra( adjNode ); //recursive call.
    }
}

/*
 * Main program loop.
 */
int main() {
    //Assing a 6 empty vectors for the AdjacentList
    AdjacentList.assign(6, vii());

    //creating the graph 1
    AdjacentList[0].push_back(ii(1,1));
    AdjacentList[0].push_back(ii(2,2));
    AdjacentList[1].push_back(ii(5,3));
    AdjacentList[1].push_back(ii(4,4));
    AdjacentList[2].push_back(ii(3,3));
    AdjacentList[2].push_back(ii(2,4));
    AdjacentList[3].push_back(ii(3,5));
    AdjacentList[4].push_back(ii(1,5));
    /*
    //creating the graph 2
    AdjacentList[0].push_back(ii(2,1));
    AdjacentList[0].push_back(ii(1,4));
    AdjacentList[1].push_back(ii(4,3));
    AdjacentList[3].push_back(ii(1,2));
    AdjacentList[4].push_back(ii(2,3));
    AdjacentList[4].push_back(ii(1,5));
    AdjacentList[5].push_back(ii(3,3));
    */
    printAL();

    //initialize a vector of wieght, where 6 is the number of nodes of the graph.
    vec.assign(6, INT_MAX);
    parent.assign(6, INT_MAX);

    /*
     * I'm not verify if the input is correct, so don't be a dumbass.
     */
    int initialNode, finalNode;
    cout << "Choose the origin Node between 0 and 5: ";
    cin >> initialNode;
    cout << "Choose the destiny Node between 0 and 5: ";
    cin >> finalNode;

    //the distance of the origin is zero.
    vec[initialNode] = 0;
    dijkstra( initialNode );

    //this prints are only for control.
    printVec(vec);
    printVec(parent);

    //Show the best (minimun) path
    printShortestPath(initialNode, finalNode);

    return 0;
}
