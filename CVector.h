#ifndef CVECTOR_H
#define CVECTOR_H
#include <cmath>
#include <iostream>
#include <string>
#include <SFML/System.hpp>

class CVector
{
public:
	struct Vector3
	{
		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;

		Vector3 &operator+=(const Vector3 &_rhs)
		{
			this->x += _rhs.x;
			this->y += _rhs.y;
			this->z += _rhs.z;
			return *this;
		}
		Vector3 operator+(const Vector3 &_rhs)
		{
			Vector3 newval = *this;
			newval += _rhs;
			return newval;
		}
		Vector3 operator-=(const Vector3 &_rhs)
		{
			this->x -= _rhs.x;
			this->y -= _rhs.y;
			this->z -= _rhs.z;
			return *this;
		}
		Vector3 operator-(const Vector3 &_rhs)
		{
			Vector3 newval = *this;
			newval -= _rhs;
			return newval;
		}
		Vector3 operator*=(const float &_rhs)
		{
			this->x *= _rhs;
			this->y *= _rhs;
			this->z *= _rhs;
			return *this;
		}
		Vector3 operator*(const float &_rhs)
		{
			Vector3 newval = *this;
			newval *= _rhs;
			return newval;
		}
		Vector3 operator/=(const float &_rhs)
		{
			this->x /= _rhs;
			this->y /= _rhs;
			this->z /= _rhs;
			return *this;
		}
		Vector3 operator/(const float &_rhs)
		{
			Vector3 newval = *this;
			newval /= _rhs;
			return newval;
		}
	};

	static Vector3 Normalize(Vector3 _vec3);
	static float Dot(Vector3 _a, Vector3 _b);
	static Vector3 CrossProduct(Vector3 _a, Vector3 _b);
	static float Magnitude(Vector3 _vec3);
	static std::string Stringify(Vector3 _vec3);
	static double Angle(Vector3 _vec3);
	static double AngleBetween(Vector3 _A, Vector3 _B);
	static bool TestPointInTriBarycentric(Vector3 _point, Vector3 _triA, Vector3 _triB, Vector3 _triC);
	static sf::Vector2f ToVector2f(Vector3 _vec3);
	static Vector3 ToVector3(sf::Vector2f _vec2f);
};
#endif