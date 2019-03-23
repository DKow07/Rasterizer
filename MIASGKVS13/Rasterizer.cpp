#include "Rasterizer.h"


Rasterizer::Rasterizer(std::shared_ptr<ColorBuffer> colorBuffer)
{
	this->colorBuffer = colorBuffer;
}

void Rasterizer::triangle(Float3 a, Float3 b, Float3 c, Float3 colorA, Float3 colorB, Float3 colorC)
{
	a.x = (a.x + 1) * this->colorBuffer->getWidth() * 0.5f;
	a.y = (a.y + 1) * this->colorBuffer->getHeight() * 0.5f;
	b.x = (b.x + 1) * this->colorBuffer->getWidth() * 0.5f;
	b.y = (b.y + 1) * this->colorBuffer->getHeight() * 0.5f;
	c.x = (c.x + 1) * this->colorBuffer->getWidth() * 0.5f;
	c.y = (c.y + 1) * this->colorBuffer->getHeight() * 0.5f;

	float minX = std::min(a.x, std::min(b.x, c.x));;
	float maxX = std::max(a.x, std::max(b.x, c.x));
	float minY = std::min(a.y, std::min(b.y, c.y));;
	float maxY = std::max(a.y, std::max(b.y, c.y));

	minX = std::max(minX, 0.0f);
	maxX = std::min(maxX, this->colorBuffer->getWidth() - 1.0f);
	minY = std::max(minY, 0.0f);
	maxY = std::min(maxY, this->colorBuffer->getHeight() - 1.0f);

	float diffX12 = a.x - b.x;
	float diffX23 = b.x - c.x;
	float diffX31 = c.x - a.x;
	float diffY12 = a.y - b.y;
	float diffY23 = b.y - c.y;
	float diffY31 = c.y - a.y;

	float lambda1Den = 1.0f / (diffY23*(-diffX31) + (diffX23)*(diffY31)); //TODO
	float lambda2Den = 1.0f / ((diffY31)*(diffX23)-(diffX31)*(diffY23));

	float lambda1 = 0;
	float lambda2 = 0;
	float lambda3 = 0;
	Float3 color(255.0f, 255.0f, 255.0f);

	bool tl1 = false;
	bool tl2 = false;
	bool tl3 = false;

	if (diffY12 < 0 || (diffY12 == 0 && diffX12 > 0))
	{
		tl1 = true;
	}
	if (diffY23 < 0 || (diffY23 == 0 && diffX23 > 0))
	{
		tl2 = true;
	}
	if (diffY31 < 0 || (diffY31 == 0 && diffX31 > 0))
	{
		tl3 = true;
	}

	for (int i = minX; i <= maxX; i++) //x
	{
		for (int j = minY; j <= maxY; j++) //y
		{
			if (((diffX12 * (j - a.y) - diffY12 * (i - a.x) > 0 && !tl1) || (diffX12 * (j - a.y) - diffY12 * (i - a.x) >= 0) && tl1)
				&& ((diffX23 * (j - b.y) - diffY23 * (i - b.x) > 0 && !tl2) || (diffX23 * (j - b.y) - diffY23 * (i - b.x) >= 0) && tl2)
				&& ((diffX31 * (j - c.y) - diffY31 * (i - c.x) > 0 && !tl3) || (diffX31 * (j - c.y) - diffY31 * (i - c.x) >= 0) && tl3))
			{
				lambda1 = ((diffY23)* (i - c.x) + (-diffX23) * (j - c.y)) * lambda1Den;
				lambda2 = ((diffY31)* (i - c.x) + (-diffX31) * (j - c.y)) * lambda2Den;
				lambda3 = 1.0f - lambda1 - lambda2;
				float depth = lambda1 * a.z + lambda2 * b.z + lambda3 * c.z;
				if (depth > colorBuffer->getDepth(i, j))
				{
					color = lambda1 * colorA + lambda2 * colorB + lambda3 * colorC;
					int rgbColor = color.x;
					rgbColor = (rgbColor << 8) + color.y;
					rgbColor = (rgbColor << 8) + color.z;
					this->colorBuffer->setPixel(i, j, rgbColor);
					this->colorBuffer->setDepth(i, j, depth);
				}
			}
		}
	}
}

