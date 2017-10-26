#include "Transform.hpp"
#include <glm/gtx/transform.hpp>
using namespace b2m2;

mat4 cTransform::RotateAroundPoint(const vec3 & point, float angle)
{
    return glm::translate(point) * glm::rotate(glm::radians(angle), glm::vec3(0, 0, 1)) * glm::translate(-point);
}

mat4 cTransform::FlipHorizontal(vec3 position, float spriteWidth)
{
    mat4 flip = glm::translate(position) * glm::rotate(glm::radians(180.f), vec3(0, 1, 0)) * glm::translate(-position);
    flip *= glm::translate(vec3(-spriteWidth, 0.f, 0.f));
    return flip;
}
