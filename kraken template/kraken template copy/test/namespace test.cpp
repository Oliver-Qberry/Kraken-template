

namespace kt {
    class drive {
        public:
        drive(int i) {}
    };
}

namespace kt {
    class sens{
        public:
        void func() {}
    };
}

namespace kt {
    int integer = 1;
}

void m() {
    kt::drive d(1);

    int i = kt::integer;


    using namespace kt;

    drive k(5);
}