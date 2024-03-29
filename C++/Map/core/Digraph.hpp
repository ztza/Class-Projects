// Digraph.hpp
//
// ICS 46 Spring 2015
// Project #4: Rock and Roll Stops the Traffic
//
// This header file declares a class template called Digraph, which is
// intended to implement a generic directed graph.  The implementation
// uses the adjacency lists technique, so each vertex stores a linked
// list of its outgoing edges.
//
// Along with the Digraph class template is a class DigraphException
// and a couple of utility structs that aren't generally useful outside
// of this header file.
//
// In general, directed graphs are all the same, except in the sense
// that they store different kinds of information about each vertex and
// about each edge; these two types are the type parameters to the
// Digraph class template.

#ifndef DIGRAPH_HPP
#define DIGRAPH_HPP

#include <functional>
#include <list>
#include <map>
#include <utility>
#include <vector>
#include <set>
#include <queue>



// DigraphExceptions are thrown from some of the member functions in the
// Digraph class template, so that exception is declared here, so it
// will be available to any code that includes this header file.

class DigraphException
{
public:
    DigraphException(const std::string& reason): reason_{reason} { }

    std::string reason() const { return reason_; }

private:
    std::string reason_;
};



// A DigraphEdge lists a "from vertex" (the number of the vertex from which
// the edge points), a "to vertex" (the number of the vertex to which the
// edge points), and an EdgeInfo object.  Because different kinds of Digraphs
// store different kinds of edge information, DigraphEdge is a template
// struct.

template <typename EdgeInfo>
struct DigraphEdge
{
    int fromVertex;
    int toVertex;
    EdgeInfo einfo;
};



// A DigraphVertex includes two things: a VertexInfo object and a list of
// its outgoing edges.  Because different kinds of Digraphs store different
// kinds of vertex and edge information, DigraphVertex is a template struct.

template <typename VertexInfo, typename EdgeInfo>
struct DigraphVertex
{
    VertexInfo vinfo;
    std::list<DigraphEdge<EdgeInfo>> edges;
};



// Digraph is a class template that represents a directed graph implemented
// using adjacency lists.  It takes two type parameters:
//
// * VertexInfo, which specifies the kind of object stored for each vertex
// * EdgeInfo, which specifies the kind of object stored for each edge
//
// You'll need to implement the member functions declared here; each has a
// comment detailing how it is intended to work.
//
// Each vertex in a Digraph is identified uniquely by a "vertex number".
// Vertex numbers are not necessarily sequential and they are not necessarily
// zero- or one-based.

template <typename VertexInfo, typename EdgeInfo>
class Digraph
{


public:
    // The default constructor initializes a new, empty Digraph so that
    // contains no vertices and no edges.
    Digraph();

    // The copy constructor initializes a new Digraph to be a deep copy
    // of another one (i.e., any change to the copy will not affect the
    // original).
    Digraph(const Digraph& d);

    // The destructor deallocates any memory associated with the Digraph.
    ~Digraph();

    // The assignment operator assigns the contents of the given Digraph
    // into "this" Digraph, with "this" Digraph becoming a separate, deep
    // copy of the contents of the given one (i.e., any change made to
    // "this" Digraph afterward will not affect the other).
    Digraph& operator=(const Digraph& d);

    // vertices() returns a std::vector containing the vertex numbers of
    // every vertex in this Digraph.
    std::vector<int> vertices() const;

    // edges() returns a std::vector of std::pairs, in which each pair
    // contains the "from" and "to" vertex numbers of an edge in this
    // Digraph.  All edges are included in the std::vector.
    std::vector<std::pair<int, int>> edges() const;

    // This overload of edges() returns a std::vector of std::pairs, in
    // which each pair contains the "from" and "to" vertex numbers of an
    // edge in this Digraph.  Only edges outgoing from the given vertex
    // number are included in the std::vector.  If the given vertex does
    // not exist, a DigraphException is thrown instead.
    std::vector<std::pair<int, int>> edges(int vertex) const;

    // vertexInfo() returns the VertexInfo object belonging to the vertex
    // with the given vertex number.  If that vertex does not exist, a
    // DigraphException is thrown instead.
    VertexInfo vertexInfo(int vertex) const;

    // edgeInfo() returns the EdgeInfo object belonging to the edge
    // with the given "from" and "to" vertex numbers.  If either of those
    // vertices does not exist *or* if the edge does not exist, a
    // DigraphException is thrown instead.
    EdgeInfo edgeInfo(int fromVertex, int toVertex) const;

