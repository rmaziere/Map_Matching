#ifndef ROAD_H
#define ROAD_H

#include "pointroad.h"
#include "track.h"

#include <set>
#include <string>
#include <vector>

/**
 * @brief Road is an element of a network. Road are strongly linked with Points.
 */
class Road {
public:
    /**
     * @brief Default constructor. Just instanciates a Road object.
     */
    Road() {}

    /**
     * @brief Constructor. Instanciates a Road object with a specific ID.
     * @param roadId The specific ID of the road
     */
    Road(long roadId)
        : m_edgeId(roadId)
    {
    }

    /**
     * @brief Destructor that clears all attributes
     */
    virtual ~Road();

    /**
     * @brief Add a point to the road.
     *
     * Insert the point to the vector of points (end position).
     *
     * @param pointId Id of the point to add.
     */
    void addPoint(int pointId);

    /**
     * @brief Add a neighbor of the road identified by its id to the road.
     *
     * Add the road id to the set of neighbors. This way the road knows its neighbors.
     *
     * @param roadId
     */
    void addNeighbor(long roadId);

    /**
     * @brief Get the vector of points composing the road
     * @return a vector of pointers to Point objects
     */
    std::vector<Point*> getListOfPoints() const;

    /**
     * @brief Get the id of the road
     * @return the id of the road
     * @todo refactor the name of the function
     * @todo delete edgeId() or getm_edgeId() because they do the same stuff
     */
    long getm_edgeId();

    /**
     * @brief print some informations about the road
     */
    void outputInfos() const;

    // accessors
    /**
     * @brief Get the id of the road
     * @return the id of the road
     * @todo refactor the name of the function
     * @todo delete edgeId() or getm_edgeId() because they do the same stuff
     */
    long edgeId() const { return m_edgeId; }

    /**
     * @brief Get the vector of points composing the road
     * @return a vector of Points' id
     */
    const std::vector<int>& vectorOfPointsId() const { return m_vectorOfPointsId; }

    /**
     * @brief get number of neighbors of the road
     * @return the number of neighbors of the road
     */
    int getNoOfNeighbors() const { return m_setOfNeighbors.size(); }
protected:
    long m_edgeId; ///<  Id of the road
    std::vector<int> m_vectorOfPointsId; ///<  Vector representing the id of each node (Point object)
    std::set<long> m_setOfNeighbors; ///<  Set of all roadId connected to this one (including this one)
};

#endif // ROAD_H
