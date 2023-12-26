#pragma once

class Vec2
{
public:
    float data[2];

    union
    {
        struct
        {
            float x, y;
        };
        struct
        {
            float u, v;
        };
        struct
        {
            float r, g;
        };
        struct
        {
            float s, t;
        };
        struct
        {
            float width, height;
        };
        struct
        {
            float w, h;
        };
        struct
        {
            float min, max;
        };
        struct
        {
            float left, right;
        };
        struct
        {
            float bottom, top;
        };
    };

    Vec2(float value)
    {
        data[0] = value;
        data[1] = value;
    }

    Vec2(float x, float y)
    {
        data[0] = x;
        data[1] = y;
    }

    Vec2(const Vec<float, 2> &other)
    {
        for (int i = 0; i < 2; i++)
        {
            data[i] = other.data[i];
        }
    }

    Vec2(const Vec<float, 3> &other)
    {
        for (int i = 0; i < 2; i++)
        {
            data[i] = other.data[i];
        }
    }

    Vec2(const Vec<float, 4> &other)
    {
        for (int i = 0; i < 2; i++)
        {
            data[i] = other.data[i];
        }
    }

    Vec2(const Vec<float, 1> &other)
    {
        for (int i = 0; i < 2; i++)
        {
            data[i] = other.data[i];
        }
    }

    Vec2()
    {
        for (int i = 0; i < 2; i++)
        {
            data[i] = 0;
        }
    }

    float dot(const Vec<float, 2> &other) const
    {
        return x * other.x + y * other.y;
    }

    float length() const
    {
        return sqrt(dot(*this));
    }

    float length_squared() const
    {
        return dot(*this);
    }

    Vec<float, 2> normalize() const
    {
        return *this / length();
    }

    float &operator[](int index)
    {
        return data[index];
    }

    const float &operator[](int index) const
    {
        return data[index];
    }

    Vec<float, 2> operator+(const Vec<float, 2> &other) const
    {
        return Vec<float, 2>(x + other.x, y + other.y);
    }

    Vec<float, 2> operator+=(const Vec<float, 2> &other)
    {
        *this = *this + other;
        return *this;
    }

    Vec<float, 2> operator-(const Vec<float, 2> &other) const
    {
        return Vec<float, 2>(x - other.x, y - other.y);
    }

    Vec<float, 2> operator-=(const Vec<float, 2> &other)
    {
        *this = *this - other;
        return *this;
    }

    Vec<float, 2> operator*(const Vec<float, 2> &other) const
    {
        return Vec<float, 2>(x * other.x, y * other.y);
    }

    Vec<float, 2> operator*=(const Vec<float, 2> &other)
    {
        *this = *this * other;
        return *this;
    }

    Vec<float, 2> operator/(const Vec<float, 2> &other) const
    {
        return Vec<float, 2>(x / other.x, y / other.y);
    }

    Vec<float, 2> operator/=(const Vec<float, 2> &other)
    {
        *this = *this / other;
        return *this;
    }

    Vec<float, 2> operator+(float value) const
    {
        return Vec<float, 2>(x + value, y + value);
    }

    Vec<float, 2> operator+=(float value)
    {
        *this = *this + value;
        return *this;
    }

    Vec<float, 2> operator-(float value) const
    {
        return Vec<float, 2>(x - value, y - value);
    }

    Vec<float, 2> operator-=(float value)
    {
        *this = *this - value;
        return *this;
    }

    Vec<float, 2> operator*(float value) const
    {
        return Vec<float, 2>(x * value, y * value);
    }

    Vec<float, 2> operator*=(float value)
    {
        *this = *this * value;
        return *this;
    }

    Vec<float, 2> operator/(float value) const
    {
        return Vec<float, 2>(x / value, y / value);
    }

    Vec<float, 2> operator/=(float value)
    {
        *this = *this / value;
        return *this;
    }

    Vec<float, 2> operator-() const
    {
        return Vec<float, 2>(-x, -y);
    }

    bool operator==(const Vec<float, 2> &other) const
    {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Vec<float, 2> &other) const
    {
        return x != other.x || y != other.y;
    }
};