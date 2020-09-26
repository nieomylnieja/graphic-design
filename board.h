#ifndef GRAPHIC_DESIGN_BOARD_H
#define GRAPHIC_DESIGN_BOARD_H

#include <unordered_map>
#include <glm/glm.hpp>

class Board {
public:
    Board();
    ~Board();

    glm::vec3 GetCoordinates(const std::string &position);
private:
    // key is a position on the chessboard and the vector describes xyz coordinates of position
    std::unordered_map<std::string, glm::vec3> layout;

    void setupLayout();
};


#endif //GRAPHIC_DESIGN_BOARD_H
