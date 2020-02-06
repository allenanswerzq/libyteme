#include <bits/stdc++.h>
using namespace std;

int dcmp(double a, double b) {
  const double eps = 1e-9;
  if (fabs(a - b) < eps) {
    // a equals b
    return 0;
  }
  if (b + eps < a) {
    // a greater than b
    return 1;
  }
  // a smaller than b
  return -1;
}

bool dcheck(double a, double b) {
  const double prec = 1e-6;
  double err = fabs(a - b) / max(1.0, fabs(b));
  return (dcmp(err, prec) < 1);
}
