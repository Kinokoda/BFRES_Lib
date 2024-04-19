//
// Created by kino on 4/16/24.
//

#ifndef BFRES_LIB_USEFULSTRUCTS_H
#define BFRES_LIB_USEFULSTRUCTS_H
namespace util {
    template <typename T>
    struct Vector2 {
        T x;
        T y;
    };
    using Vector2f = Vector2<float>;
    template <typename T>
    struct Vector3 {
        T x;
        T y;
        T z;
    };
    using Vector3f = Vector3<float>;


    template <typename T>
    struct Vector4 {
        T x;
        T y;
        T z;
        T w;
    };
    using Vector4f = Vector4<float>;


    struct Matrix34f {
        float m11;
        float m12;
        float m13;
        float m14;
        float m21;
        float m22;
        float m23;
        float m24;
        float m31;
        float m32;
        float m33;
        float m34;
    };

}
#endif //BFRES_LIB_USEFULSTRUCTS_H

