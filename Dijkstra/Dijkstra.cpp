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
vector<vii> AdjacentList2;
// My vector of distances.
vector<int> vec;

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
    for(i = 0; i < AdjacentList.size(); ++i) {
        cout << i << "-> ";
        for (j = 0; j < AdjacentList[i].size(); ++j){
            cout << AdjacentList[i][j].second << " ";
        }
        cout << endl;

    }
}

/*
 * Print a vector if integer
 */
void printVec(vector<int> v) {
    int i;
    cout << "vec: ";
    for(i = 0; i < v.size(); ++i){
        cout << ifINF(v[i]) << " ";
    }
}

/*
 * Algorithm of Dijkstra.
 */
void dijkstra(int currentNode) {
    int i;
    for (i = 0; i < AdjacentList[currentNode].size(); ++i){
        int adjNode = AdjacentList[currentNode][i].second; // get the adjacent node.
        int pathWeight = AdjacentList[currentNode][i].first + vec[currentNode]; // get the total cost to reach the adjacent node.

        cout << "   get node " << adjNode << " / " << pathWeight << endl;

        if(vec[adjNode] > pathWeight){ // if the current total cost is cheap than the old one... change it!.
            cout << "     CHANGE " << ifINF(vec[adjNode]) << " for " << pathWeight << endl;
            vec[adjNode] = pathWeight;
        }
        dijkstra( adjNode );
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

    //initialize a vector of wieght
    vec.assign(6, INT_MAX);

    //the distance of the origin is zero.
    int initialNode = 0;
    vec[initialNode] = 0;
    dijkstra( initialNode );

    printVec(vec);
    return 0;
}