    // addVertex() adds a vertex to the Digraph with the given vertex
    // number and VertexInfo object.  If there is already a vertex in
    // the graph with the given vertex number, a DigraphException is
    // thrown instead.
    void addVertex(int vertex, const VertexInfo& vinfo);

    // addEdge() adds an edge to the Digraph pointing from the given
    // "from" vertex number to the given "to" vertex number, and
    // associates with the given EdgeInfo object with it.  If one
    // of the vertices does not exist *or* if the same edge is already
    // present in the graph, a DigraphException is thrown instead.
    void addEdge(int fromVertex, int toVertex, const EdgeInfo& einfo);

    // removeVertex() removes the vertex (and all of its incoming
    // and outgoing edges) with the given vertex number from the
    // Digraph.  If the vertex does not exist already, a DigraphException
    // is thrown instead.
    void removeVertex(int vertex);

    // removeEdge() removes the edge pointing from the given "from"
    // vertex number to the given "to" vertex number from the Digraph.
    // If either of these vertices does not exist *or* if the edge
    // is not already present in the graph, a DigraphException is
    // thrown instead.
    void removeEdge(int fromVertex, int toVertex);

    // vertexCount() returns the number of vertices in the graph.
    int vertexCount() const;

    // edgeCount() returns the total number of edges in the graph,
    // counting edges outgoing from all vertices.
    int edgeCount() const;

    // This overload of edgeCount() returns the number of edges in
    // the graph that are outgoing from the given vertex number.
    // If the given vertex does not exist, a DigraphException is
    // thrown instead.
    int edgeCount(int vertex) const;

    // isStronglyConnected() returns true if the Digraph is strongly
    // connected (i.e., every vertex is reachable from every other),
    // false otherwise.
    bool isStronglyConnected() const;

    // findShortestPaths() takes a start vertex number and a function
    // that takes an EdgeInfo object and determines an edge weight.
    // It uses Dijkstra's Shortest Path Algorithm to determine the
    // shortest paths from the start vertex to every other vertex
    // in the graph.  The result is returned as a std::map<int, int>
    // where the keys are vertex numbers and the value associated
    // with each key k is the precedessor of that vertex chosen by
    // the algorithm.  For any vertex without a precedessor (e.g.,
    // a vertex that was never reached, or the start vertex itself),
    // the value is simply a copy of the key.
    std::map<int, int> findShortestPaths(
        int startVertex,
        std::function<double(const EdgeInfo&)> edgeWeightFunc) const;


    void vertexExists(int vertex) const;
    void visitVertex(int vertex, std::set<int> &visited) const;

private:
    // Add whatever member variables you think you need here.  One
    // possibility is a std::map where the keys are vertex numbers
    // and the values are DigraphVertex<VertexInfo, EdgeInfo> objects.


    // You can also feel free to add any additional member functions
    // you'd like (public or private), so long as you don't remove or
    // change the signatures of the ones that already exist.
    std::map<int, DigraphVertex<VertexInfo, EdgeInfo>> database;
    std::vector<int> _vertices;
};


template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>::Digraph()
{

}

template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>::Digraph(const Digraph& d)
{
    this->database = d.database;
    this->_vertices = d._vertices;
}

template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>::~Digraph()
{

}

template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>& Digraph<VertexInfo, EdgeInfo>::operator=(const Digraph& d)
{
    this->database = d.database;
    this->_vertices = d._vertices;
    return *this;
}

template <typename VertexInfo, typename EdgeInfo>
std::vector<int> Digraph<VertexInfo, EdgeInfo>::vertices() const
{
    return this->_vertices;
}

template <typename VertexInfo, typename EdgeInfo>
std::vector<std::pair<int, int>> Digraph<VertexInfo, EdgeInfo>::edges() const
{
    std::vector<std::pair<int, int>> result;

    std::vector<int> _vertices = this->_vertices;

    for (std::vector<int>::iterator i = _vertices.begin(); i != _vertices.end(); i++)
    {
        DigraphVertex<VertexInfo, EdgeInfo> dVertex = (database.at(*i));
        std::list<DigraphEdge<EdgeInfo>> dEdge = (dVertex.edges); 
        typename std::list<DigraphEdge<EdgeInfo>>::iterator it = dEdge.begin();

        while(it != dEdge.end())
        {
            result.push_back(std::pair<int, int>(it->fromVertex, it->toVertex));
            it++;
        }
    }

    return result;
}

