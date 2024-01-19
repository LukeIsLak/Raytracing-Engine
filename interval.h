#ifndef INTERVAL_H
#define INTERVAL_H

// Utility class that manages intervals between multiple objects
class interval {
 public:
  double min;
  double max;

 interval() : min(+infinity), max(-infinity) {}
 interval(double _min, double _max) : min(_min), max(_max) {}
  
  //Is a double contained in the interval
  bool contains(double x) const {
    return min <= x && x <= max;
  }

  //Is a double surrounded by the interval
  bool surround (double x) const {
    return min < x && x < max;
  }

  double clamp (double x) const {
    return (x > max) ? max : (x < min) ? min : x;
  }

  // Useful for non object entities, such as a skybox and empty objects.
  static const interval empty;
  static const interval universe;
};

#endif
