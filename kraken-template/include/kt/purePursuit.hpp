#pragma once

#include "api.h"

namespace kt
{
    namespace purePursuit
    {
        struct Point
        {
            double x;
            double y;
        };

        Point getLookaheadPoint(std::initializer_list<Point> path, double x_position, double y_position, double distance);
        double angleToPoint(double x, double y, double x_ahead, double y_ahead);
        double distance(Point current, Point aheadpoint);
    }
}