template <typename VertexInfo, typename EdgeInfo>
std::vector<std::pair<int, int>> Digraph<VertexInfo, EdgeInfo>::edges(int vertex) const
{
    std::vector<std::pair<int, int>> result;
        
    vertexExists(vertex);

    std::vector<int> _vertices = this->_vertices;

    for (std::vector<int>::iterator i = _vertices.begin(); i != _vertices.end(); i++)
    {
        DigraphVertex<VertexInfo, EdgeInfo> dVertex = (database.at(*i));
        std::list<DigraphEdge<EdgeInfo>> dEdge = (dVertex.edges); 
        typename std::list<DigraphEdge<EdgeInfo>>::iterator it = dEdge.begin();

        while(it != dEdge.end())
        {
            if(it->fromVertex == vertex)
                result.push_back(std::pair<int, int>(it->fromVertex, it->toVertex));
            it++;
        }
    }

    return result;
}

template <typename VertexInfo, typename EdgeInfo>
VertexInfo Digraph<VertexInfo, EdgeInfo>::vertexInfo(int vertex) const
{

    try{
        vertexExists(vertex);
        return database.at(vertex).vinfo;
    }catch (...)
    {
        throw DigraphException("Digraph::vertexInfo(int vertex). Starting vertex does not exist.");
    }
        
}

template <typename VertexInfo, typename EdgeInfo>
EdgeInfo Digraph<VertexInfo, EdgeInfo>::edgeInfo(int fromVertex, int toVertex) const
{

    vertexExists(fromVertex);
    vertexExists(toVertex);

    DigraphVertex<VertexInfo, EdgeInfo> dVertex = (database.at(fromVertex));
    std::list<DigraphEdge<EdgeInfo>> dEdge = (dVertex.edges);

   typename std::list<DigraphEdge<EdgeInfo>>::iterator it = dEdge.begin();

    while(it != dEdge.end())
    {
        if (it->fromVertex == fromVertex && it->toVertex == toVertex)
        {
            return it->einfo;
        }
        it++;
    }
    
    throw DigraphException("Diagraph::edgeInfo. Edge does not exists.");
}

template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo, EdgeInfo>::addVertex(int vertex, const VertexInfo& vinfo)
{
    DigraphVertex<VertexInfo, EdgeInfo> dVertex{vinfo};

try{
    vertexExists(vertex);
    throw  DigraphException("Diagraph::addVertex. Vertex already exist.");
    }catch(...)
    {
        //Vertex does not exist
        database[vertex] = dVertex;
        _vertices.push_back(vertex);
    }
}

template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo, EdgeInfo>::addEdge(int fromVertex, int toVertex, const EdgeInfo& einfo)
{
    //First check to make sure that the starting point and destination exists.
    vertexExists(fromVertex);
    vertexExists(toVertex);

    DigraphEdge<EdgeInfo> temp = DigraphEdge<EdgeInfo>{fromVertex, toVertex, einfo};

    DigraphVertex<VertexInfo, EdgeInfo>* dVertex = &(database.at(fromVertex));
    std::list<DigraphEdge<EdgeInfo>>* dEdge = &(dVertex->edges);

   typename std::list<DigraphEdge<EdgeInfo>>::iterator it = dEdge->begin();

    while(it != dEdge->end())
    {
        if (it->fromVertex == temp.fromVertex && it->toVertex == temp.toVertex)
        {
            throw DigraphException("Diagraph::addEdge. Edge already exists in graph.");
        }
        it++;
    }
        //If no exception is thrown, we can safely add.
    dEdge->push_back(temp);
}

template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo, EdgeInfo>::removeVertex(int vertex)
{
    vertexExists(vertex);
    database.erase(vertex);
    for (std::vector<int>::iterator it = _vertices.begin(); it != _vertices.end(); it++)
    {
        if(*it == vertex)
        {
            _vertices.erase(it);
            break;
        }
    }
    
}

template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo, EdgeInfo>::removeEdge(int fromVertex, int toVertex)
{
    vertexExists(fromVertex);
    vertexExists(toVertex);

    DigraphVertex<VertexInfo, EdgeInfo>* dVertex = &(database.at(fromVertex));
    std::list<DigraphEdge<EdgeInfo>>* dEdge = &(dVertex->edges); 
    typename std::list<DigraphEdge<EdgeInfo>>::iterator it = dEdge->begin();

    while(it != dEdge->end())
    {
        if(it->toVertex == toVertex)
        {    
            dEdge->erase(it);
            return;
        }
        it++;
    }



}

