#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <string>

// Node class for the adjacency list
class AdjListNode {
private:
    int v;
public:
    AdjListNode(int _v) { v = _v; }
    int getV() { return v; }
};

// Digraph class representing a directed graph using adjacency list representation
class Digraph {
private:
    int V; // No. of vertices
    std::list<AdjListNode>* adj; // Pointer to an array containing the adjacency lists

    // A recursive function used by topologicalSort
    void topologicalSortUtil(int v, bool visited[], std::stack<int>& Stack);

public:
    Digraph(int V);  // Constructor

    // function to add an edge to graph
    void addEdge(int u, int v);

    // prints a Topological Sort of the complete graph
    std::stack<int> topologicalSort();

    // Destructor
    ~Digraph();
};

Digraph::Digraph(int V) {
    this->V = V;
    adj = new std::list<AdjListNode>[V];
}

void Digraph::addEdge(int u, int v) {
    AdjListNode node(v);
    adj[u].push_back(node); // Add v to u’s list.
}

void Digraph::topologicalSortUtil(int v, bool visited[], std::stack<int>& Stack) {
    // Mark the current node as visited
    visited[v] = true;

    // Recur for all the vertices adjacent to this vertex
    for (auto i = adj[v].begin(); i != adj[v].end(); ++i) {
        AdjListNode node = *i;
        if (!visited[node.getV()])
            topologicalSortUtil(node.getV(), visited, Stack);
    }

    // Push current vertex to stack which stores result
    Stack.push(v);
}

std::stack<int> Digraph::topologicalSort() {
    std::stack<int> Stack;

    // Mark all the vertices as not visited
    bool* visited = new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;

    // Call the recursive helper function to store Topological Sort starting from all vertices one by one
    for (int i = 1; i < V; i++)
        if (!visited[i])
            topologicalSortUtil(i, visited, Stack);

    // Print contents of stack
    while (!Stack.empty()) {
        std::cout << Stack.top() << " ";
        Stack.pop();
    }

    delete[] visited;
    return Stack;
}

Digraph::~Digraph() {
    delete[] adj;
}

int main() {
    // Take number of tasks from the user
    int n;
    std::cout << "Enter the number of tasks: ";
    std::cin >> n;
    std::cin.ignore();  // Ignore the leftover newline character

    // Store the tasks in a vector of strings
    std::vector<std::string> tasks;
    std::cout << "Enter the tasks one by one:" << std::endl;
    for (int i = 1; i < n + 1; ++i) {
        std::string task;
        std::getline(std::cin, task);  // Read the whole line including spaces
        tasks.push_back(task);
    }

    Digraph g(n + 1);

    // Ask user to input pairs based on the task index (not starting from 0, but from 1 for user-friendliness)
    std::cout << "\nEnter the task pairs indicating which task should come before another." << std::endl;
    std::cout << "Use task numbers for inserting pairs. The first task previously entered is 1, second is 2, and so on)." << std::endl;
    std::cout << "If the first task entered comes before task 2, Format: 1 2" << std::endl;
    std::cout << "Input -1 -1 to end input of task pairs.\n" << std::endl;

    int u, v;
    while (true) {
        std::cin >> u >> v;
        if (u == -1 && v == -1) {
            break;
        }
        // adjusting user input to match zero-based index array representation
        g.addEdge(u, v);
    }

    std::cout << "\nFollowing is a Topological Sort of the entered tasks:\n";
    // The topological sort will return a stack of indices representing tasks
    std::stack<int> sortedTasks = g.topologicalSort();

    // Print out the task names in topological order
    while (!sortedTasks.empty()) {
        std::cout << tasks[sortedTasks.top() - 1] << std::endl;
        sortedTasks.pop();
    }

    return 0;
}