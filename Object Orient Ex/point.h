class Point {
public:
	Point(double x, double y);
	double distance(const Point& p) const;

private:
	double x;
	double y;
};