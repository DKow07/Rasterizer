#pragma once

#include "WriteBufferInterface.h"
#include <fstream>

class PPMBuffer : public WriteBufferInterface
{
public:
    PPMBuffer();
    void saveToFile(std::string fileName, std::shared_ptr<ColorBuffer> colorBuffer) override;
};
