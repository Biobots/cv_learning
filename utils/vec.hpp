#ifndef CV_VEC_HPP
#define CV_VEC_HPP

#include <vector>
#include <cmath>

using namespace std;

template<typename T, int n>
struct vec
{
	T data[n];

	template <typename... Ts>
	vec(Ts... vals)
		:data{vals...}
	{
		
	}

	T operator[](int i) const { return data[i];}
	T& operator[](int i) { return data[i];}

	vec operator-() const
	{
		vec rst;
		for(int i = 0; i < n; i++)
		{
			rst[i] = -data[i];
		}
		return rst;
	}
	inline vec operator-(const vec& v) const
	{
		vec rst;
		for(int i = 0; i < n; i++)
		{
			rst[i] = data[i] - v[i];
		}
		return rst;
	}
	inline vec operator+(const vec& v) const
	{
		vec rst;
		for(int i = 0; i < n; i++)
		{
			rst[i] = data[i] + v[i];
		}
		return rst;
	}
	inline vec operator*(const vec& v) const
	{
		vec rst;
		for(int i = 0; i < n; i++)
		{
			rst[i] = data[i] * v[i];
		}
		return rst;
	}
	inline vec operator/(const vec& v) const
	{
		vec rst;
		for(int i = 0; i < n; i++)
		{
			rst[i] = data[i] / v[i];
		}
		return rst;
	}
	inline vec operator-(const T& v) const
	{
		vec rst;
		for(int i = 0; i < n; i++)
		{
			rst[i] = data[i] - v;
		}
		return rst;
	}
	inline vec operator+(const T& v) const
	{
		vec rst;
		for(int i = 0; i < n; i++)
		{
			rst[i] = data[i] + v;
		}
		return rst;
	}
	inline vec operator*(const T& v) const
	{
		vec rst;
		for(int i = 0; i < n; i++)
		{
			rst[i] = data[i] * v;
		}
		return rst;
	}
	inline vec operator/(const T& v) const
	{
		vec rst;
		for(int i = 0; i < n; i++)
		{
			rst[i] = data[i] / v;
		}
		return rst;
	}
	vec& operator+=(const vec& v)
	{
		for(int i = 0; i < n; i++)
		{
			data[i] += v[i];
		}
		return *this;
	}
	vec& operator-=(const vec& v)
	{
		for(int i = 0; i < n; i++)
		{
			data[i] -= v[i];
		}
		return *this;
	}
	vec& operator*=(const vec& v)
	{
		for(int i = 0; i < n; i++)
		{
			data[i] *= v[i];
		}
		return *this;
	}
	vec& operator/=(const vec& v)
	{
		for(int i = 0; i < n; i++)
		{
			data[i] /= v[i];
		}
		return *this;
	}
	vec& operator+=(const T& v)
	{
		for(int i = 0; i < n; i++)
		{
			data[i] += v;
		}
		return *this;
	}
	vec& operator-=(const T& v)
	{
		for(int i = 0; i < n; i++)
		{
			data[i] -= v;
		}
		return *this;
	}
	vec& operator*=(const T& v)
	{
		for(int i = 0; i < n; i++)
		{
			data[i] *= v;
		}
		return *this;
	}
	vec& operator/=(const T& v)
	{
		for(int i = 0; i < n; i++)
		{
			data[i] /= v;
		}
		return *this;
	}

	inline T dot(const vec& v1, const vec& v2)
	{
		return v1 * v2;
	}
	T square()
	{
		T sum;
		for(int i = 0; i < n; i++)
		{
			sum += data[i] * data[i];
		}
		return sum;
	}
	T length()
	{
		return sqrt(square());
	}
};

template<typename T, int n>
inline vec<T, n> operator*(const T& t, const vec<T, n>& v)
{
	vec<T, n> rst;
	for(int i = 0; i < n; i++)
	{
		rst[i] = v[i] * t;
	}
	return rst;
}

template<int n>
inline vec<float, n> operator*(const double& t, const vec<float, n>& v)
{
	vec<float, n> rst;
	for(int i = 0; i < n; i++)
	{
		rst[i] = v[i] * t;
	}
	return rst;
}

struct rgb : vec<short, 3>
{
	template <typename... Ts>
	rgb(Ts... vals) : vec<short, 3>(vals...) {}
	rgb(vec<short, 3>&& val)
	{
		copy(val.data, val.data + 3, this->data);
	}
	short& r() { return data[0];}
	short& g() { return data[1];}
	short& b() { return data[2];}
};

struct rgbf : vec<float, 3>
{
	template <typename... Ts>
	rgbf(Ts... vals) : vec<float, 3>(vals...) {}
	rgbf(vec<float, 3>&& val)
	{
		copy(val.data, val.data + 3, this->data);
	}
	float& r() { return data[0];}
	float& g() { return data[1];}
	float& b() { return data[2];}
};

struct bgr : vec<short, 3>
{
	template <typename... Ts>
	bgr(Ts... vals) : vec<short, 3>(vals...) {}
	bgr(vec<short, 3>&& val)
	{
		copy(val.data, val.data + 3, this->data);
	}
	short& b() { return data[0];}
	short& g() { return data[1];}
	short& r() { return data[2];}
};

struct yuv : vec<short, 3>
{
	template <typename... Ts>
	yuv(Ts... vals) : vec<short, 3>(vals...) {}
	yuv(vec<short, 3>&& val)
	{
		copy(val.data, val.data + 3, this->data);
	}
	short& y() { return data[0];}
	short& u() { return data[1];}
	short& v() { return data[2];}
};

template<typename T>
struct vec2 : vec<T, 2>
{
	template <typename... Ts>
	vec2(Ts... vals) : vec<T, 2>(vals...) {}
	vec2(vec<T, 2>&& val)
	{
		copy(val.data, val.data + 2, this->data);
	}
	T& x() { return this->data[0];}
	T& y() { return this->data[1];}
};

template<typename T>
struct vec3 : vec<T, 3>
{
	template <typename... Ts>
	vec3(Ts... vals) : vec<T, 3>(vals...) {}
	vec3(vec<T, 3>&& val)
	{
		copy(val.data, val.data + 3, this->data);
	}
	T& x() { return this->data[0];}
	T& y() { return this->data[1];}
	T& z() { return this->data[2];}

	inline vec3 cross(const vec3& u, const vec3& v)
	{
		return vec3(
				u.data[1] * v.data[2] - u.data[2] * v.data[1],
				u.data[2] * v.data[0] - u.data[0] * v.data[2],
				u.data[0] * v.data[1] - u.data[1] * v.data[0]
			);
	}
};

using vec3f = vec3<float>;

template<typename T>
struct vec4 : vec<T, 4>
{
	template <typename... Ts>
	vec4(Ts... vals) : vec<T, 4>(vals...) {}
	vec4(vec<T, 4>&& val)
	{
		copy(val.data, val.data + 4, this->data);
	}
	T& x() { return this->data[0];}
	T& y() { return this->data[1];}
	T& z() { return this->data[2];}
	T& w() { return this->data[3];}
};

template<typename T, int n>
inline vec<T, n> unit_vector(vec<T, n> v)
{
	return v / v.length();
}

inline vec3f unit_vector(vec3f v)
{
	return v / v.length();
}

#endif