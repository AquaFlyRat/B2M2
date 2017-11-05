#pragma once

namespace b2m2 {
    class cColor {
    private:
        static const int OneOver255 = 1 / 255;
    public:

        float R, G, B, A;
    };
}