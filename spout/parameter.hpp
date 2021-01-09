namespace Game
{
    class Parameter
    {
    private:
        float _value = 0.0; // The current value

        float min = 0.0;
        float center = 0.5;
        float max = 1.0;

        // The probability window of change.
        float probChgMin = 0.2;
        float probChgMax = 0.3;

        // How many times the change is applied
        int chgCnt = 0;
        int cnt = 0;

    public:
        Parameter() = default;
        Parameter(float min, float max, float probChgMin, float probChgMax);

        void adjust();
        float update();

        float value();
        int iValue();
    };

} // namespace Game