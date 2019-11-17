#pragma once

class AbstractBack
{
public:
    AbstractBack() = default;
    virtual ~AbstractBack() = default;
	virtual bool update() = 0;
	virtual void draw() const = 0;
};

