#include <iostream>
#include <vector>
#include <cmath>
#include "matplotlibcpp.h"  // Include Matplotlib for visualization

namespace plt = matplotlibcpp;

struct Point {
    float x, y;
    Point operator*(float scalar) const { return {x * scalar, y * scalar}; }
    Point operator+(const Point& other) const { return {x + other.x, y + other.y}; }
    Point operator-(const Point& other) const { return {x - other.x, y - other.y}; }
};

// Catmull-Rom interpolation
Point catmullRom(const Point& p0, const Point& p1, const Point& p2, const Point& p3, float t) {
    float t2 = t * t;
    float t3 = t2 * t;

    return p1 * (2.0f * t3 - 3.0f * t2 + 1.0f) +
           p2 * (-2.0f * t3 + 3.0f * t2) +
           p0 * (t3 - 2.0f * t2 + t) +
           p3 * (t3 - t2);
}

// Generate spline
std::vector<Point> generateSpline(const std::vector<Point>& controlPoints, int samplesPerSegment) {
    std::vector<Point> result;

    if (controlPoints.size() < 4) {
        std::cerr << "Not enough points for Catmull-Rom interpolation!\n";
        return result;
    }

    for (size_t i = 1; i < controlPoints.size() - 2; ++i) {
        for (int j = 0; j < samplesPerSegment; ++j) {
            float t = static_cast<float>(j) / samplesPerSegment;
            result.push_back(catmullRom(controlPoints[i - 1], controlPoints[i], controlPoints[i + 1], controlPoints[i + 2], t));
        }
    }

    return result;
}

// Plot the spline
void plotSpline(const std::vector<Point>& controlPoints, const std::vector<Point>& splinePoints) {
    std::vector<double> x_cp, y_cp, x_spline, y_spline;

    // Extract X and Y values
    for (const auto& p : controlPoints) {
        x_cp.push_back(p.x);
        y_cp.push_back(p.y);
    }
    for (const auto& p : splinePoints) {
        x_spline.push_back(p.x);
        y_spline.push_back(p.y);
    }

    // Plot control points
    plt::plot(x_cp, y_cp, "ro-"); // Red circles with lines
    // Plot spline
    plt::plot(x_spline, y_spline, "b-"); // Blue smooth line
    // Show plot
    plt::show();
}

int main() {
    std::vector<Point> controlPoints = {{0, 0}, {2, 3}, {4, 2}, {5, 5}}; // Control points
    int samplesPerSegment = 10;

    std::vector<Point> spline = generateSpline(controlPoints, samplesPerSegment);

    plotSpline(controlPoints, spline);

    return 0;
}
