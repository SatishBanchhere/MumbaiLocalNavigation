#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <limits>
#include <string>
#include <stack>
#include <iomanip>   // for std::setprecision
#include <algorithm> // for std::reverse
#include <fstream>
#include <sstream>

using namespace std;

// Structure to represent an edge
struct Edge
{
    string dest;
    double weight; // Changed from int to double for decimal distances
};

// Graph class using adjacency list representation
class Graph
{
private:
    unordered_map<string, vector<Edge>> adj;

public:
    // Function to add an edge to the graph
    void addEdge(const string &src, const string &dest, double weight)
    {
        adj[src].push_back({dest, weight});
        adj[dest].push_back({src, weight}); // Assuming bidirectional routes
    }

    // Function to find shortest path using Dijkstra's algorithm
    void dijkstra(const string &src, const string &dest)
    {
        // Min-heap priority queue to store {distance, vertex}
        priority_queue<pair<double, string>, vector<pair<double, string>>, greater<pair<double, string>>> pq;

        // Map to store distances from source
        unordered_map<string, double> dist;

        // Map to store predecessors in shortest path
        unordered_map<string, string> prev;

        // Start from the source vertex
        dist[src] = 0.0;
        pq.push({0.0, src});

        while (!pq.empty())
        {
            string u = pq.top().second;
            double u_dist = pq.top().first;
            pq.pop();

            // Early exit if we reach the destination
            if (u == dest)
                break;

            // Iterate through all adjacent vertices of u
            for (auto &edge : adj[u])
            {
                string v = edge.dest;
                double weight = edge.weight;

                // Calculate new distance to neighbor vertex
                double new_dist = u_dist + weight;

                // If shorter path to v found through u, update it
                if (!dist.count(v) || new_dist < dist[v])
                {
                    dist[v] = new_dist;
                    prev[v] = u;
                    pq.push({new_dist, v});
                }
            }
        }

        // If there is no path to the destination
        if (dist[dest] == numeric_limits<double>::max())
        {
            cout << "No path found from " << src << " to " << dest << endl;
            return;
        }

        // Reconstruct the shortest path from source to destination
        vector<string> path;
        string current = dest;
        while (current != src)
        {
            path.push_back(current);
            current = prev[current];
        }
        path.push_back(src);

        cout << "Route:" << endl
             << endl;

        reverse(path.begin(), path.end());
        for (int i = 0; i < path.size(); i++)
        {
            cout << path[i] << endl;
            if (path[i] == "Dadar" && i != 0 && i != path.size())
            {
                string lastStaion = path[i - 1];
                string nextStaion = path[i + 1];
                if (lastStaion == "Matunga" && nextStaion == "Prabhadevi")
                {
                    cout << endl
                         << "Change train from central line to western line" << endl
                         << endl;
                }
                if (lastStaion == "Prabhadevi" && nextStaion == "Matunga")
                {
                    cout << endl
                         << "Change train from western line to central line" << endl
                         << endl;
                }
                if (lastStaion == "Matunga Road" && nextStaion == "Parel")
                {
                    cout << endl
                         << "Change train from western line to central line" << endl
                         << endl;
                }
                if (lastStaion == "Parel" && nextStaion == "Matunga Road")
                {
                    cout << endl
                         << "Change train from central line to western line" << endl
                         << endl;
                }
            }

            if (path[i] == "Kurla" && i != 0 && i != path.size())
            {
                string lastStaion = path[i - 1];
                string nextStaion = path[i + 1];
                if (lastStaion == "Vidya Vihar" && nextStaion == "Chunabhatti")
                {
                    cout << endl
                         << "Change train from central line to harbour line" << endl
                         << endl;
                }
                if (lastStaion == "Chunabhatti" && nextStaion == "Vidya Vihar")
                {
                    cout << endl
                         << "Change train from harbour line to central line" << endl
                         << endl;
                }
                if (lastStaion == "Tilaknagar" && nextStaion == "Sion")
                {
                    cout << endl
                         << "Change train from harbour line to central line" << endl
                         << endl;
                }
                if (lastStaion == "Sion" && nextStaion == "Tilaknagar")
                {
                    cout << endl
                         << "Change train from central line to harbour line" << endl
                         << endl;
                }
            }
            if (path[i] == "Thane" && i != 0 && i != path.size())
            {
                string lastStaion = path[i - 1];
                string nextStaion = path[i + 1];
                if (lastStaion == "Airoli")
                {
                    cout << endl
                         << "Change train from trans-harbour line to central line" << endl
                         << endl;
                }
                if (nextStaion == "Airoli")
                {
                    cout << endl
                         << "Change train from central line to trans-harbour line" << endl
                         << endl;
                }
            }
            if (path[i] == "Vashi" && i != 0 && i != path.size())
            {
                string lastStaion = path[i - 1];
                string nextStaion = path[i + 1];
                if (lastStaion == "Mankhurd" && i != path.size() - 1 && path[i + 2] == "Turbhe")
                {
                    cout << endl
                         << "Change train from harbour line to trans-harbour line" << endl
                         << endl;
                }
                if (lastStaion == "Sanpada" && i != 1 && path[i - 2] == "Turbhe")
                {
                    cout << endl
                         << "Change train from trans-harbour line to harbour line" << endl
                         << endl;
                }
            }
        }

        cout << endl
             << "Shortest distance from Station " << src << " to Station " << dest << ": " << dist[dest] << " km\n";
    }
};

