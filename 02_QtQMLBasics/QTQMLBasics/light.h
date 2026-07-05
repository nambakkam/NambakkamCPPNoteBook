#ifndef LIGHT_H
#define LIGHT_H

#include "ismartdevice.h"

class Light : public ISmartDevice
{
    Q_OBJECT
public:
    explicit Light(QObject *parent = nullptr);
};

#endif // LIGHT_H
