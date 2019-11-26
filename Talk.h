#pragma once

class Talk 
{
public:
	Talk();
	~Talk() = default;
	int main();
	void ini(int);
	void fin();
	int getflag() const { return flag; }

private:
	int fp;
	int flag, font;
	int char_pic, enemy_pic[4];
	int ishuman, face;
	char str[100];

	void draw();
};