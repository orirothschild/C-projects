#ifndef ILRD_SPRINKLER_HPP
#define ILRD_SPRINKLER_HPP



namespace ilrd {

class Sprinkler
{
public:
    explicit Sprinkler() = default;
    ~Sprinkler() = default;

    void DispatcherSmokeFunction(bool isSmokey);

private:
    void TurnOn();
    //void TurnOff();
};

} // ilrd

#endif //ILRD_SPRINKLER_HPP