void Rasterizer::trianglePixel(Float3 a, Float3 b, Float3 c, Float3 n1, Float3 n2, Float3 n3, std::vector<Light*> lights, VertexProcessor& vp, bool f1)
{
	Float3 aWithoutTr = Float3(a.x, a.y, a.z);
	Float3 bWithoutTr = Float3(b.x, b.y, b.z);
	Float3 cWithoutTr = Float3(c.x, c.y, c.z);

	a = vp.tr(a);
	b = vp.tr(b);
	c = vp.tr(c);
	
	a.x = (a.x + 1) * this->colorBuffer->getWidth() * 0.5f;
	a.y = (a.y + 1) * this->colorBuffer->getHeight() * 0.5f;
	b.x = (b.x + 1) * this->colorBuffer->getWidth() * 0.5f;
	b.y = (b.y + 1) * this->colorBuffer->getHeight() * 0.5f;
	c.x = (c.x + 1) * this->colorBuffer->getWidth() * 0.5f;
	c.y = (c.y + 1) * this->colorBuffer->getHeight() * 0.5f;

	float minX = std::min(a.x, std::min(b.x, c.x));;
	float maxX = std::max(a.x, std::max(b.x, c.x));
	float minY = std::min(a.y, std::min(b.y, c.y));;
	float maxY = std::max(a.y, std::max(b.y, c.y));

	minX = std::max(minX, 0.0f);
	maxX = std::min(maxX, this->colorBuffer->getWidth() - 1.0f);
	minY = std::max(minY, 0.0f);
	maxY = std::min(maxY, this->colorBuffer->getHeight() - 1.0f);

	float diffX12 = a.x - b.x;
	float diffX23 = b.x - c.x;
	float diffX31 = c.x - a.x;
	float diffY12 = a.y - b.y;
	float diffY23 = b.y - c.y;
	float diffY31 = c.y - a.y;

	float lambda1Den = 1.0f / (diffY23*(-diffX31) + (diffX23)*(diffY31)); //TODO
	float lambda2Den = 1.0f / ((diffY31)*(diffX23)-(diffX31)*(diffY23));

	float lambda1 = 0;
	float lambda2 = 0;
	float lambda3 = 0;
	//Float3 color(255.0f, 255.0f, 255.0f);

	bool tl1 = false;
	bool tl2 = false;
	bool tl3 = false;

	if (diffY12 < 0 || (diffY12 == 0 && diffX12 > 0))
	{
		tl1 = true;
	}
	if (diffY23 < 0 || (diffY23 == 0 && diffX23 > 0))
	{
		tl2 = true;
	}
	if (diffY31 < 0 || (diffY31 == 0 && diffX31 > 0))
	{
		tl3 = true;
	}

	for (int i = minX; i <= maxX; i++) //x
	{
		for (int j = minY; j <= maxY; j++) //y
		{
			Float3 color = Float3();
			if (((diffX12 * (j - a.y) - diffY12 * (i - a.x) > 0 && !tl1) || (diffX12 * (j - a.y) - diffY12 * (i - a.x) >= 0) && tl1)
				&& ((diffX23 * (j - b.y) - diffY23 * (i - b.x) > 0 && !tl2) || (diffX23 * (j - b.y) - diffY23 * (i - b.x) >= 0) && tl2)
				&& ((diffX31 * (j - c.y) - diffY31 * (i - c.x) > 0 && !tl3) || (diffX31 * (j - c.y) - diffY31 * (i - c.x) >= 0) && tl3))
			{

				lambda1 = ((diffY23)* (i - c.x) + (-diffX23) * (j - c.y)) * lambda1Den;
				lambda2 = ((diffY31)* (i - c.x) + (-diffX31) * (j - c.y)) * lambda2Den;
				lambda3 = 1.0f - lambda1 - lambda2;
				float depth = lambda1 * a.z + lambda2 * b.z + lambda3 * c.z;


				Float3 vB = lambda1 * aWithoutTr + lambda2 * bWithoutTr + lambda3 * cWithoutTr;
				Float3 normalB = lambda1 * n1 + lambda2 * n2 + lambda3 * n3;
				Vertex bar = Vertex(vB, normalB);

				for (auto light : lights)
				{
					color = color + light->calculate(bar, vp, f1);
				}
				color = color.Saturate();
				if (depth > colorBuffer->getDepth(i, j))
				{
					int rgbColor = color.x;
					rgbColor = (rgbColor << 8) + color.y;
					rgbColor = (rgbColor << 8) + color.z;
					this->colorBuffer->setPixel(i, j, rgbColor);
					this->colorBuffer->setDepth(i, j, depth);
				}
			}
		}
	}
}

Rasterizer::~Rasterizer()
{
}
