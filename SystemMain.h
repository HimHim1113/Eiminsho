#pragma once

class SystemMain final
{
public:
	SystemMain() : end_count(0) {};
	~SystemMain() = default;
	bool initialize() const;
	void finalize() const;
	void main() const;
private:
	int end_count;
};

