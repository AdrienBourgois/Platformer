#include <cmath>
#include <algorithm>
#include <iostream>
#include <iomanip>

#include "maths/utility.h"
#include "maths/matrix.h"

namespace id {
namespace maths {

Matrix4x4 const Matrix4x4::identity =
Matrix4x4({
    1.f, 0.f, 0.f, 0.f,
    0.f, 1.f, 0.f, 0.f,
    0.f, 0.f, 1.f, 0.f,
    0.f, 0.f, 0.f, 1.f
});

auto Matrix4x4::perspective(float fovy, float aspect, float near, float far) -> Matrix4x4
{
    float fovy_rad = degToRad(fovy);

    float f = 1.f / ( tan( ( fovy_rad / 2.f )) );
    return Matrix4x4({
        (f / aspect), 0.f, 0.f, 0.f,
        0.f, f, 0.f, 0.f,
        0.f, 0.f, ((far+near)/(near-far)), ((2.f*near*far)/(near-far)),
        0.f, 0.f, -1.f, 0.f
    });
}

auto Matrix4x4::translate(float x, float y, float z) -> Matrix4x4
{
    return Matrix4x4({
        1.f, 0.f, 0.f, x,
        0.f, 1.f, 0.f, y,
        0.f, 0.f, 1.f, z,
        0.f, 0.f, 0.f, 1.f
    });
}
auto Matrix4x4::scale(float x, float y, float z) -> Matrix4x4
{
    return Matrix4x4({
        x, 0.f, 0.f, 0.f,
        0.f, y, 0.f, 0.f,
        0.f, 0.f, z, 0.f,
        0.f, 0.f, 0.f, 1.f
    });
}
auto Matrix4x4::scale(float s) -> Matrix4x4
{
    return Matrix4x4({
        s, 0.f, 0.f, 0.f,
        0.f, s, 0.f, 0.f,
        0.f, 0.f, s, 0.f,
        0.f, 0.f, 0.f, 1.f
    });
}
auto Matrix4x4::rotateX(float angle) -> Matrix4x4
{
    float angle_rad = degToRad(angle);
    return Matrix4x4({
        1.f, 0.f, 0.f, 0.f,
        0.f, std::cos(angle_rad), -std::sin(angle_rad), 0.f,
        0.f, std::sin(angle_rad), std::cos(angle_rad), 0.f,
        0.f, 0.f, 0.f, 1.f
    });
}
auto Matrix4x4::rotateY(float angle) -> Matrix4x4
{
    float angle_rad = degToRad(angle);
    return Matrix4x4({
        std::cos(angle_rad), 0.f, std::sin(angle_rad), 0.f,
        0.f, 1.f, 0.f, 0.f,
        -std::sin(angle_rad), 0.f, std::cos(angle_rad), 0.f,
        0.f, 0.f, 0.f, 1.f
    });
}
auto Matrix4x4::rotateZ(float angle) -> Matrix4x4
{
    float angle_rad = degToRad(angle);
    return Matrix4x4({
        std::cos(angle_rad), -std::sin(angle_rad), 0.f, 0.f,
        std::sin(angle_rad), std::cos(angle_rad), 0.f, 0.f,
        0.f, 0.f, 1.f, 0.f,
        0.f, 0.f, 0.f, 1.f
    });
}

auto Matrix4x4::operator*(Matrix4x4 const& mat) const -> Matrix4x4
{
    Matrix4x4 res = Matrix4x4({0.f,0.f,0.f,0.f, 0.f,0.f,0.f,0.f, 0.f,0.f,0.f,0.f, 0.f,0.f,0.f,0.f});
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            for (int k = 0; k < 4; ++k)
            {
                res.val[(4 * i) + j] += this->val[(4 * i) + k] * mat.val[(4 * k) + j];
            }
        }
    }
    return res;
}
auto Matrix4x4::operator*=(Matrix4x4 const& mat) -> Matrix4x4&
{
    *this = *this * mat;
    return *this;
}

auto Matrix4x4::getMatrixRotation() -> Matrix3x3
{
    return {
        this->val[0], this->val[1], this->val[2],
        this->val[4], this->val[5], this->val[6],
        this->val[8], this->val[9], this->val[10],
    };
}
auto Matrix4x4::getMatrixTranslation() -> Matrix3x1
{
    return {
        this->val[3],
        this->val[7],
        this->val[11]
    };
}

