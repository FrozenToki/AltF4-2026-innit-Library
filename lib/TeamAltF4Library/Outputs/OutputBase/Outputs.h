#pragma once
#include <Arduino.h>


class OutputBase{
protected:
	String name;
	String type;
public:
	OutputBase(String n); 
	
	static String LED;
	static String MOTOR;

	String getName() const;
	String getType() const;

	String& getNameRef();
	
	OutputBase();
};
