#include <sstream>

class Orto {
    public:
        Orto() = default;
        ~Orto() = default;

        Orto Scale(Orto lhs, Orto rhs);
        Orto Intersect(Orto lhs, Orto rhs, Orto in_new) {
             if((lhs.l_up > rhs.l_up) && (rhs.l_down > lhs.l_down)) {
                in_new.l_down = rhs.l_down - lhs.l_up; 
                in_new.l_up = lhs.l_up;
                in_new.r_up = rhs.r_up;
                in_new.r_down = rhs.r_down;
             }

        }
        Orto Union(Orto lhs, Orto rhs);

    private:
         int l_up = 0;
         int l_down = 0;
         int r_up = 0;
         int r_down = 0;

};
