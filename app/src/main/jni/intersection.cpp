#include "intersection.h"
#include "object.h"
#include "physics.h"
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <memory>


namespace intersection {

// finds a and b coefficients for y = a * x + b line equation from the line segment
bool FindLineEquationFromLineSegment(const LineSegment& ls, Line& line) {
	Vec2 v = ls.e - ls.s;
	if (abs(v.x()) < MIN_FLOAT)	// v.x() == 0 => eq: x = const
		return false;

	line.a = v.y() / v.x();
	line.b = ls.s.y() - line.a * ls.s.x();

//	std::cout << "line : y = " << line.a << " * x + " << line.b << std::endl;
	return true;
}

bool FindIntersectionOfTwoLines(const LineSegment& ls1, const LineSegment& ls2, Vec2& res) {
	Line line1;
	bool res1 = FindLineEquationFromLineSegment(ls1, line1);
	Line line2;
	bool res2 = FindLineEquationFromLineSegment(ls2, line2);

	if (!res1 && !res2) {
		// x1 = const; x2 = const
		if (ls1.s.x() != ls2.s.x())
			return false;
		// consider parallel line segments as not a collision
		return false;
	} else if (!res1) {
		// x1 = const
		// y2 = a2 * x2 + b2
		res.x() = ls1.s.x();
		res.y() = line2.a * res.x() + line2.b;
	} else if (!res2) {
		// y1 = a1 * x1 + b1
		// x2 = const
		res.x() = ls2.s.x();
		res.y() = line1.a * res.x() + line1.b;
	} else {
		// y1 = a1 * x1 + b1
		// y2 = a2 * x2 + b2
		res.x() = (line1.b - line2.b) / (line2.a - line1.a);
		res.y() = line1.a * res.x() + line1.b;
	}
//	std::cout << "line intersection: " << res << std::endl;
	return true;
}

bool PointInsideSegmentBox(Vec2 p, const LineSegment& ls) {
	Vec2 min(ls.s);
	Vec2 max(ls.e);
	min.x() = ls.s.x() < ls.e.x() ? ls.s.x() : ls.e.x();
	min.y() = ls.s.y() < ls.e.y() ? ls.s.y() : ls.e.y();
	max.x() = ls.s.x() > ls.e.x() ? ls.s.x() : ls.e.x();
	max.y() = ls.s.y() > ls.e.y() ? ls.s.y() : ls.e.y();
	if (p.x() < min.x() ||
		p.x() > max.x() ||
		p.y() < min.y() ||
		p.y() > max.y()) {
		
		return false;
	}
	return true;
}

bool CheckIntersectionOfTwoSegments(const LineSegment& ls1, const LineSegment& ls2) {
	Vec2 res;
	if (!FindIntersectionOfTwoLines(ls1, ls2, res))
		return false;
	// should check whether segments cover intersection of lines or not
	return PointInsideSegmentBox(res, ls1) && PointInsideSegmentBox(res, ls2);
}

bool CheckObjectIntersection(Object* obj1, Object* obj2) {
    if (!obj1 || !obj2)
        return false;
    if (physics::CheckNoCollisionFast(obj1, obj2))
        return false;
    if (obj1->type() == obj2->type())
        return false;

    for (int i = 0; i < (obj1->object_points().size() - 1); i++) {
        Vec2 s1, e1;
        obj1->GetObjectPointInWorld(s1, i);
        obj1->GetObjectPointInWorld(e1, i + 1);
        for (int j = 0; j < (obj2->object_points().size() - 1); j++) {
            Vec2 s2, e2;
            obj2->GetObjectPointInWorld(s2, j);
            obj2->GetObjectPointInWorld(e2, j + 1);
            if (CheckIntersectionOfTwoSegments(LineSegment(s1, e1), LineSegment(s2, e2)))
                return true;
        }
    }

    return false;
}

}

