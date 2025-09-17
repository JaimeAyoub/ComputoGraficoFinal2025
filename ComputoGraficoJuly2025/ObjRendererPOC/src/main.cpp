#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "model.h"

#include <iostream>

// For stb_image to work, define this macro in ONE .cpp file
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

// --- Function Prototypes ---
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// --- Settings ---
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// Camera (simple fixed position for demonstration)
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

// Delta time for movement
float deltaTime = 0.0f;
float lastFrame = 0.0f;

double posxMouse, posyMouse;

int main() {
    // --- GLFW: Initialize and Configure ---
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Required for macOS
#endif

    // --- GLFW: Window Creation ---
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL Model Loading", NULL, NULL);
    if (window == NULL) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // --- GLAD: Load all OpenGL function pointers ---
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Configure global OpenGL state
    glEnable(GL_DEPTH_TEST);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // --- Build and Compile our Shader program ---
    // Make sure these paths are correct relative to your executable
    Shader ourShader("shaders/default_vertex_shader.glsl", "shaders/default_fragment_shader.glsl");

    // --- Load Model ---
    // Replace "path/to/your/model.obj" with the actual path to your 3D model
    // Common formats: .obj, .fbx, .gltf
    Model ourModel("Modelos/scene.gltf");
    //Model ourModel("H:/Desarrollo/3DModels/Tron_Tank/Tron Tank.fbx");
    //Model ourModel("H:/Desarrollo/3DModels/ftl_faster_than_light_kestrel_cruiser/scene.gltf");

    // --- Render Loop ---
    while (!glfwWindowShouldClose(window)) {
        // Per-frame time logic
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Input
        processInput(window);

        // Render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Activate shader
        ourShader.use();

        // Pass projection matrix to shader (it's a perspective matrix)
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        ourShader.setMat4("projection", projection);

        //Pass acumTrans
       glfwGetCursorPos(window, &posxMouse, &posyMouse);
       glm::mat4 accumTransX = glm::rotate(glm::mat4(1.0f), glm::radians(static_cast<float>(posyMouse) * 20 / SCR_HEIGHT), glm::vec3(1.0f, 0.0f, 0.0f));
       glm::mat4 accumTransY = glm::rotate(glm::mat4(1.0f), glm::radians(static_cast<float>(posxMouse) * 20 / SCR_WIDTH), glm::vec3(0.0f, 1.0f, 0.0f));
       glm::mat4  accumTrans = accumTransX * accumTransY;
       ourShader.setMat4("accumTrans", accumTrans);

        // Camera/View transformation
        glm::mat4 view = glm::lookAt(cameraPos, cameraFront, cameraUp);
        ourShader.setMat4("view", view);

        // Render the loaded model
        glm::mat4 model = glm::mat4(1.0f); // Make sure to initialize to identity matrix!
        glm::vec3 reCenter = ourModel.GetCenter();
        reCenter.y -= 0.5f;
        reCenter.z /= 6.0f;
        model = glm::translate(model, -reCenter);// Translate model to center (example)
        glm::vec3 minBB, maxBB;
        std::tie(minBB, maxBB) = ourModel.BoundingBox();
        glm::vec3 dimension = maxBB - minBB;

        float maxValue = std::max(dimension.x, std::max(dimension.y, dimension.z));
        model = glm::scale(model,glm::vec3(2.0f/maxValue));       // Scale model (example, might need adjustment)
        ourShader.setMat4("model", model);

        // --- THIS IS WHERE YOUR SHADER INTERACTS WITH THE MODEL DATA ---
        // The Mesh::Draw method will bind the VAO, EBO, and textures.
        // It will also set the texture uniforms like 'material.texture_diffuse1'.
        // You just need to ensure your fragment shader receives these.
        ourModel.Draw(ourShader,model);

        // GLFW: Swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // GLFW: Terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

// --- Input Processing ---
void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // Simple camera movement for demonstration
    float cameraSpeed = 2.5f * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraUp;
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraUp;
}

// --- GLFW: Callback for window resize ---
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // Make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}