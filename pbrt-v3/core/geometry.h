#ifndef CV_PBRT_CORE_GEOMETRY_H
#define CV_PBRT_CORE_GEOMETRY_H

#include <pbrt.h>

namespace pbrt
{

template<typename T>
inline bool isNaN(const T x)
{
	return std::isnan(x);
}
template<>
inline bool isNaN(const int x)
{
	return false;
}

template<typename T, uint n>
class vec
{
private:

	T data[n];

public:

	template <typename... Ts>
	vec(Ts... vals)
		:data{vals...}
	{
		
	}

	T operator[](int i) const { return data[i];}
	T& operator[](int i) { return data[i];}

};

}

#endif