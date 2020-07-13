#pragma once
class grid {
public:
	grid();
	~grid();
	int createGridArray();
	double getSize() { return size; }
private:
	double size;
};