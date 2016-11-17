#ifndef BOXNODE_H
#define BOXNODE_H

#include "box.h"

class BoxNode : public Box {

public:
    BoxNode() {}

    BoxNode(Point low, Point high, int mother, int daughterOne, int daughterTwo, int myptlo, int mypthi)
        : Box(low, high)
        , m_motherBox(mother)
        , m_daughterBox1(daughterOne)
        , m_daughterBox2(daughterTwo)
        , m_indexOfLowerPoint(myptlo)
        , m_indexOfUpperPoint(mypthi)
    {
    }

    // protected: // no protection, classe only used within kdtree
    int m_motherBox, m_daughterBox1, m_daughterBox2;
    int m_indexOfLowerPoint, m_indexOfUpperPoint;
};

#endif // BOXNODE_H