auto Matrix4x4::getInverse() const -> Matrix4x4
{
    Matrix4x4 res = *this;
    
    std::swap(res.val[1], res.val[4]);
    std::swap(res.val[2], res.val[8]);
    std::swap(res.val[6], res.val[9]);
    
    Matrix3x1 trans = -res.getMatrixRotation() * res.getMatrixTranslation();
    
    res.val[3] = trans.val[0];
    res.val[7] = trans.val[1];
    res.val[11] = trans.val[2];
    
    return res;
}

void Matrix4x4::setPosition(Vector3 vec)
{
    this->val[3] = vec.val[0];
    this->val[7] = vec.val[1];
    this->val[11]= vec.val[2];
    
    //*this *= translate(vec.val[0],vec.val[1],vec.val[2]);
}
void Matrix4x4::setRotation(Vector3 rot)
{
    this->val[0] = this->val[5] = this->val[10] = 1;
    this->val[1] = this->val[2] = this->val[4] = this->val[6] = this->val[8] = this->val[9] = 0;
    *this *= rotateX(rot.val[0]) * rotateY(rot.val[1]) * rotateZ(rot.val[2]);
    _rotation = rot;
}
auto Matrix4x4::getPosition() const -> Vector3
{
    return {this->val[3], this->val[7], this->val[11]};
}
auto Matrix4x4::getRotation() const -> Vector3
{
    return _rotation;
}
void Matrix4x4::print() const
{
    std::cout<<" / "<<this->val[0]<<" "<<this->val[1]<<" "<<this->val[2]<<" "<<this->val[3]<<" \\ "<<std::endl;
    std::cout<<" | "<<this->val[4]<<" "<<this->val[5]<<" "<<this->val[6]<<" "<<this->val[7]<<" | "<<std::endl;
    std::cout<<" | "<<this->val[8]<<" "<<this->val[9]<<" "<<this->val[10]<<" "<<this->val[11]<<" | "<<std::endl;
    std::cout<<" \\ "<<this->val[12]<<" "<<this->val[13]<<" "<<this->val[14]<<" "<<this->val[15]<<" / "<<std::endl;
}

auto Matrix4x4::Forward() -> Vector3
{
    return {-this->val[2], -this->val[6], -this->val[10]};
}

Matrix3x3 const Matrix3x3::identity =
{
    1.f, 0.f, 0.f,
    0.f, 1.f, 0.f,
    0.f, 0.f, 1.f,
};

    
auto Matrix3x3::operator*(Matrix3x3 const& mat) const -> Matrix3x3
{
    Matrix3x3 res = {0.f,0.f,0.f, 0.f,0.f,0.f, 0.f,0.f,0.f,};
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            for (int k = 0; k < 3; ++k)
            {
                res.val[(3 * i) + j] += this->val[(3 * i) + k] * mat.val[(3 * k) + j];
            }
        }
    }
    return res;

}

auto Matrix3x3::operator*(Matrix3x1 const& mat) const -> Matrix3x1
{
    return {
        this->val[0] * mat.val[0] + this->val[1] * mat.val[1] + this->val[2] * mat.val[2],
        this->val[3] * mat.val[0] + this->val[4] * mat.val[1] + this->val[5] * mat.val[2],
        this->val[6] * mat.val[0] + this->val[7] * mat.val[1] + this->val[8] * mat.val[2]
    };
}

auto Matrix3x3::operator*=(Matrix3x3 const& mat) -> Matrix3x3&
{
    *this = *this * mat;
    return *this;
}
auto Matrix3x3::operator-() const -> Matrix3x3
{
    return {
        -this->val[0], -this->val[1], -this->val[2],
        -this->val[3], -this->val[4], -this->val[5],
        -this->val[6], -this->val[7], -this->val[8]
    };
}
void Matrix3x3::print() const
{
    std::cout<<" / "<<this->val[0]<<" "<<this->val[1]<<" "<<this->val[2]<<" \\ "<<std::endl;
    std::cout<<" | "<<this->val[3]<<" "<<this->val[4]<<" "<<this->val[5]<<" | "<<std::endl;
    std::cout<<" \\ "<<this->val[6]<<" "<<this->val[7]<<" "<<this->val[8]<<" / "<<std::endl;
}

void Matrix3x1::print() const
{
    std::cout<<" { "<<this->val[0]<<" "<<this->val[1]<<" "<<this->val[2]<<" } "<<std::endl;
}

} // namespace maths
} // namespace id
