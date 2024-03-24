#include "Vector3.h"

const YAM::Vector3 YAM::Vector3::Up {0., 1., 0.}; 
const YAM::Vector3 YAM::Vector3::Forward {0., 0., -1.}; 
const YAM::Vector3 YAM::Vector3::Right {1., 0., 0.}; 
const YAM::Vector3 YAM::Vector3::Zero {0., 0., 0.}; 

YAM::Vector3::Vector3(const Vector4& vec4)
    : x(vec4.x)
      , y(vec4.y)
      , z(vec4.z) {}