template <typename VertexInfo, typename EdgeInfo>
int Digraph<VertexInfo, EdgeInfo>::vertexCount() const
{
    return _vertices.size();
}

template <typename VertexInfo, typename EdgeInfo>
int Digraph<VertexInfo, EdgeInfo>::edgeCount() const
{
    return edges().size();
}

template <typename VertexInfo, typename EdgeInfo>
int Digraph<VertexInfo, EdgeInfo>::edgeCount(int vertex) const
{
    vertexExists(vertex);
    return edges(vertex).size();
}

template <typename VertexInfo, typename EdgeInfo>
bool Digraph<VertexInfo, EdgeInfo>::isStronglyConnected() const
{
    std::vector<int> _vertices = this->_vertices;
    std::set<int> visited;
    for (std::vector<int>::iterator i = _vertices.begin(); i != _vertices.end(); i++)
    {
        visitVertex(*i, visited);
        if (visited.size() != _vertices.size())
            return false;
        visited.clear();
    }
    return true;
}

template <typename VertexInfo, typename EdgeInfo>
std::map<int, int> Digraph<VertexInfo, EdgeInfo>::findShortestPaths(
    int startVertex,
        std::function<double(const EdgeInfo&)> edgeWeightFunc) const
{
    std::map<int, int> resultmap;

    #define infinity 100000000
    #define none -1
    #define unknown -2
    struct vertex_details
    {
        bool known;
        int precedessor;
        double distance;
        int vertex;
        bool operator<(const vertex_details &right)
        {
            return (distance < right.distance);
        }
        bool operator>(const vertex_details &right)
        {
            return (distance > right.distance);
        }
    };

    class compareDistance
    {
    public:
        bool operator()(vertex_details &x, vertex_details &y)
        {
            if (x.distance > y.distance) return true;
            if (x.distance == y.distance) return true;
            return false;
        }
    };


    vertex_details vertex_map[_vertices.size()];
    std::priority_queue<vertex_details, std::vector<vertex_details>, compareDistance> q;

    int v;
    std::vector<int> _vertices = this->_vertices;
    for (std::vector<int>::iterator i = _vertices.begin(); i != _vertices.end(); i++)
    {
        //Setting default values
        if (*i == startVertex)
        {
            vertex_map[*i] = vertex_details{false, none, 0, *i};
            q.push(vertex_map[*i]);
            resultmap[*i] = none;
        }
        else
        {   
            vertex_map[*i] = vertex_details{false, unknown, infinity, *i};
            q.push(vertex_map[*i]);
        }
    }

    while (!q.empty())
    {
        v = q.top().vertex;
        if(vertex_map[v].known == false)
        {
            vertex_map[v].known = true;
            std::vector<std::pair<int, int>> v_edges = edges(v);

            for ( std::vector<std::pair<int, int>>::iterator i = v_edges.begin(); i != v_edges.end(); i++)
            {  
                int w = std::get<1>(*i);
                double result = vertex_map[v].distance + edgeWeightFunc(edgeInfo(v, w));
                if(vertex_map[w].distance > result)
                {
                    vertex_map[w].distance = result;
                    vertex_map[w].precedessor = v;
                    resultmap[v] = q.top().precedessor;
                    q.push(vertex_map[w]);
                }
            }
        }
        else
        {  
            q.pop();
        }
    }
    return resultmap;
}


template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo, EdgeInfo>::visitVertex(int vertex, std::set<int> &visited) const
{
    visited.insert(vertex);
    DigraphVertex<VertexInfo, EdgeInfo> dVertex = (database.at(vertex));
    std::list<DigraphEdge<EdgeInfo>> dEdge = (dVertex.edges); 
    typename std::list<DigraphEdge<EdgeInfo>>::iterator it = dEdge.begin();

    while(it != dEdge.end())
    {
        if (find(visited.begin(), visited.end(), it->toVertex) == visited.end())
            visitVertex(it->toVertex, visited);
        it++;
    }
}


template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo, EdgeInfo>::vertexExists(int vertex) const
{
   if (find(_vertices.begin(), _vertices.end(), vertex) == _vertices.end())//Items do not exists;
    {
        throw DigraphException("Digraph::vertexExists. Vertex does not exist.");
    }
}
#endif // DIGRAPH_HPP

