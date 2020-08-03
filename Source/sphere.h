#pragma once
class sphere {
public:
	sphere();
	~sphere();
	int createSphereArray();
	double getSize() { return size; }
private:
	double size;
};