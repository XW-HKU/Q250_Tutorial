#ifndef  GENE_MATH_H
#define  GENE_MATH_H

#include <Eigen/Dense>
using namespace Eigen;

typedef float v3_t[3];
typedef float q_t[4];

struct vector_xyz_64t
{
    double x;
    double y;
    double z;
};

struct vector_wxyz_64t
{
    double w;
    double x;
    double y;
    double z;
};

// void gene_math_copy_wxyz_array_to_xyzw_quatf(const q_t q_in, Quaternionf q_out);

#endif