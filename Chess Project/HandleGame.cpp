#include "HandleGame.h"
#include "Rook.h"
#include "Pawn.h"
#include "Queen.h"
#include "King.h"
#include "Bishop.h"
#include "Knight.h"
#include "Piece.h"
#include "Server.h"

const std::string castleCodes[4] = { "e1g1", "e1c1", "e8g8", "e8c8" };
bool HandleGame::_currentPlayer;

bool HandleGame::getCurrentPlayer()
{
    return _currentPlayer;
}

void HandleGame::setCurrentPlayer(int color)
{
    HandleGame::_currentPlayer = color;
}

// image recognition -> logic -> AI -> logic -> ESP
// recv(IMG) -> send(AI) -> recv(AI) -> send(ESP)
void HandleGame::startGame(Board* board, SOCKET* imageSocket, SOCKET* AISocket, SOCKET* ESPSocket)
{
    int roundCounter = 0;
    int code = 0;
    char strCode[2] = { 0 };
    std::string msgToGraphics = INIT_STR;
    const char* pStr = msgToGraphics.c_str();
    std::string msgFromGraphics = "";
    std::string moveFromAI = "";

    HandleGame::setCurrentPlayer(WHITE);
    board->printBoard();

    while (msgFromGraphics != "quit")
    {
        msgFromGraphics = Server::recvMsg(*imageSocket);
        code = HandleGame::handleTurn(msgFromGraphics, *board);

        strCode[0] = code + '0';
        strCode[1] = '\0';

        msgToGraphics = strCode;
        pStr = msgToGraphics.c_str();
        Server::sendMsg(*imageSocket, msgToGraphics);
        if (code == VALID || code == CHECK || code == CASTLE || code == CHECKMATE) {
            HandleGame::changeCurrentPlayer(code, &roundCounter);
            Server::sendMsg(*AISocket, board->getBoardStr(getCurrentPlayer()));  // SEND AI NEW BOARD POSITION
            moveFromAI = Server::recvMsg(*AISocket);  // RECV MOVE FROM AI
            HandleGame::handleTurn(msgFromGraphics, *board);  // UPDATE BOARD
            HandleGame::changeCurrentPlayer(code, &roundCounter);
            Server::sendMsg(*ESPSocket, moveFromAI);  // SEND MOVE TO ESP
        }
    }
}

int HandleGame::handleTurn(std::string instruction, Board& board)
{
    int* src = board.convertIndex(instruction.substr(0, 2));
    int* dest = board.convertIndex(instruction.substr(2, 2));
    char srcChar = board.getBoard()[src[0]][src[1]]->getType();
    char destChar = board.getBoard()[dest[0]][dest[1]]->getType();
    const std::string* str = std::find(std::begin(castleCodes), std::end(castleCodes), instruction);
    int code = 0;

    if (tolower(srcChar) == B_KING && str != std::end(castleCodes))
    {
        code = board.castle(src, dest);
    }
    else
    {
        code = board.getBoard()[src[0]][src[1]]->isValidMove(src, dest, board);
    }

    if (code == VALID || code == CHECK || code == CASTLE)
    {
        board.getBoard()[src[0]][src[1]]->setHasMoved(true);
        board.movePiece(src, dest, true);

        if (srcChar == B_PAWN || srcChar == W_PAWN)
        {
            if (dest[0] == 7 || dest[0] == 0)
            {
                delete board.getBoard()[dest[0]][dest[1]];
                board.getBoard()[dest[0]][dest[1]] = (dest[0] == 7) ? new Queen(B_QUEEN) : new Queen(W_QUEEN);
            }
        }

        if (code == CHECK)
        {
            code = board.isInMate(!HandleGame::_currentPlayer);
        }
    }
    board.printBoard();

    delete[] src;
    delete[] dest;
    return code;
}

void HandleGame::changeCurrentPlayer(const int code, int* roundCounter)
{
    if (code == VALID || code == CHECK || code == CASTLE)
    {
        (*roundCounter)++;
    }
    if ((*roundCounter) % 2 == 0 && (code == VALID || code == CHECK || code == CASTLE))
    {
        HandleGame::setCurrentPlayer(WHITE);
    }
    else if (code == VALID || code == CHECK || code == CASTLE)
    {
        HandleGame::setCurrentPlayer(BLACK);
    }
}
/*
std::string HandleGame::receiveMsg(SOCKET sock, int len, int offset)
{
    if (len == 0)
    {
        return (char*)"";
    }

    char* data = new char[len + 1];
    int res = recv(sock, data, len, 0);

    if (res == INVALID_SOCKET)
    {
        std::string s = "Error while recieving from socket: ";
        s += std::to_string(sock);
        throw std::exception(s.c_str());
    }

    data[len] = 0;
    return data;
}

void HandleGame::sendMsg(SOCKET sock, const char** buffer, int len)
{
    if (send(sock, *buffer, len, 0) == INVALID_SOCKET)
    {
        throw std::exception("Error while sending message to client");
    }
}
*/