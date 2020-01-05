#ifndef VECTOR_2D_H
#define VECTOR_2D_H

template <class T>
class Vector2
{
public:
    union {
        struct { T x, y; };
    };

public:
	Vector2()
	{
	}

	Vector2(const T& x_input, const T& y_input)
		: x(x_input), y(y_input)
	{}

	~Vector2()
	{
	}

	void operator += (const Vector2<T>& v)
	{
		x += v.x;
		y += v.y;
	}

	void operator -= (const Vector2<T>& v)
	{
		x -= v.x;
		y -= v.y;
	}

	void operator *= (const T& s)
	{
		x *= s;
		y *= s;
	}

	void operator /= (const T& s)
	{
		const T one_over_s = T(1) / s;
		x *= one_over_s;
		y *= one_over_s;
	}

	Vector2<T> operator + (const Vector2<T>& v) const
	{
		return Vector2<T>(x + v.x, y + v.y);
	}

	Vector2<T> operator - (const Vector2<T>& v) const
	{
		return Vector2<T>(x - v.x, y - v.y);
	}

	Vector2<T> operator * (const T& a) const
	{
		return Vector2<T>(x * a, y * a);
	}

	Vector2<T> operator / (const T& a) const
	{
		const T one_over_a = T(1) / a;
		return Vector2<T>(x * one_over_a, y * one_over_a);
	}

	Vector2<T> operator - () const
	{
		return Vector2<T>(-x, -y);
	}   
};

#endif // !VECTOR_2D_H