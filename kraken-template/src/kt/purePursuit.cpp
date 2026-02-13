#include "main.h"
#include "kt/purePursuit.hpp"
#include <cmath>
#include <vector>

namespace kt
{
    namespace purePursuit
    {
        struct Point getLookaheadPoint(std::initializer_list<Point> path, double x_position, double y_position, double distance)
        {
            std::vector<Point> points(path.begin(), path.end());
            if (points.size() == 0)
            {
                return {x_position, y_position};
            }
            if (points.size() == 1)
            {
                return points[0];
            }

            Point best = points.back();
            int best_segment = -1;
            double best_t = -1.0;

            for (size_t i = 0; i + 1 < points.size(); i++)
            {
                Point p1 = points[i];
                Point p2 = points[i + 1];
                double dx = p2.x - p1.x;
                double dy = p2.y - p1.y;

                double fx = p1.x - x_position;
                double fy = p1.y - y_position;

                double a = (dx * dx) + (dy * dy);
                double b = 2.0 * ((fx * dx) + (fy * dy));
                double c = (fx * fx) + (fy * fy) - (distance * distance);

                double discriminant = (b * b) - (4.0 * a * c);
                if (a == 0 || discriminant < 0)
                {
                    continue;
                }

                discriminant = sqrt(discriminant);
                double t1 = (-b - discriminant) / (2.0 * a);
                double t2 = (-b + discriminant) / (2.0 * a);

                auto use_t = [&](double t)
                {
                    if (t < 0 || t > 1)
                    {
                        return;
                    }
                    if (static_cast<int>(i) > best_segment || (static_cast<int>(i) == best_segment && t > best_t))
                    {
                        best_segment = static_cast<int>(i);
                        best_t = t;
                        best = {p1.x + (dx * t), p1.y + (dy * t)};
                    }
                };

                use_t(t1);
                use_t(t2);
            }

            return best;
        }

        double angleToPoint(double x, double y, double x_ahead, double y_ahead)
        {
            return atan2(y_ahead - y, x_ahead - x) * (180.0 / M_PI);
        }

        double distance(Point current, Point goal)
        {
            return sqrt(pow(goal.x - current.x, 2) + pow(goal.y - current.y, 2));
        }
    }
}
