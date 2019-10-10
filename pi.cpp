// estimate pi (3.1415...) using monte carlo method
// r = 0.5 (bound by square)
// area of square = 2r*2r = 4r^2 = 4*(1/4) = 1
// area of circle = πr^2 = (1/4)π
// divide area of circle by area of square
// (1/4)π = circle area / square area
// π = 4(circle area / square area)
// now, if we plot enough points randomly in our area:
// π = 4(points in circle / points in square)

#include <iostream>
#include <random>
#include <string>

using namespace std;

// global rng
minstd_rand& global_rng () {
  static minstd_rand rng;
  return rng;
}

// seed the rng
void randomize() {
  static random_device rd;
  global_rng().seed(rd());
}

// return a random float [0,1]
float rand_float() {
  return static_cast<float>(global_rng()() + 1)/(global_rng().max() + 1);
}

int main(int argc, char **argv) {
  int n;
  if (argc < 2) { // # if no. of points isnt passed in
    string s;
    cin >> s;
    n = stoi(s);
  } else {
    n = stoi(argv[1]);
  }
  cout << "Number of points to plot is " << n << endl;
  
  randomize(); // seed rng (avoid the same outcome every time)

  double x{0}, y{0};
  int boundPoints{0};

  for (int i = 0; i < n; i++) {
    x = rand_float();
    y = rand_float();
    // if x^2 + y^2 (centered on axis) is less than r^2
    if (pow(x - 0.5, 2) + pow(y - 0.5, 2) < 0.25) 
        boundPoints++;
  }

  double estimatedPi = 4.0 * ((float)boundPoints/(float)n); // n is also the number of points inside the box
  cout.precision(17);
  cout << "The value of pi is estimated to: " << estimatedPi << endl;
  cout << n << " points, " << boundPoints << " points in circle." << endl;
  constexpr double realPi = atan(1)*4;
  cout << "the real value of pi is: " << realPi << endl;
  cout.precision(4);
  double pc{100*(realPi-estimatedPi)/realPi};
  cout << "estimated pi is " << pc << "% off." << endl;
  return 0;
}
