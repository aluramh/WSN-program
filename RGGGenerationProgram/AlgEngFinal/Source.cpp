#include <iostream>
#include <fstream>
#include "ListaLineal.h"
#include <list>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>  
#include <vector>
#include <algorithm>

#define Q_NODES 16000
#define M_PI 3.14159265358979323846  /* pi */
#define Q_COLORS 100

using namespace std;

struct Sensors {
	unsigned int id;
	double x, y, z;
};

//Array of edges in dynamic memory. 
//e.g. edges[33] contains a list with all the edges of node with ID 33
vector<list<Sensors>> edges(Q_NODES);
vector<list<Sensors>> originalEdges;
vector<unsigned int>degrees(Q_NODES);
vector<unsigned int>originalDegrees(Q_NODES);
unsigned int *smallestLast;
int *coloring = new int[Q_NODES];
vector<Sensors> nodeInfo(Q_NODES);

//Declare list of nodes
list<Node> myList;

//List of terminal clique
list<int> terminalClique;

//Degree bucket
list<unsigned int> *bucketDegrees;

int colorsNeeded = 1;
char type;
int maximumDegree = 0;
int maximumDegreeWhenDeleted = 0;
int minimumDegree = Q_NODES;
int terminalCliqueSize = 0;
int maxColorClassSize = 0;
unsigned int edgesLargestBipartite = 0;
unsigned int edgesLargestBipartite2 = 0;
double backboneCoverage = 0.0;
double backboneCoverage2 = 0.0;
int maxDegreeNode = 0;
int minDegreeNode = 0;
double radius;

double random() {
	return (double)rand() / (double)RAND_MAX;
}
bool xcompare(Sensors lhs, Sensors rhs) {
	return lhs.x < rhs.x;
}
double distanceBetweenNodes(Node &a, Node &b) {
	return sqrt(pow((a.getX() - b.getX()), 2) + pow((a.getY() - b.getY()), 2) + pow((a.getZ() - b.getZ()), 2));
}
void addEdge(int a, int b) {
	edges[a].push_front(nodeInfo[b]);
}
void displayList(list<Sensors> myList) {
	for (list<Sensors>::iterator it = myList.begin(); it != myList.end(); it++) {
		cout << (*it).id << ", ";
	}
}
void showDegrees() {
	for (int i = 0; i < Q_NODES; i++) {
		cout << i << ": " << degrees[i] << " Original:" << originalDegrees[i] << endl;
	}
}
void writeColorSetSize(vector<int> &colorInfo) {
	ofstream myfile;
	myfile.open("colorsets.txt");
	for (int i = 0; i < colorsNeeded; i++) {
		myfile << i << " " << colorInfo[i] << endl;
	}
	myfile.close();
}
void writeDegrees() {
	ofstream myfile;
	myfile.open("degrees.txt");
	myfile << "id D origDeg\n";
	for (int i = 0; i < Q_NODES; i++) {
		myfile << i << " " << degrees[i] << " " << originalDegrees[i] << endl;
	}
	myfile.close();
}
double averageDegree() {
	double accum = 0;
	for (int i = 0; i < Q_NODES; i++) {
		accum += originalDegrees[i];
	}
	return accum / Q_NODES;
}
void displayAdjacenecyList() {
	int i = 0;
	for (list<Node>::iterator it = myList.begin(); it != myList.end(); it++) {
		cout << (*it).getInfo() << "-> ";
		displayList(edges[i]);
		i++;
		cout << endl;
	}
}
void displayAdjacenecyList2() {
	int i = 0;
	for (list<Node>::iterator it = myList.begin(); it != myList.end(); it++) {
		cout << (*it).getInfo() << "-> ";
		displayList(originalEdges[i]);
		i++;
		cout << endl;
	}
}
double calcDistance(Sensors e1, Sensors e2) {
	double x = e2.x - e1.x;
	double y = e2.y - e1.y;
	double z = e2.z - e1.z;
	return (x*x) + (y*y) + (z*z);
}
void connectNodes3D() {
	//Create copy
	vector<Sensors> sorted = nodeInfo;
	//Sort copy by X coord
	sort(sorted.begin(), sorted.end(), xcompare);
	//Calculate R^2
	double r2 = radius*radius;
	for (int i = 0; i < Q_NODES; i++) {
		for (int j = i + 1; j < Q_NODES; j++) {
			if ((sorted[j].x - sorted[i].x) > radius) {
				break;
			}
			else {
				double euclideanDist = calcDistance(sorted[i], sorted[j]);
				if (euclideanDist < r2) {
					addEdge(sorted[i].id, sorted[j].id);
					addEdge(sorted[j].id, sorted[i].id);
					degrees[sorted[i].id]++;
					degrees[sorted[j].id]++;
				}
			}
		}
	}

	/*Obsolete
	int i = 0;
	//O(n^2)
	for (list<Sensors>::iterator A = myList.begin(); A != myList.end(); A++) {
		degrees[i] = 0;
		originalDegrees[i] = 0;
		for (list<Sensors>::iterator B = myList.begin(); B != myList.end(); B++) {
			double distance = pow(((*A).getX() - (*B).getX()), 2) + pow(((*A).getY() - (*B).getY()), 2) + pow(((*A).getZ() - (*B).getZ()), 2);
			if ((distance <= rs) && ((*A).getInfo() != (*B).getInfo())) {
				addEdge(*A, *B);
				degrees[i]++;
				originalDegrees[i]++;
			}
		}
		i++;
	}
	*/
}

