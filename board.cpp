#include "board.h"

Board::Board() {
    setupLayout();
}

Board::~Board() = default;

void Board::setupLayout() {
    std::string columns = "abcdefgh";
    glm::vec3 topRightCorner = glm::vec3(0.0735f, 0.0715f, -0.0025f);

    float x = topRightCorner.x;
    float y = topRightCorner.y;
    float z = topRightCorner.z;

    float step = 0.02f;

    for (int column = 0; column < 8; column++) {
        for (int row = 0; row < 8; row++) {
            layout[columns[column] + std::to_string(row + 1)] = glm::vec3(x, y, z);
            y -= step;
        }
        y = topRightCorner.y;
        x -= step;
    }
}

glm::vec3 Board::GetCoordinates(const std::string &position) {
    return layout[position];
}
