#pragma once
enum Mode { RAIN, MIST, WATERFALL, STATIC };

class System
{
public:
	System() {};
	virtual void generateSpringDemo()=0;
	virtual void changeModes(int i)=0;
	virtual void clear()=0;
	virtual void kill()=0;
	virtual void generate()=0;
	virtual void setBlast()=0;
	virtual void AddK()=0;
	virtual void update(double t)=0;
};

