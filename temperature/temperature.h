/*
Bria Weisblat
Section: 2
 */


class Temperature {
    public:
        Temperature(double degrees = 0, char scale = 'C');

        void Input();
        void Show() const;
        bool Set(double degrees, char scale);

        // Accessor Functions (Constant)
        double GetDegrees() const;
        char GetScale() const;

        // Functions that change things
        bool SetFormat(char format);
        bool Convert(char sc);

        // Const Function
        int Compare(const Temperature& d) const;

        // Increments by deg
        void Increment(int deg, char sc);


    private:
        char storedScale;
        double storedDegrees;
        char storedFormat;


        void makeValid(double degrees, char scale);     // converts a temperature to the default if it's invalid
        bool check(double degrees, char scale);         // check to see if a temperature is valid
        double makeCelsius (double degrees, char scale) const;      // convert a temperature to Celsius
};

