#include "Transform.hpp"
#include <glm/gtx/transform.hpp>
using namespace arch;

mat4 cTransform::RotateAroundPoint(const vec3 & point, float angle) {
    return cMatrix4::Translate(point) * cMatrix4::RotateZ(angle) * cMatrix4::Translate(-point);
}

mat4 cTransform::FlipHorizontal(vec3 position, float spriteWidth) {
    cMatrix4 final =  cMatrix4::Translate(position) * cMatrix4::RotateY(180) * cMatrix4::Translate(-position);
    final = final * cMatrix4::Translate({ -spriteWidth, 0.f });
    return final;
}