void connectNodes2D(double r) {
	//Create copy of nodes
	vector<Sensors> sorted = nodeInfo;
	//Sort copy by X coordinates
	sort(sorted.begin(), sorted.end(), xcompare);
	//Calculate R^2
	double r2 = radius*radius;

	for (int i = 0; i < Q_NODES; i++) {
		for (int j = i + 1; j < Q_NODES; j++) {
			if ((sorted[j].x - sorted[i].x) > radius) {
				break;
			}
			else {
				double euclideanDist = calcDistance(sorted[i], sorted[j]);
				if (euclideanDist < r2) {
					addEdge(sorted[i].id, sorted[j].id);
					addEdge(sorted[j].id, sorted[i].id);
					degrees[sorted[i].id]++;
					degrees[sorted[j].id]++;
				}
			}
		}
	}
}
void displayNodes(list<Node> myList) {
	for (list<Node>::iterator it = myList.begin(); it != myList.end(); it++) {
		cout << (*it).getInfo() << ": (" << (*it).getX() << ", " << (*it).getY() << ", " << (*it).getZ() << ")" << endl;
	}
}
void createRGG() {
	srand(time(NULL));
	for (int i = 0; i < Q_NODES; i++) {
		double x = random();
		double y = random();
		nodeInfo[i].id = i;
		nodeInfo[i].x = x;
		nodeInfo[i].y = y;
		nodeInfo[i].z = 0;

		myList.push_back(Node(i, x, y, 0));
	}
}
void createCircleRGG() {
	srand(time(NULL));
	for (int i = 0; i < Q_NODES; i++) {
		double x = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 2));
		double y = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 2));
		if ( ( pow((x-1),2) + pow((y-1),2) ) > 1) {
			i--;
		}
		else {
			nodeInfo[i].id = i;
			nodeInfo[i].x = x;
			nodeInfo[i].y = y;
			nodeInfo[i].z = 0;
			myList.push_back(Node(i, x, y, 0));
		}
	}
}

void createDegreeBucket(int buckets) {
	//Initialize array of lists

	bucketDegrees = new list<unsigned int>[buckets];

	for (int i = 0; i < buckets; i++) {
		for (int j = 0; j < Q_NODES; j++) {
			if (degrees[j] == i) {
				bucketDegrees[i].push_back(j);
			}
		}
	}
}
void displayDegreeBucket(int buckets) {
	for (int i = 0; i < buckets; i++) {
		cout << i << ": ";
		for (list<unsigned int>::iterator it = bucketDegrees[i].begin(); it != bucketDegrees[i].end(); it++) {
			cout << (*it) << ", ";
		}
		cout << endl;
	}
}
int maxDegree() {
	//minimumDegree
	int max = 0;
	for (int i = 0; i < Q_NODES; i++) {
		if (degrees[i] > max) {
			max = degrees[i];
			maxDegreeNode = i;
		}
		if (degrees[i] < minimumDegree) {
			minimumDegree = degrees[i];
			minDegreeNode = i;
		}
	}
	return max;
}

