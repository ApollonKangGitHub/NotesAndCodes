#ifndef FURNITURE_H
#define FURNITURE_H


class Furniture
{
public:
    Furniture(float len, float wid, float wei);
    void discript();
protected:
    float _length;
    float _width;
    float _weight;
};

#endif // FURNITURE_H
