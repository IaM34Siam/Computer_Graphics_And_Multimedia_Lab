
#include "glad.h"
#include "glfw3.h"

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const float PI = 3.1416;

// Game state: every cell starts empty
char board[3][3] = {
    {' ', ' ', ' '},
    {' ', ' ', ' '},
    {' ', ' ', ' '}
};

double moveTime[3][3] = {};

char currentPlayer = 'X';
char winner = ' ';
bool gameOver = false;
bool isDraw = false;

double winTime = 0.0;
float winLine[4] = {};

unsigned int VAO, VBO, shaderProgram;
int colorLocation;

// Vertex shader
const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec2 aPos;

void main()
{
    gl_Position = vec4(aPos, 0.0, 1.0);
}
)";

// Fragment shader
const char* fragmentShaderSource = R"(
#version 330 core
uniform vec3 objectColor;
out vec4 FragColor;

void main()
{
    FragColor = vec4(objectColor, 1.0);
}
)";

// Compile shader
unsigned int compileShader(unsigned int type, const char* source)
{
    unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        char info[512];
        glGetShaderInfoLog(shader, 512, NULL, info);
        std::cout << "Shader compilation error:\n" << info << '\n';
    }

    return shader;
}

// Create shader program
void createShaderProgram()
{
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vs);
    glAttachShader(shaderProgram, fs);
    glLinkProgram(shaderProgram);

    int success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

    if (!success)
    {
        char info[512];
        glGetProgramInfoLog(shaderProgram, 512, NULL, info);
        std::cout << "Shader linking error:\n" << info << '\n';
    }

    glDeleteShader(vs);
    glDeleteShader(fs);

    colorLocation = glGetUniformLocation(shaderProgram, "objectColor");
}

// Draw line segments
void drawLines(const std::vector<float>& vertices,
               float r, float g, float b)
{
    if (vertices.empty())
        return;

    glUniform3f(colorLocation, r, g, b);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(
        GL_ARRAY_BUFFER,
        vertices.size() * sizeof(float),
        vertices.data(),
        GL_DYNAMIC_DRAW
    );

    glDrawArrays(
        GL_LINES, 0,
        static_cast<GLsizei>(vertices.size() / 2)
    );
}

// Add a line that can be drawn progressively
void addLine(std::vector<float>& v,
             float x1, float y1,
             float x2, float y2,
             float progress)
{
    progress = std::clamp(progress, 0.0f, 1.0f);

    if (progress <= 0.0f)
        return;

    v.insert(v.end(), {
        x1, y1,
        x1 + (x2 - x1) * progress,
        y1 + (y2 - y1) * progress
    });
}

// Draw the 3x3 board
void drawBoard()
{
    std::vector<float> vertices = {
        -0.2f,  0.6f, -0.2f, -0.6f,
         0.2f,  0.6f,  0.2f, -0.6f,
        -0.6f,  0.2f,  0.6f,  0.2f,
        -0.6f, -0.2f,  0.6f, -0.2f
    };

    drawLines(vertices, 0.0f, 0.85f, 1.0f);
}

float cellX(int col)
{
    return -0.4f + col * 0.4f;
}

float cellY(int row)
{
    return 0.4f - row * 0.4f;
}

// Draw animated X
void drawX(int row, int col, float progress)
{
    float x = cellX(col);
    float y = cellY(row);
    float size = 0.13f;

    std::vector<float> vertices;

    addLine(vertices,
        x - size, y - size,
        x + size, y + size, progress);

    addLine(vertices,
        x - size, y + size,
        x + size, y - size, progress);

    drawLines(vertices, 1.0f, 0.25f, 0.55f);
}

// Draw animated O
void drawO(int row, int col, float progress)
{
    float x = cellX(col);
    float y = cellY(row);
    float radius = 0.13f;

    const int segments = 60;
    int count = static_cast<int>(segments * progress);

    std::vector<float> vertices;

    for (int i = 0; i < count; i++)
    {
        float a1 = 2.0f * PI * i / segments;
        float a2 = 2.0f * PI * (i + 1) / segments;

        vertices.insert(vertices.end(), {
            x + radius * std::cos(a1),
            y + radius * std::sin(a1),
            x + radius * std::cos(a2),
            y + radius * std::sin(a2)
        });
    }

    drawLines(vertices, 0.25f, 1.0f, 0.4f);
}

// Check a possible winning line
bool checkLine(int r1, int c1,
               int r2, int c2,
               int r3, int c3)
{
    char symbol = board[r1][c1];

    if (symbol != ' ' &&
        symbol == board[r2][c2] &&
        symbol == board[r3][c3])
    {
        winner = symbol;

        winLine[0] = cellX(c1);
        winLine[1] = cellY(r1);
        winLine[2] = cellX(c3);
        winLine[3] = cellY(r3);

        return true;
    }

    return false;
}

