class KT {
    public:

    void func();

    class subc {
        void subc_func();
    };

    class chas {
        public:
        chas(int i) {}

        void chas_func();
    };

    class inn{
        public:
        inn() {}

    };

    class out{
        public:
        out(inn i) {}
    };
};