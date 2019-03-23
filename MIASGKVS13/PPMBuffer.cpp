#include "PPMBuffer.h"

PPMBuffer::PPMBuffer()
{

}

void PPMBuffer::saveToFile(std::string fileName, std::shared_ptr<ColorBuffer> colorBuffer)
{
    std::ofstream out(fileName);
    out << "P3\n" << colorBuffer->getWidth() << '\n' << colorBuffer->getHeight() << '\n' << "255\n";
    for(int y = 0; y < colorBuffer->getHeight(); y++)
    {
        for(int x = 0; x < colorBuffer->getWidth(); x++)
        {
            int color = colorBuffer->getPixel(x,y);
            int r = (color & 0xFF0000) >> 16;
            int g = (color & 0xFF00) >> 8;
            int b = (color & 0xFF);
            out << r;
            out << '\n';
            out << g;
            out << '\n';
            out << b;
            out << '\n';
        }
    }
    out.close();
}
