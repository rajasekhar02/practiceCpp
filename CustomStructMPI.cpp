#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include <stddef.h>
#include <vector>
#include <set>
#include <iostream>
#include <cstring>
using namespace std;

typedef struct car_s
{
    int shifts;
    int topSpeed;
} car;

struct Position
{
    int row;
    int column;
    Position()
    {
        row = -1;
        column = -1;
    }
    Position(int row, int column)
    {
        this->row = row;
        this->column = column;
    }
    bool operator<(const Position &b) const
    {
        if (row - b.row != 0)
        {
            return row - b.row < 0;
        }
        return column - b.column < 0;
    }
};

enum Status
{
    INITIAL,
    VICTORY,
    FAILED,
    KILLED,
    ALIVE,
    ON_SNOW,
    STRUCT_BY_WALL
};

struct GameBoard
{
    Position currentPenguPosition;
    Status status;
    vector<int> path;
    set<Position> fishesCaughtWhileTraversing;
};
struct MPISerializeGameBoard
{
    int fishesCaughtWhileTraversingSize;
    int status;
    int *path;
    int pathLength;
    Position *fishesCaughtWhileTraversing;
    Position currentPenguPosition;
    void castToMPISerializeGameBoard(GameBoard gM)
    {
        this->fishesCaughtWhileTraversingSize = gM.fishesCaughtWhileTraversing.size();
        this->fishesCaughtWhileTraversing = new Position[this->fishesCaughtWhileTraversingSize];
        int i = 0;
        for (const Position p : gM.fishesCaughtWhileTraversing)
        {
            this->fishesCaughtWhileTraversing[i++] = p;
        }
        this->pathLength = gM.path.size();
        this->path = new int[this->pathLength];
        i = 0;
        for (const int direction : gM.path)
        {
            this->path[i++] = direction;
        }
        this->status = gM.status;
        this->currentPenguPosition = gM.currentPenguPosition;
    }
    GameBoard castToGameBoard()
    {
        GameBoard gM;
        int i = 0;
        for (i = 0; i < this->fishesCaughtWhileTraversingSize; i++)
        {
            gM.fishesCaughtWhileTraversing.insert(this->fishesCaughtWhileTraversing[i]);
        }
        i = 0;
        for (i = 0; i < pathLength; i++)
        {
            gM.path.push_back(this->path[i]);
        }
        gM.status = static_cast<Status>(this->status);
        gM.currentPenguPosition = this->currentPenguPosition;
        return gM;
    }
};
MPI_Datatype getMPIStructPosition()
{
    const int nitems = 2;
    int blocklengths[2] = {1, 1};
    MPI_Datatype types[2] = {MPI_INT, MPI_INT};
    MPI_Datatype mpi_position_type;
    MPI_Aint offsets[2];
    MPI_Type_create_struct(nitems, blocklengths, offsets, types, &mpi_position_type);
    MPI_Type_commit(&mpi_position_type);
    return mpi_position_type;
}

MPI_Datatype getMPIStructGameBoard(MPISerializeGameBoard gameBoard)
{
    MPI_Datatype fishesCaughtWhileTraversingMPI;
    MPI_Datatype position = getMPIStructPosition();
    int sizeOfFishesCaught = gameBoard.fishesCaughtWhileTraversingSize;
    MPI_Type_contiguous(sizeOfFishesCaught, position, &fishesCaughtWhileTraversingMPI);
    int counts[1] = {sizeOfFishesCaught};
    MPI_Datatype types[1] = {fishesCaughtWhileTraversingMPI};
    MPI_Datatype mpi_gameboard_type;
    MPI_Aint fishesAddress;
    MPI_Get_address(gameBoard.fishesCaughtWhileTraversing, &fishesAddress);
    cout << fishesAddress << endl;
    MPI_Aint displs[1] = {
        fishesAddress,
    };
    cout << MPI_Type_create_struct(1, counts, displs, types, &mpi_gameboard_type);
    MPI_Type_commit(&mpi_gameboard_type);
    return mpi_gameboard_type;
}

