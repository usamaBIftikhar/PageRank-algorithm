#include <iostream>  // std::fixed
#include <iterator>
#include <vector>
#include <map>
#include <unordered_map>
#include <iomanip>  // std::setprecision

using namespace std;


// Adjacency List Graph
class AdjacencyList {
private:
    /* Graph vertex (node)
     *
     * Example:
     *
     * (to) A: (from) B -> (1/from out_degree) 1/d_B
     */
    // Attributes
    unordered_map<string, unsigned int> outDegreeGraph;  // Store the out_degree connection (from -> to)
    unordered_map<string, vector<string> > inDegreeGraph;  // Store the in_degree connection (to -> from (out_degree)

    map<string, float> pageRank;  // Store the website with their rank  (initial rank is -> website : (1 / |V|)

    // Return number of unique vertices |V| in the graph
    int getNumberOfVertices() { return (int) inDegreeGraph.size(); }

    // Initialize page rank to 1 / |V|
    void initializePageRank() {
        // Initialize page rank to 1 / |V|
        for (auto &vertex : inDegreeGraph) {
            pageRank[vertex.first] = 1.0f / (float) getNumberOfVertices();
        }
    }

    // Print page ranks
    void printPageRanks() {
        // Iterator to go through each vertex
        map<string, float>::iterator pageRankIt;

        // Printing ranks
        for(pageRankIt = pageRank.begin(); pageRankIt != pageRank.end(); ++pageRankIt) {
            cout << std::setprecision(2) << std::fixed << pageRankIt->first << " " << pageRankIt->second;
            cout<<"\n";
        }
    }

public:
    // Constructor
    AdjacencyList() = default;

    // Connect two vertices
    void insertEdge(string &from, string &to) {
        // Push value into the graph
        outDegreeGraph[from] += 1;  // From -> to (out_degree of from)
        inDegreeGraph[to].push_back(from);  // To -> from (in_degree of from)

        // Add (from) key with empty value into the graph if it is not there
        if (outDegreeGraph.find(to) == outDegreeGraph.end()) outDegreeGraph[to] = 0;

        // Add (to) key with empty value into the graph if it is not there
        if (inDegreeGraph.find(from) == inDegreeGraph.end()) inDegreeGraph[from] = {};
    }

    // Simplified PageRank Algorithm
    void PageRank(int power_iterations) {
        // Initialize page rank to 1 / |V|
        initializePageRank();

        // Temporary rank to hold old ranks until the next iteration
        map<string, float> newPageRank;  // Page rank graph (website with their corresponding rank value

        // Find the page rank for each webpage
        for (int i = 1; i < power_iterations; i++) {
            // Temporary rank to hold old ranks until the next iteration
            newPageRank = pageRank;

            // Go through each webpage (vertex)
            for (auto &webpage : inDegreeGraph) {
                // Sum of result
                float sum = 0.0f;

                // Calculate the rank for each page
                for (auto &link : webpage.second) {
                    // Sum = (1 / out_degreeCount of j) * page_rank of i
                    sum += (1.0f / (float) outDegreeGraph.find(link)->second) * pageRank[link];  // Add the result
                }

                // Update the page rank
                newPageRank[webpage.first] = sum;
            }
            // Update page rank
            pageRank = newPageRank;
        }

        // Print page ranks
        printPageRanks();
    }
};


int main() {
    // Graph
    AdjacencyList graph;

    // User inputs
    int no_of_lines = 0, power_iterations = 0;
    string from, to;

    // Get user inputs
    cin >> no_of_lines;
    cin >> power_iterations;

    // Insert the edges into the graph
    for (int i = 0; i < no_of_lines; i++) {
        // Get vertices
        cin >> from;
        cin >> to;

        // Insert vertices into graph
        graph.insertEdge(from, to);
    }

    // Get page ranks
    graph.PageRank(power_iterations);

    return 0;
}
