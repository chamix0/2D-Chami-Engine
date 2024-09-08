#pragma once

/// \brief This class represents a vector of two dimensions
class Vec2
{
private:

public:
    //data  
    float x, y, z, a;

    //constructor
    Vec2();
    Vec2(float x);
    Vec2(float x, float y);
    Vec2(float R, float G, float B, float alpha = 1);


    //add sub
    Vec2 operator+(const Vec2& b) const;
    void operator+=(const Vec2& b);
    Vec2 operator-(const Vec2& b) const;
    void operator-=(const Vec2& b);

    //multiply divide
    Vec2 operator*(float val) const;
    Vec2 operator*(double val) const;
    Vec2 operator*(int val) const;
    Vec2 operator*(Vec2 val) const;
    void operator*=(float val);
    void operator*=(double val);
    void operator*=(int val);
    Vec2 operator*=(Vec2 val) const;

    
    Vec2 operator/(float val) const;
    Vec2 operator/(double val) const;
    Vec2 operator/(int val) const;
    void operator/=(float val);
    void operator/=(double val);
    void operator/=(int val);

    float R() const;
    float G() const;
    float B() const;
    float A() const;

    //equal
    bool operator==(const Vec2& b) const;

    /// \brief Dot product with other vector
    /// \param b 
    /// \return
    float Dot(const Vec2& b) const;

    /// \brief magnitude of the vector
    /// \return
    float Magnitude() const;

    /// \brief direction of the vector normalized
    /// \return
    Vec2 Normalized() const;

    /// \brief angle with other vector 
    /// \param other 
    /// \return 
    float angle(Vec2& other) const;

    /// \brief Distance between two points
    /// \param other 
    /// \return 
    float distance(const Vec2& other) const;

    static Vec2 DirectionByAngle(float angle);

    bool equals(Vec2 other= Vec2());
};