string castGameBoardToString(GameBoard gM)
{
    string st = "#0#";
    for (const Position p : gM.fishesCaughtWhileTraversing)
    {
        st += string("_") + to_string(p.row) + string("_") + to_string(p.column);
    }
    st += string("|#1#");
    for (const int direction : gM.path)
    {
        st += string("_") + to_string(direction);
    }
    st += string("|#2#_");
    st += to_string(gM.status);
    st += string("|#3#_");
    st += to_string(gM.currentPenguPosition.row) + string("_") + to_string(gM.currentPenguPosition.column);
    return st;
}
vector<string> split(string s, char c)
{
    vector<string> res;
    string tempStr = "";
    for (int index = 0; index < s.length(); index++)
    {
        if (s[index] != c)
        {
            tempStr += s[index];
        }
        else
        {
            res.push_back(tempStr);
            tempStr = "";
        }
    }
    res.push_back(tempStr);
    return res;
}
GameBoard castStringToGameBoard(string gameBoardString)
{
    GameBoard gm;
    vector<string> gMProperties = split(gameBoardString, '|');
    for (int i = 0; i < gMProperties.size(); i++)
    {
        vector<string> eachProperty = split(gMProperties[i], '_');
        switch ((eachProperty[0][1] - '0'))
        {
        case 0:
            for (int i = 1; i < eachProperty.size(); i += 2)
            {
                gm.fishesCaughtWhileTraversing.emplace(stoi(eachProperty[i]), stoi(eachProperty[i + 1]));
            }
            break;
        case 1:
            for (int i = 1; i < eachProperty.size(); i += 1)
            {
                gm.path.push_back(stoi(eachProperty[i]));
            }
            break;
        case 2:
            gm.status = static_cast<Status>(stoi(eachProperty[1]));
            break;
        case 3:
            gm.currentPenguPosition = {stoi(eachProperty[1]), stoi(eachProperty[2])};
            break;
        }
    }
    return gm;
}
int main(int argc, char **argv)
{

    const int tag = 13;
    int size, rank;
    int flag;
    MPI_Status status, probe_status;
    MPI_Request request;
    GameBoard gm;
    string gm1;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int line_size;
    char *gameBoardString;
    if (rank == 0)
    {
        const int dest = 1;
        int a[10] = {1, 2, 3, 4, 5, 6, 7, 81, 2, 4};
        gm.status = Status::KILLED;
        for (int i = 0; i < 10; i++)
        {
            gm.path.push_back(a[i]);
        }
        for (int i = 0; i < 10; i++)
        {
            gm.fishesCaughtWhileTraversing.emplace(a[i], i + 1);
        }
        gm1 = castGameBoardToString(gm);
        gameBoardString = &gm1[0];
        line_size = strlen(gameBoardString) + 1;
        // MPI_Send(&line_size, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
        cout << line_size << endl;
        MPI_Isend(gameBoardString, line_size, MPI_CHAR, dest, tag, MPI_COMM_WORLD, &request);
        cout << gameBoardString << endl;
    }
    if (rank == 1)
    {
        int message_pending;
        MPI_Iprobe(MPI_ANY_SOURCE, tag, MPI_COMM_WORLD, &message_pending, &status);
        if (message_pending)
        {
            MPI_Get_count(&status, MPI_CHAR, &line_size);
            cout << line_size << endl;
            // MPI_Recv(&line_size, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
            gameBoardString = (char *)malloc(line_size);
            MPI_Recv(gameBoardString, line_size, MPI_CHAR, 0, tag, MPI_COMM_WORLD, &status);
            gm1 = string(gameBoardString);
            gm = castStringToGameBoard(gm1);
            cout << castGameBoardToString(gm) << endl;
        }
    }

    return 0;
}