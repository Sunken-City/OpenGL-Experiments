#pragma once
#include <vector>

#include "Geometry.h"
#include "Face.h"

class Triangle : public virtual Geometry	
{
public:
	Triangle();
	~Triangle();
	void draw();
};