// Check rows, columns, and diagonals
bool checkWinner()
{
    for (int i = 0; i < 3; i++)
    {
        if (checkLine(i, 0, i, 1, i, 2) ||
            checkLine(0, i, 1, i, 2, i))
            return true;
    }

    return checkLine(0, 0, 1, 1, 2, 2) ||
           checkLine(0, 2, 1, 1, 2, 0);
}

// Check for a draw
bool checkDraw()
{
    for (int r = 0; r < 3; r++)
    {
        for (int c = 0; c < 3; c++)
        {
            if (board[r][c] == ' ')
                return false;
        }
    }

    return true;
}

// Restart the game
void resetGame()
{
    for (int r = 0; r < 3; r++)
    {
        for (int c = 0; c < 3; c++)
        {
            board[r][c] = ' ';
            moveTime[r][c] = 0.0;
        }
    }

    currentPlayer = 'X';
    winner = ' ';
    gameOver = false;
    isDraw = false;
    winTime = 0.0;
    std::fill(winLine, winLine + 4, 0.0f);
}

// Handle mouse clicks
void mouseButtonCallback(GLFWwindow* window,
                         int button, int action, int)
{
    if (button != GLFW_MOUSE_BUTTON_LEFT ||
        action != GLFW_PRESS || gameOver)
        return;

    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);

    int width, height;
    glfwGetWindowSize(window, &width, &height);

    if (width <= 0 || height <= 0)
        return;

    float x = static_cast<float>(2.0 * mouseX / width - 1.0);
    float y = static_cast<float>(1.0 - 2.0 * mouseY / height);

    if (x < -0.6f || x > 0.6f ||
        y < -0.6f || y > 0.6f)
        return;

    int col = std::min(2, static_cast<int>((x + 0.6f) / 0.4f));
    int row = std::min(2, static_cast<int>((0.6f - y) / 0.4f));

    if (board[row][col] != ' ')
        return;

    board[row][col] = currentPlayer;
    moveTime[row][col] = glfwGetTime();

    if (checkWinner())
    {
        gameOver = true;
        winTime = glfwGetTime();
    }
    else if (checkDraw())
    {
        gameOver = true;
        isDraw = true;
    }
    else
    {
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }
}

// Keyboard controls
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    static bool rWasPressed = false;
    bool rPressed = glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS;

    if (rPressed && !rWasPressed)
        resetGame();

    rWasPressed = rPressed;
}

// Main function
int main()
{
    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(
        SCR_WIDTH, SCR_HEIGHT, "Tic-Tac-Toe  -  By Team Reaper   ", NULL, NULL
    );

    if (!window)
    {
        std::cout << "Failed to create window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD\n";
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    // Create VAO and VBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(
        0, 2, GL_FLOAT, GL_FALSE,
        2 * sizeof(float), (void*)0
    );

    glEnableVertexAttribArray(0);

    createShaderProgram();
    glfwSetMouseButtonCallback(window, mouseButtonCallback);

    // Main rendering loop
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.04f, 0.05f, 0.09f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);

        double now = glfwGetTime();

        drawBoard();

        for (int r = 0; r < 3; r++)
        {
            for (int c = 0; c < 3; c++)
            {
                // IMPORTANT: only draw actual X or O symbols.
                // Empty cells must never be treated as O.
                if (board[r][c] == ' ')
                    continue;

                float progress = static_cast<float>(
                    std::clamp((now - moveTime[r][c]) / 0.25,
                               0.0, 1.0));

                if (board[r][c] == 'X')
                    drawX(r, c, progress);
                else if (board[r][c] == 'O')
                    drawO(r, c, progress);
            }
        }

        // Draw the winning line
        if (winner != ' ')
        {
            float progress = static_cast<float>(
                std::clamp((now - winTime) / 0.5, 0.0, 1.0));

            std::vector<float> vertices;

            addLine(vertices,
                winLine[0], winLine[1],
                winLine[2], winLine[3], progress);

            drawLines(vertices, 1.0f, 0.85f, 0.1f);
        }

        // Display game status in the window title
        if (winner != ' ')
        {
            glfwSetWindowTitle(window,
                winner == 'X'
                ? "Tic-Tac-Toe -  By Team Reaper - X Wins! Press R to Restart"
                : "Tic-Tac-Toe -  By Team Reaper - O Wins! Press R to Restart");
        }
        else if (isDraw)
        {
            glfwSetWindowTitle(window,
                "Tic-Tac-Toe -  By Team Reaper - Draw! Press R to Restart");
        }
        else
        {
            glfwSetWindowTitle(window,
                currentPlayer == 'X'
                ? "Tic-Tac-Toe -  By Team Reaper - Player X's Turn"
                : "Tic-Tac-Toe -  By Team Reaper - Player O's Turn");
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean up
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
