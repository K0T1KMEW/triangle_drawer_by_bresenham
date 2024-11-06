#include "Geometry.hpp"
#include <iostream>

using namespace std;
using namespace Geometry;

int main(){
	try{
		Point point[3] = {Point(-8, -6), Point(6, 8), Point(16, -35)};
		Triangle triangle(point);
		triangle.AlgoritmBresenham();
	}catch(std::string error){
		cout << error << std :: endl;
	}
	return 0;
}
