#ifndef ROAD_H
#define ROAD_H

#include "pointroad.h"
#include "track.h"

#include <set>
#include <string>
#include <vector>

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
     * @brief addPoint
     * @param pointId
     */
    void addPoint(int pointId);
    /**
     * @brief addNeighbor
     * @param roadId
     */
    void addNeighbor(long roadId);

    /**
     * @brief getListOfPoints
     * @return
     */
    std::vector<Point*> getListOfPoints() const;
    /**
     * @brief getm_edgeId
     * @return
     */
    long getm_edgeId();

    /**
     * @brief outputInfos
     */
    void outputInfos() const;

    // accessors
    /**
     * @brief edgeId
     * @return
     */
    long edgeId() const { return m_edgeId; }
    /**
     * @brief vectorOfPointsId
     * @return
     */
    const std::vector<int>& vectorOfPointsId() const { return m_vectorOfPointsId; }
    /**
     * @brief getNoOfNeighbors
     * @return
     */
    int getNoOfNeighbors() const { return m_setOfNeighbors.size(); }
protected:
    long m_edgeId;
    std::vector<int> m_vectorOfPointsId;
    std::set<long> m_setOfNeighbors; /*< Set of all roadId connected to this one (including this one) */
};

#endif // ROAD_H
