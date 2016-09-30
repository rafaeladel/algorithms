#include <iostream>
#include <array>
#include <algorithm>
#include <fstream>
#include <cfloat>
#include <cmath>

struct Point {
    Point(double x = 0, double y = 0) {
        x_coordinate = x;
        y_coordinate = y;
    }
    double x_coordinate;
    double y_coordinate;
    static bool sortByX(const Point &lhs, const Point &rhs) {
      return lhs.x_coordinate < rhs.x_coordinate;
    }
    static bool sortByY(const Point &lhs, const Point &rhs) {
      return lhs.y_coordinate < rhs.y_coordinate;
     }
};

void initialize_points(std::array<Point, 10> &points) {
    double x, y;
    int i = 0;
    char c;
    std::ifstream infile("./points.txt");
    while((infile >> x >> c >> y) && (c == ',') && (i < 11)) {
        points[i++] = Point(x, y);
    }
}

double calculate_distance(Point p1, Point p2) {
    return std::sqrt(std::pow(p1.x_coordinate - p2.x_coordinate, 2) + std::pow(p1.y_coordinate - p2.y_coordinate , 2));
}

template <typename T>
std::array<Point, 2> eucledian_closest(T points) {
    std::array<Point, 2> closest_arr = {Point(), Point()};
    double closest_distance = DBL_MAX, distance = 0.0;

    for(int i = 0; i < points.size() - 1; i++){
      for(int j = i + 1; j < points.size(); j++) {
        distance = calculate_distance(points[i], points[j]);
        if(distance < closest_distance) {
          closest_distance = distance;
          closest_arr[0] = points[i];
          closest_arr[1] = points[j];
        }
      }
    }
    return closest_arr;
}

template <std::size_t SIZE>
std::array<Point, 2> closest_side_pair(std::array<Point, SIZE> &points, std::array<Point, SIZE> &x_arr, std::array<Point, SIZE> &y_arr) {
    std::size_t delimeter = SIZE / 2 ;
    if(delimeter <= 3) {
      return eucledian_closest(points);
    }
    std::array<Point, 2> closest_left, closest_right, result;
    std::array<Point, SIZE / 2> p_temp, x_temp, y_temp;

    //p_l, x_l, x_r
    std::copy(points.begin(), points.begin() + delimeter, p_temp.begin());
    std::copy(x_arr.begin(), x_arr.begin() + delimeter, x_temp.begin());
    std::copy(y_arr.begin(), y_arr.begin() + delimeter, y_temp.begin());
    closest_left = closest_side_pair(p_temp, x_temp, y_temp);

    //p_r, x_r, y_r
    std::copy(points.begin() + delimeter, points.end(), p_temp.begin());
    std::copy(x_arr.begin() + delimeter, x_arr.end(), x_temp.begin());
    std::copy(y_arr.begin() + delimeter, y_arr.end(), y_temp.begin());
    closest_right = closest_side_pair(p_temp, x_temp, y_temp);

    if(calculate_distance(closest_left.front(), closest_left.back()) < calculate_distance(closest_right.front(), closest_right.back())) {
      result = closest_left;
    } else {
      result = closest_right;
    }
    return result;
}

template<std::size_t SIZE>
std::array<Point, 2> closest_split_pair(std::array<Point, SIZE> &points, std::array<Point, 2> &closest_side_pairs) {
    std::vector<Point> split_pairs;
    std::array<Point, 2> final_result = {Point(), Point()};
    double closest_distance = DBL_MAX, distance = 0.0;

    Point midpoint = points[SIZE/2];

    //filtering points to only points in sigma-2sigma rectangle
    for (size_t i = 0; i < SIZE; i++) {
      if(std::abs(points[i].x_coordinate - midpoint.x_coordinate) < calculate_distance(closest_side_pairs[0], closest_side_pairs[1])){
          split_pairs.push_back(points[i]);
      }
    }

    //finding closest pair in split_pairs
    for (size_t i = 0; i < split_pairs.size() - 1; i++) {
      for (size_t j = i+1; (j < 7) && (j < split_pairs.size()) ; j++) {
        distance = calculate_distance(split_pairs[i], split_pairs[j]);
        if(distance < closest_distance) {
          closest_distance = distance;
          final_result[0] = split_pairs[i];
          final_result[1] = split_pairs[j];
        }
      }
    }

    //comparing split paris distance and side pairs distance
    if(calculate_distance(closest_side_pairs.front(), closest_side_pairs.back()) < calculate_distance(final_result.front(), final_result.back())) {
      final_result = closest_side_pairs;
    }
    return final_result;
}

int main()
{
    std::array<Point, 10> points;
    initialize_points(points);

    std::array<Point, 10> x_p = points;
    std::array<Point, 10> y_p = points;
    std::sort(x_p.begin(), x_p.end(), Point::sortByX);
    std::sort(y_p.begin(), y_p.end(), Point::sortByY);

    std::array<Point, 2> closest_result = closest_side_pair(points, x_p, y_p);
    closest_result = closest_split_pair(points, closest_result);
    std::cout << "Closest pair are: " << std::endl;
    for(Point p: closest_result) {
        std::cout << p.x_coordinate << ", " << p.y_coordinate << std::endl;
    }
}