void readFile(string &filename, unordered_map<string, int> &stations, int &stationNo, Graph &g, unordered_map<int, string> &numbers)
{
    ifstream infile(filename);
    if (!infile.is_open())
    {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    string line;
    while (getline(infile, line))
    {
        stringstream ss(line);
        string from_station, to_station, is, km;
        double distance;

        if (!(getline(ss, from_station, '"') && getline(ss, from_station, '"')))
        {
            cerr << "Error reading 'from' station from line: " << line << endl;
            continue;
        }

        if (!(getline(ss, to_station, '"') && getline(ss, to_station, '"')))
        {
            cerr << "Error reading 'to' station from line: " << line << endl;
            continue;
        }

        if (!(ss >> is))
        {
            cerr << "Error reading 'is' from line: " << line << endl;
            continue;
        }

        if (!(ss >> distance))
        {
            cerr << "Error reading distance from line: " << line << endl;
            continue;
        }

        if (!(ss >> km))
        {
            cerr << "Error reading 'km' from line: " << line << endl;
            continue;
        }
        cout << stationNo  << ". " << from_station << endl;
        if (distance != 0)
        {
            g.addEdge(from_station, to_station, distance);
        }

        stations[from_station] = stationNo;
        numbers[stationNo] = from_station;
        stationNo++;
    }
}

bool isNum(string num)
{
    for (int i = 0; i < num.size(); i++)
    {
        if (!(num[i] >= '0' && num[i] <= '9'))
        {
            return false;
        }
    }
    return true;
}

int main()
{
    Graph g;
    unordered_map<string, int> stations;
    unordered_map<int, string> numbers;
    int stationNo = 1;
    vector<string> lines = {"western.txt", "central.txt", "harbour.txt", "transHarbour.txt"};

    for (int i = 0; i < lines.size(); i++)
    {
        readFile(lines[i], stations, stationNo, g, numbers);
    }

    cout << endl;
    string source, destination;
    cout << "Enter source station name: ";
    getline(cin, source);
    if (isNum(source))
    {
        int no = stoi(source);
        cout << no << endl;
        source = numbers[no];
    }
    while (!stations[source])
    {
        cout << "Please enter the correct station name or number" << endl;
        getline(cin, source);
        if (isNum(source))
        {
            int no = stoi(source);
            source = numbers[no];
        }
    }

    cout << endl;
    cout << "Enter destination station name: ";
    getline(cin, destination);
    if (isNum(destination))
    {
        int no = stoi(destination);
        cout << no << endl;
        destination = numbers[no];
    }
    while (!stations[destination])
    {
        cout << "Please enter the correct station name or number" << endl;
        getline(cin, destination);
        if (isNum(destination))
        {
            int no = stoi(destination);
            cout << no << endl;
            destination = numbers[no];
        }
    }

    cout << endl;
    // Use Dijkstra's algorithm to find shortest path
    g.dijkstra(source, destination);

    return 0;
}