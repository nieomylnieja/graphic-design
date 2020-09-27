#ifndef GRAPHIC_DESIGN_CHESSBOARD_H
#define GRAPHIC_DESIGN_CHESSBOARD_H

#include <unordered_map>
#include <glm/glm.hpp>
#include "shader_program.h"
#include "model.h"

struct Piece {
    Model *model;
    glm::vec3 pos;
    bool isMoving;
};

class Chessboard {
public:
    explicit Chessboard(ShaderProgram &shaderProgram);
    ~Chessboard();

    void Draw(ShaderProgram &shaderProgram);

    // very naive teleportation, this will just change the pawn position instantly and remove any existing pawn in place
    void move(const std::string &from, const std::string &to);

    glm::vec3 GetCoordinates(const std::string &position);
private:
    // key is a position on the chessboard and the vector describes xyz coordinates of position
    std::unordered_map<std::string, glm::vec3> m_Layout;

    std::unordered_map<std::string, Piece> m_Pieces;
    Model m_Chessboard;

    void setupLayout();
    void setupInitialPiecesPositions(ShaderProgram &shaderProgram);
};

#endif //GRAPHIC_DESIGN_CHESSBOARD_H
