/// Vector 3 class
/// Name: Robin Meyler

#include "MyVector3.h"
#include <string.h>
#define PI           3.14159265358979323846


MyVector3::MyVector3() :
	x{ 0.0 },
	y{ 0.0 },
	z{ 0.0 }
{
}


MyVector3::MyVector3(double t_x, double t_y, double t_z) :
	x{ t_x },
	y{ t_y },
	z{ t_z }
{
}

MyVector3::~MyVector3()
{
}

// Cast to double for each of the sfVectors

MyVector3::MyVector3(sf::Vector3i t_sfVector) :
	x{ static_cast<double>(t_sfVector.x) },
	y{ static_cast<double>(t_sfVector.y) },
	z{ static_cast<double>(t_sfVector.z) }
{
}
MyVector3::MyVector3(sf::Vector3f t_sfVector) :
	x{ static_cast<double>(t_sfVector.x) },
	y{ static_cast<double>(t_sfVector.y) },
	z{ static_cast<double>(t_sfVector.z) }
{
}
MyVector3::MyVector3(sf::Vector2i t_sfVector) :			// Z removed to 2i,u,f. Making the vector 2D
	x{ static_cast<double>(t_sfVector.x) },
	y{ static_cast<double>(t_sfVector.y) },
	z{ 0.0 }
{
}
MyVector3::MyVector3(sf::Vector2u t_sfVector) :
	x{ static_cast<double>(t_sfVector.x) },
	y{ static_cast<double>(t_sfVector.y) },
	z{ 0.0 }
{
}
MyVector3::MyVector3(sf::Vector2f t_sfVector) :
	x{ static_cast<double>(t_sfVector.x) },
	y{ static_cast<double>(t_sfVector.y) },
	z{ 0.0 }
{
}

bool MyVector3::operator==(const MyVector3 t_right) const
{
	const bool equality{ x == t_right.x && y == t_right.y && z == t_right.z };					// Checking the equality of the coordinates
	return equality;
}


bool MyVector3::operator!=(const MyVector3 t_right) const
{
	const bool inequality{ x != t_right.x || y != t_right.y || z != t_right.z};					// Checking the non-equality of the coordinates
	return inequality;
}

MyVector3 MyVector3::operator + (const MyVector3 t_right) const
{
	return MyVector3(x + t_right.x, y + t_right.y, z + t_right.z);					// Addition of two vectors
}


MyVector3 MyVector3::operator - (const MyVector3 t_right) const
{
	return MyVector3(x - t_right.x, y - t_right.y,z - t_right.z);					// Subtraction of two vectors
}

MyVector3 MyVector3::operator * (const double t_scalar) const
{
	return MyVector3(x*t_scalar, y*t_scalar, z*t_scalar);									// Vector double mulitplication
}

MyVector3 MyVector3::operator / (const double t_divisor) const
{
	if (t_divisor != 0)								// Can't be allowed to divide by 0
		return MyVector3(x / t_divisor, y / t_divisor, z / t_divisor);      // Dividing by a constant
	else
		return MyVector3{};
}

MyVector3 MyVector3::operator += (const MyVector3 t_right)
{														
	return MyVector3(x + t_right.x, y + t_right.y, z + t_right.z);			// Plus/ equals
}


MyVector3 MyVector3::operator -= (const MyVector3 t_right)
{
	return MyVector3(x - t_right.x, y - t_right.y, z - t_right.z);			// Minus/ equals
}

MyVector3 MyVector3::operator-()
{
	return MyVector3(-x, -y, -z);													// Minus of the vector coordinates
}

double MyVector3::length() const
{
	const double len = std::sqrt(x * x + y * y + z * z);					// Square root of the sum of the products of the vectors
	return len;
}


double MyVector3::lengthSquared() const
{
	const double lenSq = x*x + y*y + z*z;					// Pythagoras used to find Length Squared
	return lenSq;
}



std::string MyVector3::toString()
{
	const std::string output = "[" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z) + "]";  // String setup
	return output;
}

MyVector3 MyVector3::unit() const
{
	double mag = length();
	if (x != 0 && y != 0)											// If used to ensure I don't divide by 0
		return MyVector3(x*(1.0 / mag), y*(1.0 / mag), z *(1.0 / mag));
	else											// Multiply by 1/Magnitude to return a unit vector		
		return MyVector3(0, 0, 0);
}


void MyVector3::normalise()
{
	double mag = length();
	if (x != 0 && y != 0)											// If used to ensure I don't divide by 0
	{
							
		x = x*(1.0 / mag);				// Multiply by 1/Magnitude to normalise the vector
		y = y*(1.0 / mag);
		z = z*(1.0 / mag);
	}
	else
	{
		x = 0;
		y = 0;
	}
}

double MyVector3::dot(MyVector3 t_other) const
{
	double dot = x*t_other.x + y*t_other.y + z*t_other.z;					// Sum of the products to get the dot product
	return dot;
}

double MyVector3::angleBetween(MyVector3 t_other) const
{

	double dotProd = dot(t_other);									// Dot product found from both vectors
	double mag1 = length();									// Magnitude of both vectors
	double mag2 = t_other.length();
	double result = dotProd / (mag1*mag2);										// Dot over the magnitude product
	result = acos(result);													// acos used to get the angle in radians
	double answer = result*(180 / PI);					// Convert to Degrees
	return answer;
}

MyVector3 MyVector3::projection(const MyVector3 t_other) const
{
	double dotProd = dot(t_other);											// Dot Product
	double belowLine = lengthSquared();		// Length by itself making the length squared
	double answer = (dotProd / belowLine);								// Formula for projecting

	return MyVector3(answer*x, answer*y, answer*z);							// Multiplying answer by the vector
}

MyVector3 MyVector3::rejection(const MyVector3 t_other) const
{
	return MyVector3(t_other - projection(t_other));		// answer taken from oringal vector to get the remainder
}

MyVector3 MyVector3::crossProduct(const MyVector3 t_other)const
{
	return MyVector3((y*t_other.z) - (z*t_other.y), (z*t_other.x) - (x*t_other.z), (x*t_other.y) - (y*t_other.x));  // Formula for the cross product
}
MyVector3::operator sf::Vector2u()
{
	double changedX{ x };								// Making both the x and y postive and returning it
	double changedY{ y };
	if (changedX < 0)
	{
		changedX = -changedX;
	}
	if (changedY < 0)
	{
		changedY = -changedY;
	}
	return sf::Vector2u{ static_cast<unsigned>(changedX), static_cast<unsigned>(changedY) };
}

void MyVector3::reverseX()
{
	x = -x;									// Reversing the X, to use when bounced off the side coushins
}
void MyVector3::reverseY()
{
	y = -y;									// Reversing the Y, to use when bounced off the top coushins
}

