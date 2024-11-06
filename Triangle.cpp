#include "Geometry.hpp" 
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <limits>

using namespace std;
namespace Geometry {

	Point::Point(int a, int b) {
		this->x = a;
		this->y = b;
	}

	static inline float lineLen(Point p1, Point p2) {
		return static_cast <float> (sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y)));
	}

	static inline int return_max_side(Point point[3]) {
		int max_x = std::max({ point[0].x, point[1].x, point[2].x });
		int max_y = std::max({ point[0].y, point[1].y, point[2].y });
		return max(max_x, max_y) + 1;
	}

	static inline void shift_points(Point point[3]) {

		int min_x = min({ point[0].x, point[1].x, point[2].x });
		int min_y = min({ point[0].y, point[1].y, point[2].y });

		for (int i = 0; i < 3; i++) {
			point[i].x -= min_x;
			point[i].y -= min_y;
		}
	}

	Triangle::Triangle(Point point[3]) {
	
		float len_1 = lineLen(point[0], point[1]);
		float len_2 = lineLen(point[0], point[2]);
		float len_3 = lineLen(point[1], point[2]);

		if (len_1 + len_2 <= len_3 || len_1 + len_3 <= len_2 || len_2 + len_3 <= len_1) {
			throw string("ERROR : Not a triangle.");
		}

		shift_points(point);

		this->point[0] = point[0];
		this->point[1] = point[1];
		this->point[2] = point[2];

		this->max_side = return_max_side(point);
	}

	void Triangle::AlgoritmBresenham() {
		vector<vector<char>> field(this->max_side, vector<char>(this->max_side, '.'));

		for (int k = 0; k < 3; k++) {
			if (this->point[k].x >= 0 && this->point[k].x < this->max_side &&
				this->point[k].y >= 0 && this->point[k].y < this->max_side) {
				field[this->point[k].y][this->point[k].x] = '*';
			}
			else {
				throw string("ERROR: Point out of bounds");
			}
		}

		for (int k = 0; k < 3; k++) {
			int z = (k + 1 < 3) ? k + 1 : 0;
			int x0 = this->point[k].x;
			int y0 = this->point[k].y;
			int x1 = this->point[z].x;
			int y1 = this->point[z].y;

			int dx = x1 - x0;
			int dy = y1 - y0;

			int sx = (dx >= 0) ? 1 : -1;
			int sy = (dy >= 0) ? 1 : -1;
			dx = abs(dx);
			dy = abs(dy);

			if (dx > dy) {
				int err = dx / 2;
				while (x0 != x1) {
					if (x0 >= 0 && x0 < this->max_side && y0 >= 0 && y0 < this->max_side) {
						field[y0][x0] = '*';
					}
					err -= dy;
					if (err < 0) {
						y0 += sy;
						err += dx;
					}
					x0 += sx;
				}
			}
			else {
				int err = dy / 2;
				while (y0 != y1) {
					if (x0 >= 0 && x0 < this->max_side && y0 >= 0 && y0 < this->max_side) {
						field[y0][x0] = '*';
					}
					err -= dx;
					if (err < 0) {
						x0 += sx;
						err += dy;
					}
					y0 += sy;
				}
			}
		}

		cout << field;
	}

	ostream& operator<<(ostream& str, const vector<vector<char>>& field) {
		for (int i = field.size() - 1; i >= 0; i--) {
			for (int j = 0; j < field[i].size(); j++) {
				str << field[i][j] << " ";
			}
			str << endl;
		}
		return str;
	}
}