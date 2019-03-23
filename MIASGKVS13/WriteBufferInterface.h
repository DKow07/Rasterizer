#pragma once
#include <string>
#include <memory>
#include "ColorBuffer.h"

class WriteBufferInterface
{
public:
    virtual void saveToFile(std::string fileName, std::shared_ptr<ColorBuffer> colorBuffer) = 0;
};
