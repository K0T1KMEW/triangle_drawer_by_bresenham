#pragma once 
#include <iostream>
#include <vector>

namespace Geometry {

	struct Point {
		int x;
		int y;
		Point() = default;
		Point(int a, int b);
	};

	class Triangle {
	private:
		Point point[3];
		int max_side;
	public:
		Triangle(Point triangle[3]);

		void AlgoritmBresenham();

		friend std::ostream& operator<<(std::ostream& str, const std::vector<std::vector<char>>& field);
	};
	std::ostream& operator<<(std::ostream& str, const std::vector<std::vector<char>>& field);
}