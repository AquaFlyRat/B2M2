#include "Transform.hpp"
#include <glm/gtx/transform.hpp>
using namespace b2m2;

mat4 cTransform::RotateAroundPoint(const vec3 & point, float angle)
{
    return glm::translate(point) * glm::rotate(glm::radians(angle), glm::vec3(0, 0, 1)) * glm::translate(-point);
}
