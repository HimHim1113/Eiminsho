#pragma once


class Board final
{
public:
    Board();
    ~Board() = default;
    bool main(int, int, int, int);
    void draw(int, int, int, int) const;

private:
	int img_board[30];
    void drawFrame() const;
	int font;
};
