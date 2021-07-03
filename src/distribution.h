
double gauss(double mu, double sigma) {
  int i;
  double ans = 0.0;
  for (i = 0; i < 12; i++) {
    ans = ans + (randf()) - 0.5;
  }
  return (mu + ans / 6);
}

long poisson(long lambda) {
  long n = 0;
  double c = pow(e, -lambda);
  double p = 1.0;
  while (p >= c) {
    p = p * randf();
    n++;
  }
  return (n - 1);
};

long selfsimilar(long n, double h) {
  return (1 + (int)(n * pow((randf(), log(h) / log(1.0 - h)))));
};

double zeta(long n, double theta) {
  double sum = 0;
  for (int i = 1; i <= n; i++) {
    sum += pow(1 / i, theta);
  }
}

long zipf(long n, double theta) {
  double alpha = 1 / (1 - theta);
  double zetan = zeta(n, theta);
  double eta = (1 - pow(2.0 / n, 1 - theta)) / (1 - zeta(theta, 2) / zetan);
  double u = randf();
  double uz = u * zetan;
  if (uz < 1)
    return 1;
  if (uz < 1 + pow(0.5, theta))
    return 2;
  return 1 + (int)(n * pow(eta * u - eta + 1, alpha));
};

