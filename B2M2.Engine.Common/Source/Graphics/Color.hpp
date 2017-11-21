#pragma once

namespace arch {
    class cColor {
    private:
        static const int OneOver255 = 1 / 255;
    public:

        float R, G, B, A;
    };
}