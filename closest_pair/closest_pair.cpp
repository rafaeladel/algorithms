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

using p_iterator = std::vector<Point>::iterator;

template<std::size_t SIZE>
using p_iterators_array = std::array<std::vector<Point>::iterator, SIZE>;

void initialize_points(std::vector<Point> &points) {
    double x, y;
    char c;
    std::ifstream infile("./points.txt");
    while((infile >> x >> c >> y) && (c == ',')) {
        points.push_back(Point(x, y));
    }
}

double calculate_distance(Point &p1, Point &p2) {
    return std::sqrt(std::pow(p1.x_coordinate - p2.x_coordinate, 2) + std::pow(p1.y_coordinate - p2.y_coordinate , 2));
}

template<typename T>
p_iterators_array<2> eucledian_closest(T &points, int size) {
    p_iterators_array<2> closest_arr;
    double closest_distance = DBL_MAX, distance = 0.0;

    for(int i = 0; i < size - 1; i++){
      for(int j = i + 1; j < size; j++) {
        distance = calculate_distance(points[i], points[j]);
        if(distance < closest_distance ) {
          closest_distance = distance;
          closest_arr[0] = points + i;
          closest_arr[1] = points + j;
        }
      }
    }
    return closest_arr;
}

p_iterators_array<2> closest_split_pair(p_iterator points_iterator, p_iterators_array<2> &closest_side_pairs, std::size_t size) {
    std::vector<p_iterator> split_pairs;
    p_iterators_array<2> final_result;
    double closest_distance = DBL_MAX, distance = 0.0;

    p_iterator midpoint = points_iterator + (size/2);

    //filtering points to only points in sigma-2sigma rectangle
    for (size_t i = 0; i < size; i++) {
      if(std::abs(points_iterator[i].x_coordinate - midpoint->x_coordinate) < calculate_distance(*(closest_side_pairs[0]), *(closest_side_pairs[1]))){
          split_pairs.push_back(points_iterator + i);
      }
    }

    //finding closest pair in split_pairs
    for (size_t i = 0; i < split_pairs.size() - 1; i++) {
      for (size_t j = i+1; (j < 7) && (j < split_pairs.size()) ; j++) {
        distance = calculate_distance(*(split_pairs[i]), *(split_pairs[j]));
        if(distance < closest_distance ) {
          closest_distance = distance;
          final_result[0] = split_pairs[i];
          final_result[1] = split_pairs[j];
        }
      }
    }

    //comparing split paris distance and side pairs distance
    if(calculate_distance(*(closest_side_pairs.front()), *(closest_side_pairs.back())) < calculate_distance(*(final_result.front()), *(final_result.back()))) {
      final_result = closest_side_pairs;
    }
    return final_result;
}

p_iterators_array<2> closest_side_pair(p_iterator points_iterator, p_iterator x_arr_iterator, p_iterator y_arr_iterator, std::size_t size) {
    std::size_t delimeter = size / 2 ;
    if(delimeter <= 3) {
      return eucledian_closest(points_iterator, delimeter);
    }
    p_iterators_array<2> closest_left, closest_right, result;

    closest_left = closest_side_pair(points_iterator, x_arr_iterator, y_arr_iterator, delimeter);
    closest_right = closest_side_pair(points_iterator + delimeter, x_arr_iterator + delimeter, y_arr_iterator + delimeter, delimeter);

    if(calculate_distance(*(closest_left.front()), *(closest_left.back())) < calculate_distance(*(closest_right.front()), *(closest_right.back()))) {
      result = closest_left;
    } else {
      result = closest_right;
    }
    return closest_split_pair(points_iterator, result, size);
}

int main()
{
    std::vector<Point> points;
    initialize_points(points);

    std::vector<Point> x_p = points;
    std::vector<Point> y_p = points;
    std::sort(x_p.begin(), x_p.end(), Point::sortByX);
    std::sort(y_p.begin(), y_p.end(), Point::sortByY);

    p_iterators_array<2> closest_result = closest_side_pair(points.begin(), x_p.begin(), y_p.begin(), points.size());
    std::cout << "Closest pair are: " << std::endl;
    for(auto p: closest_result) {
        std::cout << p->x_coordinate << ", " << p->y_coordinate << std::endl;
    }
}
