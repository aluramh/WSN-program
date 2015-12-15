#ifndef ListaLineal_ListaLineal_h
#define ListaLineal_ListaLineal_h
using namespace std;

class Node {
public:
	int info;
	double x;
	double y;
	double z;
	Node() { }
	Node(int dato) { info = dato;  }
	Node(int dato, double xval, double yval, double zval) {
		info = dato; 
		x = xval;
		y = yval; 
		z = zval; 
	}

	double getInfo() {return this->info;}
	double getX() { return this->x; }
	double getY() { return this->y; }
	double getZ() { return this->z; }
};

#endif
