#include "chessboard.h"
#include "paths.h"

Chessboard::Chessboard(ShaderProgram &shaderProgram) : m_Chessboard(Model(ChessObjectsPath("board"))) {
    setupLayout();
    setupInitialPiecesPositions(shaderProgram);
}

Chessboard::~Chessboard() = default;

glm::vec3 Chessboard::GetCoordinates(const std::string &position) {
    return m_Layout[position];
}

void Chessboard::Draw(ShaderProgram &shaderProgram) {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
    shaderProgram.SetUniform("model", model);
    m_Chessboard.Draw(shaderProgram);

    for (auto const &kv : m_Pieces) {
        model = glm::mat4(1.0f);
        model = glm::translate(model, kv.second.pos);
        shaderProgram.SetUniform("model", model);
        kv.second.model->Draw(shaderProgram);
    }
}

void Chessboard::setupLayout() {
    std::string columns = "abcdefgh";
    glm::vec3 topRightCorner = glm::vec3(0.0735f, 0.0715f, -0.0001f);

    float x = topRightCorner.x;
    float y = topRightCorner.y;
    float z = topRightCorner.z;

    float step = 0.02f;

    for (int column = 0; column < 8; column++) {
        for (int row = 0; row < 8; row++) {
            if ((row % 2 != 0 && column % 2 == 0) || (row % 2 == 0 && column % 2 != 0)) {
                m_Layout[columns[column] + std::to_string(row + 1)] = glm::vec3(x, y, -0.0025f);
            } else {
                m_Layout[columns[column] + std::to_string(row + 1)] = glm::vec3(x, y, z);
            }
            y -= step;
        }
        y = topRightCorner.y;
        x -= step;
    }
}

// TODO Load each model only once per color
void Chessboard::setupInitialPiecesPositions(ShaderProgram &shaderProgram) {
    std::string whitePieces[] = {"rook", "knight", "bishop", "king", "queen", "bishop", "knight", "rook"};
    std::string blackPieces[] = {"rook", "knight", "bishop", "queen", "king", "bishop", "knight", "rook"};

    shaderProgram.Use();

    std::string columns = "abcdefgh";

    auto *whitePawn = new Model(ChessObjectsPath("white/pawn"));
    auto *blackPawn = new Model(ChessObjectsPath("black/pawn"));

    for (int column = 0; column < 8; column++) {
        m_Pieces[columns[column] + std::to_string(2)] = {whitePawn, m_Layout[columns[column] + std::to_string(2)], false};
        m_Pieces[columns[column] + std::to_string(7)] = {blackPawn, m_Layout[columns[column] + std::to_string(7)], false};

        m_Pieces[columns[column] + std::to_string(1)] = {new Model(
                ChessObjectsPath("white/" + whitePieces[column])), m_Layout[columns[column] + std::to_string(1)], false};
        m_Pieces[columns[column] + std::to_string(8)] = {new Model(
                ChessObjectsPath("black/" + blackPieces[column])), m_Layout[columns[column] + std::to_string(8)], false};
    }
}

void Chessboard::move(const std::string &from, const std::string &to) {
    if (m_Pieces.find(to) != m_Pieces.end()) {
        m_Pieces.erase(from);
    }
    m_Pieces[from].pos = m_Layout[to];
}
