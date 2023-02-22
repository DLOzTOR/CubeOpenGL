#include <iostream>
#include <SFML/Graphics.hpp>
#include <GL/glew.h>
#include <GL/GL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
const GLchar* codeVertArray[] = { "#version 460\nin vec3 VertexPosition;layout(location = 1) in vec3 vertexColor;out vec3 Color;uniform mat4 RotationMatrix;void main(){Color = vertexColor;gl_Position = RotationMatrix * vec4(VertexPosition / 2, 1.0);}" };
const GLchar* codeFragArray[] = { "#version 460\n in vec3 Color;\nout vec4 FragColor;\nvoid main()\n {FragColor = vec4(Color, 1);}" };
static const GLfloat g_vertex_buffer_data[] = {
    -1.0f,-1.0f,-1.0f, // Треугольник 1 : начало
    -1.0f,-1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f, // Треугольник 1 : конец
    1.0f, 1.0f,-1.0f, // Треугольник 2 : начало
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f, // Треугольник 2 : конец
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f
};
static const GLfloat g_color_buffer_data[] = {
    0.583f,  0.771f,  0.014f,
    0.609f,  0.115f,  0.436f,
    0.327f,  0.483f,  0.844f,
    0.822f,  0.569f,  0.201f,
    0.435f,  0.602f,  0.223f,
    0.310f,  0.747f,  0.185f,
    0.597f,  0.770f,  0.761f,
    0.559f,  0.436f,  0.730f,
    0.359f,  0.583f,  0.152f,
    0.483f,  0.596f,  0.789f,
    0.559f,  0.861f,  0.639f,
    0.195f,  0.548f,  0.859f,
    0.014f,  0.184f,  0.576f,
    0.771f,  0.328f,  0.970f,
    0.406f,  0.615f,  0.116f,
    0.676f,  0.977f,  0.133f,
    0.971f,  0.572f,  0.833f,
    0.140f,  0.616f,  0.489f,
    0.997f,  0.513f,  0.064f,
    0.945f,  0.719f,  0.592f,
    0.543f,  0.021f,  0.978f,
    0.279f,  0.317f,  0.505f,
    0.167f,  0.620f,  0.077f,
    0.347f,  0.857f,  0.137f,
    0.055f,  0.953f,  0.042f,
    0.714f,  0.505f,  0.345f,
    0.783f,  0.290f,  0.734f,
    0.722f,  0.645f,  0.174f,
    0.302f,  0.455f,  0.848f,
    0.225f,  0.587f,  0.040f,
    0.517f,  0.713f,  0.338f,
    0.053f,  0.959f,  0.120f,
    0.393f,  0.621f,  0.362f,
    0.673f,  0.211f,  0.457f,
    0.820f,  0.883f,  0.371f,
    0.982f,  0.099f,  0.879f
};
int main()
{
    using glm::mat4;
    using glm::vec3;

    sf::RenderWindow window(sf::VideoMode(1000, 1000), "My window");
    window.setActive();
    window.setFramerateLimit(60);
    if (glewInit() != GLEW_OK) { std::cout << "Glew init problem" << std::endl; return -1; }
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, codeVertArray, nullptr);
    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, codeFragArray, nullptr);
    GLuint shaderHandle = glCreateProgram();
    glAttachShader(shaderHandle, vertexShader);
    glAttachShader(shaderHandle, fragShader);
    glLinkProgram(shaderHandle);
    glDeleteShader(vertexShader);
    glDeleteShader(fragShader);

    GLuint vao;
    GLuint VAOposId;
    GLuint colorbuffer;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &VAOposId);
    glBindBuffer(GL_ARRAY_BUFFER, VAOposId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    mat4 rotationMatrix = mat4(1.0f);
    float angle = 0;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        glUseProgram(shaderHandle);
        rotationMatrix = glm::rotate(mat4(1.0f), glm::radians(angle), vec3(0, 1, 1));
        GLuint location = glGetUniformLocation(shaderHandle, "RotationMatrix");
        angle++;
        glUniformMatrix4fv(location, 1, GL_FALSE, &rotationMatrix[0][0]);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0, 0, 0, 1);
        glBindVertexArray(vao);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        window.display();
    }
    return 0;
}