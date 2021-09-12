#include "CVector.h"

CVector::Vector3 CVector::Normalize(Vector3 _vec3)
{
	const double len = Magnitude(_vec3);
	_vec3 /= len;
	return _vec3;
}

float CVector::Dot(Vector3 _a, Vector3 _b)
{
	float product = 0;
	product += _a.x * _b.x;
	product += _a.y * _b.y;
	product += _a.z * _b.z;
	return product;
}

CVector::Vector3 CVector::CrossProduct(Vector3 _a, Vector3 _b)
{
	Vector3 product;
	product.x = _a.y * _b.z - _a.z * _b.y;
	product.y = _a.z * _b.x - _a.x * _b.z;
	product.z = _a.x * _b.y - _a.y * _b.x;
	return product;
}

float CVector::Magnitude(Vector3 _vec3)
{
	return sqrt((_vec3.x * _vec3.x) + (_vec3.y * _vec3.y) + (_vec3.z * _vec3.z));
}

std::string CVector::Stringify(Vector3 _vec3)
{
	std::string result = "";
	result += "(" + std::to_string(_vec3.x) + ", " + std::to_string(_vec3.y) + ", " + std::to_string(_vec3.z) + " )";
	return result;
}

double CVector::Angle(Vector3 _vec3)
{
	return atan(_vec3.y / _vec3.x) / (2 * 3.14f) * 360;
}

double CVector::AngleBetween(Vector3 _A, Vector3 _B)
{
	double dotProduct = _A.x * _B.x + _A.y * _B.y;
	double determinant = _A.x * _B.y - _A.y * _B.x;
	return (atan2(determinant, dotProduct) / (M_PI)*180);
}

sf::Vector2f CVector::ToVector2f(Vector3 _vec3)
{
	return sf::Vector2f(_vec3.x, _vec3.y);
}

CVector::Vector3 CVector::ToVector3(sf::Vector2f _vec2f)
{
	return CVector::Vector3{_vec2f.x, _vec2f.y, 0.0f};
}

bool CVector::TestPointInTriBarycentric(Vector3 _point, Vector3 _triA, Vector3 _triB, Vector3 _triC)
{
	float ABC = CVector::Dot(CVector::Vector3{0, 0, 1}, CVector::CrossProduct((_triB - _triA), (_triC - _triA)));
	float PBC = CVector::Dot(CVector::Vector3{0, 0, 1}, CVector::CrossProduct((_triB - _point), (_triC - _point)));
	float PCA = CVector::Dot(CVector::Vector3{0, 0, 1}, CVector::CrossProduct((_triC - _point), (_triA - _point)));
	CVector::Vector3 bary{PBC / ABC, PCA / ABC, 1.0f - (PBC / ABC) - (PCA / ABC)};
	return (bary.y >= 0 && bary.y <= 1 && bary.z >= 0 && bary.z <= 1 && (bary.y + bary.z) <= 1);
}