int findNonEmptyBucket(int buckets) {
	//Returns -1 if all buckets are empty
	for (int i = 0; i < buckets; i++) {
		if (!bucketDegrees[i].empty()) {
			return i;
		}
	}
	return -1;
}
void removeEdge(int adjacentNode, int smallestNode) {
	for (list<Sensors>::iterator it = edges[adjacentNode].begin(); it != edges[adjacentNode].end();) {
		if ((*it).id == smallestNode) {
			it = edges[adjacentNode].erase(it);
		}
		else {
			it++;
		}
	}
	//edges[(int)a.getInfo()].push_back(b);
	//edges[adjacentNode].remove(smallestNode);
}
void smallestLastOrdering(int buckets) {
	ofstream myfile;
	myfile.open("deletion.txt");

	for (int it = 0; it < Q_NODES; it++) {
		int currentList = findNonEmptyBucket(buckets);
		//Perform if not all buckets are empty:
		if (!(currentList == -1)) {
			//Find node with smallest degree in bucket sorter
			int smallestNode = bucketDegrees[currentList].front();
			
				//Add it to end of array
			smallestLast[Q_NODES - it - 1] = smallestNode;
			//Remove them from bucket
			bucketDegrees[currentList].pop_front();
			//Update max degree when deleted
			if (degrees[smallestNode] > maximumDegreeWhenDeleted) {
				maximumDegreeWhenDeleted = degrees[smallestNode];
			}
			myfile << smallestNode << " " << degrees[smallestNode] << " " << originalDegrees[smallestNode] << endl;
			
			//Next: Traverse through adjacent nodes and update their degree and position in bucket sorter.
			//Traverse through adjacent nodes
			for (list<Sensors>::iterator it = edges[smallestNode].begin(); it != edges[smallestNode].end(); it++) {
				int adjacentNode = (*it).id;
				int adjacentNodeDegree = degrees[adjacentNode];
				//Update their bucket position
					//Add them to a lower degree in the bucket
				bucketDegrees[adjacentNodeDegree - 1].push_back(adjacentNode);
					//Remove them from current degree bucket
				bucketDegrees[adjacentNodeDegree].remove(adjacentNode);
					//Remove the edges (otherwise it could be found again)
				removeEdge(adjacentNode, smallestNode);

				//Update their degree
				degrees[adjacentNode]--;
			}
		}
	}

	int prev = 0;

	for (int i = 0; i < Q_NODES; i++) {
		int n = smallestLast[i];
		if (prev > degrees[n]) {
			break;
		}
		terminalClique.push_front(n);
		terminalCliqueSize++;
		prev = degrees[n];
	}
	myfile.close();
}
void showSmallestLast() {
	cout << "Smallest last ordering: [Node ID, Act. Deg., Deg. when deleted]" << endl;
	for (int i = 0; i < Q_NODES; i++) {
		int n = smallestLast[i];
		cout << n << " " << originalDegrees[n] << " " << degrees[n] << endl;
	}
}
void coloringAlgorithm() {
	for (int i = 0; i < Q_NODES; i++) {
		//Initialize to 0
		coloring[i] = -1;
	}
	
	//Go through small last ordering
	for (int i = 0; i < Q_NODES; i++) {
		int current = smallestLast[i];

		//Possible color combinations. 1 indicates available
		bool color[Q_COLORS + 1] = {0};
		//Iterate through neighbors
		for (list<Sensors>::iterator it = originalEdges[current].begin(); it != originalEdges[current].end(); it++) {
			//Get an adjacent node
			int adjacentNode = (*it).id;
			if (coloring[adjacentNode] > -1) {
				//Mark color with 1 for not available
				color[coloring[adjacentNode]] = 1;
			}
		}
		int j;
		for (j = 0; j < Q_COLORS; j++) {
			if (color[j] == 0) {
				break;
			}
		}
		coloring[current] = j;
	}
}
void displayColoring() {
	for (int i = 0;i < Q_NODES; i++) {
		cout << i << " " << coloring[i] << endl;
	}
}
int maxColors() {
	int max = 0;
	for (int i = 0; i < Q_NODES; i++) {
		if (coloring[i] > max) {
			max = coloring[i];
		}
	}
	return max+1;
}
void showTerminalClique() {
	cout << "Terminal clique: ";
	for (std::list<int>::const_iterator iterator = terminalClique.begin(), end = terminalClique.end(); iterator != end; ++iterator) {
		cout << *iterator << " ";
	}
	cout << endl;
}
void writeFile(char type) {
	ofstream myfile;
	myfile.open("nodes.txt");
	myfile << type << " 0 0 0 0" << endl;
	myfile << "k " << colorsNeeded << " 0 0 0" << endl;
	int i = 0;

	for (list<Node>::iterator it = myList.begin(); it != myList.end(); it++) {
		myfile << "n " << (*it).getX() << " " << (*it).getY() << " " << (*it).getZ() << " " << coloring[(int)(*it).getInfo()] << endl;
		list<Sensors> edgeList = edges[i];

		for (list<Sensors>::iterator it2 = edgeList.begin(); it2 != edgeList.end(); it2++) {
			myfile << "e " << (*it2).x << " " << (*it2).y << " " << (*it2).z << " 0" << endl;
		}
		i++;
	}
	i = 0;

	while (!terminalClique.empty()) {
		int node = terminalClique.front();
		myfile << "l " << nodeInfo[node].x << " " << nodeInfo[node].y << " " << nodeInfo[node].z << " " << 0 << endl;
		terminalClique.pop_front();
	}
	myfile << "max " << nodeInfo[maxDegreeNode].x << " " << nodeInfo[maxDegreeNode].y << " " << nodeInfo[maxDegreeNode].z << " " << 0 << endl;
	myfile << "min " << nodeInfo[minDegreeNode].x << " " << nodeInfo[minDegreeNode].y << " " << nodeInfo[minDegreeNode].z << " " << 0 << endl;
	myfile.close();
}
void writeGraphData(double radius) {
	ofstream myfile;
	myfile.open("graphData.txt");
	myfile << "avgdeg " << averageDegree() << endl;
	myfile << "maxdeg " << maximumDegree << endl;
	myfile << "mindeg " << minimumDegree << endl;
	myfile << "colors " << colorsNeeded << endl;
	myfile << "radius " << radius << endl;
	myfile << "vertices " << Q_NODES << endl;
	myfile << "terminalCliqueSize " << terminalCliqueSize << endl;
	myfile << "maxdegWD " << maximumDegreeWhenDeleted << endl;
	myfile << "maxColorClassSize " << maxColorClassSize << endl;
	myfile << "edgesBipartite " << edgesLargestBipartite << endl;
	myfile << "edgesBipartite2 " << edgesLargestBipartite2 << endl;
	myfile.close();
}
void createSphereRGG() {
	srand(time(NULL));
	for (int i = 0; i < Q_NODES; i++) {
		double x = 2 * random() - 1;
		double y = 2 * random() - 1;
		double z = 2 * random() - 1;
		double squares = x*x + y*y + z*z;
		if ( squares > 1) {
			i--;
		}
		else {
			double reciprocal = sqrt(squares);
			nodeInfo[i].id = i;
			nodeInfo[i].x = x / reciprocal;
			nodeInfo[i].y = y / reciprocal;
			nodeInfo[i].z = z / reciprocal;
			myList.push_back(Node(i, x/reciprocal, y/ reciprocal, z/ reciprocal));
		}
	}
}
void showNodeInfo() {
	for (int i = 0; i < Q_NODES; i++) {
		cout << nodeInfo[i].id << ": " << nodeInfo[i].x << " " << nodeInfo[i].y << " " << nodeInfo[i].z << endl;
	}
}
int findMaxSet(vector<int> &colorEdges){
	int max = 0;
	int maxColor = 0;
	for (int i = 0; i < colorsNeeded; i++) {
		if (colorEdges[i] > max) {
			max = colorEdges[i];
			maxColor = i;
		}
	}
	colorEdges[maxColor] = 0;
	return maxColor;
}
int calculateConnectedness(int i, int j, vector<list<int>> &colorNodes, vector<list<Sensors>> originalEdges){
	//Calculates how many edges connect between the subgraphs
	int connectedness = 0;
	//Obtain list of nodes we'll check
	list<int> colorSet1 = colorNodes[i];
	list<int> colorSet2 = colorNodes[j];

	//Iterate through each element of list 1
	for (list<int>::iterator it = colorSet1.begin(); it != colorSet1.end(); it++) {
		//Iterate through edges of each node of the list 1
		list<int> auxList = colorSet2;
		for (list<Sensors>::iterator it2 = originalEdges[(*it)].begin(); it2 != originalEdges[(*it)].end(); it2++) {
			//Iterate through each element of list 2 to see if they are connected by edge
			for (list<int>::iterator it3 = auxList.begin(); it3 != auxList.end(); it3++) {
				if ( (*it2).id == (*it3) ) {
					connectedness++;
					it3 = auxList.erase(it3);
					break;
				}
			}
		}
	}
	return connectedness;
}
void writeBipartite(list<int> setA, list<int> setB, vector<list<Sensors>> edgeList, string version) {
	ofstream myfile;
	myfile.open("bipartite" + version + ".txt");

	myfile << type << " 0 0 0 0" << endl;
	myfile << "k " << colorsNeeded << " 0 0 0" << endl;
	for (list<int>::iterator it = setA.begin(); it != setA.end(); it++) {
		myfile << "n " << nodeInfo[(*it)].x << " " << nodeInfo[(*it)].y << " " << nodeInfo[(*it)].z << " " << coloring[nodeInfo[(*it)].id] << endl;
		for (list<Sensors>::iterator it2 = edgeList[(*it)].begin(); it2 != edgeList[(*it)].end(); it2++) {
			for (list<int>::iterator it3 = setB.begin(); it3 != setB.end(); it3++) {
				if ((*it2).id == (*it3)) {
					myfile << "e " << (*it2).x << " " << (*it2).y << " " << (*it2).z << " 0" << endl;
					break;
				}
			}
		}
	}
	for (list<int>::iterator it = setB.begin(); it != setB.end(); it++) {
		myfile << "n " << nodeInfo[(*it)].x << " " << nodeInfo[(*it)].y << " " << nodeInfo[(*it)].z << " " << coloring[nodeInfo[(*it)].id] << endl;
	}
	myfile.close();
}
void findBipartite(vector<list<int>> &colorNodes, vector<int> colorEdges, int &i1, int &j1, int &i2, int &j2) {
	int setsQ = 4;
	vector<int> largestColors(setsQ);
	//Find sets with maximum edges
	cout << "Largest color sets" << endl;
	if (colorsNeeded >= 4) {
		for (int i = 0; i < 4; i++) {
			int color = findMaxSet(colorEdges);
			cout << i << " is color set #" << color << endl;
			largestColors[i] = color;
		}
	}	
	else {
		setsQ = colorsNeeded;
		for (int i = 0; i < colorsNeeded; i++) {
			int color = findMaxSet(colorEdges);
			cout << i << " is color set #" << color << endl;
			largestColors[i] = color;
		}
	}

	//Check all combinations
	int maxi = 0;
	int maxj = 0;
	int maxConnect = 0;

	int maxi2 = 0;
	int maxj2 = 0;
	int maxConnect2 = 0;
	for (int i = 0; i < setsQ; i++) {
		for (int j = i; j < setsQ; j++) {
			if (i != j) {
				int quantity = calculateConnectedness(i, j, colorNodes, originalEdges);
				if (quantity > maxConnect2) {
					maxi2 = i;
					maxj2 = j;
					maxConnect2 = quantity;
					if (quantity > maxConnect) {
						maxi2 = maxi;
						maxj2 = maxj;
						maxConnect2 = maxConnect;
						maxi = i;
						maxj = j;
						maxConnect = quantity;
					}
				}
				cout << endl << "Sets (" << i << ", " << j << ") have " << quantity << endl;
			}
		}
	}
	edgesLargestBipartite = maxConnect;
	edgesLargestBipartite2 = maxConnect2;
	i1 = maxi;
	j1 = maxj;
	i2 = maxi2;
	j2 = maxj2;
}
void calculateBiData(vector<int> &colorInfo, vector<list<int>> &colorSets, vector<int> &colorEdgeCount) {
	//Initialize
	for (int i = 0; i < colorsNeeded; i++) {
		colorInfo[i] = 0;
	}
	//Count how many for each node
	for (int i = 0; i < Q_NODES; i++){
		colorInfo[coloring[i]]++;
		colorSets[coloring[i]].push_back(i);
		for (list<Sensors>::iterator it2 = originalEdges[i].begin(); it2 != originalEdges[i].end(); it2++) {
			colorEdgeCount[coloring[i]]++;
		}
	}
	for (int i = 0; i < colorsNeeded; i++) {
		if (colorInfo[i] > maxColorClassSize) {
			maxColorClassSize = colorInfo[i];
		}
	}
}
void displayBiData(vector<int> &colorInfo, vector<list<int>> &colorSets, vector<int> &colorEdgeCount) {
	for (int i = 0; i < colorsNeeded; i++) {
		cout << "Color: " << i << " -> There are " << colorInfo[i] << endl;
		cout << "# of edges = " << colorEdgeCount[i] << endl;
		for (list<int>::iterator it2 = colorSets[i].begin(); it2 != colorSets[i].end(); it2++) {
			cout << (*it2) << " ";
		}
		cout << endl << endl;
	}
}
void showBipartiteEdges(vector<int> &colorEdgeCount, int i, int j) {
	cout << "Largest sets: " << i << ", " << j << " have #edges = " << edgesLargestBipartite << endl;
	cout << "List of edges per color set:\n";
	for (int i = 0; i < colorsNeeded; i++) {
		cout << i << " has " << colorEdgeCount[i] << endl;
	}
}
double calculateCoverage(list<int> setA, list<int> setB, vector<list<Sensors>> edgeList) {
	//Create aux array. If node has been visisted, do not add again as another reached node.
	bool *nodeAux = new bool[Q_NODES]();
	unsigned int reachedNodes = 0;

	//Iterate through 1st set of bipartite
	for (list<int>::const_iterator it = setA.begin(), end = setA.end(); it != end; ++it) {
		int currentNode = (*it);
		if (nodeAux[currentNode] == 0) {
			//Count bipartite nodes as reached
			nodeAux[currentNode] = 1;
			reachedNodes++;
		}
		//Iterate through neighbors of nodes
		for (list<Sensors>::iterator it2 = edgeList[currentNode].begin(); it2 != edgeList[currentNode].end(); it2++) {
			//Get an adjacent node
			int adjacentNode = (*it2).id;
			if (nodeAux[adjacentNode] == 0) {
				//Count node as reached
				nodeAux[adjacentNode] = 1;
				reachedNodes++;
			}
		}
	}
	
	//Iterate through 2nd set of bipartite
	for (list<int>::const_iterator it = setB.begin(), end = setB.end(); it != end; ++it) {
		int currentNode = (*it);
		if (nodeAux[currentNode] == 0) {
			//Count bipartite nodes as reached
			nodeAux[currentNode] = 1;
			reachedNodes++;
		}
		//Iterate through neighbors of nodes
		for (list<Sensors>::iterator it2 = edgeList[currentNode].begin(); it2 != edgeList[currentNode].end(); it2++) {
			//Get an adjacent node
			int adjacentNode = (*it2).id;
			if (nodeAux[adjacentNode] == 0) {
				//Count node as reached
				nodeAux[adjacentNode] = 1;
				reachedNodes++;
			}
		}
	}
	cout << endl;
	//Delete memory and return node coverage
	delete[] nodeAux;
	return 1.0*reachedNodes/Q_NODES;
}
int main(int argc, const char * argv[]){	
	radius = 0.9;
	int degree = 120;
	cout << "Enter graph type (u = Unit square, c = Unit disk, s = Unit sphere)" << endl;
	cin >> type;
	cout << "Enter wanted degree:" << endl;
	cin >> degree;

	//Degree approximation
	double area;
	switch (type) {
	case 's': //Sphere area
		area = 4 * M_PI;
		break;
	case 'c': //Unit circle area
		area = M_PI;
		break;
	case 'u': //Unit square area
		area = 1;
		break;
	}
	
	radius = sqrt( (degree*area) / (Q_NODES*M_PI) );

	switch (type) {
		case 'u':
			createRGG();
			cout << "Nodes created." << endl;
			connectNodes2D(radius);
			cout << "Edge list created." << endl;
			break;
		case 'c':
			createCircleRGG();
			cout << "Nodes created." << endl;
			connectNodes2D(radius);
			cout << "Edge list created." << endl;
			break;
		case 's':
			//Sphere case
			createSphereRGG();
			cout << "Nodes created." << endl;
			connectNodes3D();
			cout << "Edge list created." << endl;
			break;
		default:
			break;
	}
	
	maximumDegree = maxDegree();
	//displayNodes(myList);
	cout << endl;
	//displayAdjacenecyList();
	originalDegrees = degrees;
	
	//Perform bucket sort
	
	int buckets = maximumDegree +1;
	
	createDegreeBucket(buckets);
	cout << "Degree bucket created." << endl;
	//displayDegreeBucket(buckets);
	
	originalEdges = edges;
	smallestLast = new unsigned int[Q_NODES];
	//Perform smallest last ordering
	smallestLastOrdering(buckets);
	cout << "Smallest last ordering executed successully." << endl;
	delete[] bucketDegrees;
	//showSmallestLast();

	//Coloring
	coloringAlgorithm();
	colorsNeeded = maxColors();
	cout << "Coloring algorithm executed successully." << endl;
	//displayColoring();

	writeDegrees();
	

	//Find bipartite subgraph
		//Find how many and which nodes, in each color
	vector<int> colorInfo(colorsNeeded);
	vector<list<int>> colorSets(colorsNeeded);
	vector<int> colorEdgeCount(colorsNeeded);
	calculateBiData(colorInfo, colorSets, colorEdgeCount);
	writeColorSetSize(colorInfo);
	writeFile(type);

	//displayBiData(colorInfo, colorSets, colorEdgeCount);
		//Find max independent set
	int i1, j1, i2, j2;
	findBipartite(colorSets, colorEdgeCount, i1, j1, i2, j2);
	
	/*
	i1 = 1;
	j1 = 2;
	i2 = 2;
	j2 = 3;
	*/

	cout << "Bipartite backbone selected successully." << endl;

	writeGraphData(radius);
	cout << "Graph data wrote successfully" << endl;
	
	writeBipartite(colorSets[i1], colorSets[j1], originalEdges, "1");
	cout << "Wrote 1st backbone" << endl;
	
	writeBipartite(colorSets[i2], colorSets[j2], originalEdges, "2");
	cout << "Wrote 2nd backbone" << endl;

	backboneCoverage = calculateCoverage(colorSets[i1], colorSets[j1], originalEdges);
	backboneCoverage2 = calculateCoverage(colorSets[i2], colorSets[j2], originalEdges);
	
	//showBipartiteEdges(colorEdgeCount, i1, j1);

	//displayColoring();
	//displayAdjacenecyList2();

	//Find terminal clique
	//showTerminalClique();

	cout << "\nSuccess!\nAvg. deg.: " << averageDegree() << "\nMax deg.: " << maximumDegree << "\nColors needed: " << colorsNeeded << endl;
	cout << "Coverage bipartite 1: " << 1.0*backboneCoverage << endl;
	cout << "Coverage bipartite 2: " << 1.0*backboneCoverage2 << endl;
	
	//Release memory
	delete[] smallestLast;
	delete[] coloring;
	cout << "END\n";
	return 0;
}