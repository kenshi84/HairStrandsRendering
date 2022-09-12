#pragma once

#include <vector>
#include <glm/glm.hpp>

class Vertex
{

public:
    Vertex() : m_pos(), m_normal() {}
  
    // Initialize by string to be tokenized
    // TODO: Better handle outside of this class
    Vertex(const std::vector<std::string> tokens)
    {
    }

    Vertex(const glm::vec3& pos, const glm::vec3& normal) : m_pos(pos), m_normal(normal)
    {
    }

    ~Vertex() = default;


    glm::vec3 m_pos;

    glm::vec3 m_normal;

    // TODO
    // glm::vec2 mUV;
};