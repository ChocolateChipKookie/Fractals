//
// Created by kookie on 20. 11. 2020..
//

#include "Pixies.h"

kki::Pixies::Pixies(std::vector<glm::vec2> vertices, std::vector<glm::vec3> colours)
        : positions(std::move(vertices)),
          colours(std::move(colours)),
          pixies(positions.size())
{
    assert(vertices.size() == colours.size());
    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);

    glGenBuffers(2, _vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(positions[0]), positions.data(), GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(positions[0]), reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, _vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, colours.size() * sizeof(colours[0]), colours.data(), GL_DYNAMIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(colours[0]), reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

kki::Pixies::Pixies(size_t count, bool random_start)
        : pixies(count)

{
    if (random_start) {
        auto rng = kki::rng::global;
        positions.reserve(pixies);
        for (size_t i = 0; i < pixies; ++i){
            positions.emplace_back(rng.randomReal(-1.f, 1.f), rng.randomReal(-1.f, 1.f));
        }
        colours.resize(pixies, {1, 0, 0});
    } else {
        positions.resize(pixies);
        colours.resize(pixies, {1, 0, 0});
    }

    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);

    glGenBuffers(2, _vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(positions[0]), positions.data(), GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(positions[0]), reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, _vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, colours.size() * sizeof(colours[0]), colours.data(), GL_DYNAMIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(colours[0]), reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

kki::Pixies::~Pixies() {
    glDeleteBuffers(2, _vbo);
    glDeleteVertexArrays(1, &_vao);
}

void kki::Pixies::resetPositions() {
    auto rng = kki::rng::global;
    for (size_t i = 0; i < pixies; ++i){
        positions[i] = {rng.randomReal(-1.f, 1.f), rng.randomReal(-1.f, 1.f)};
    }
}

void kki::Pixies::draw(std::shared_ptr<kki::Shader> shader) {
    shader->use();
    glBindVertexArray(_vao);
    glDrawArrays(GL_POINTS, 0, positions.size());

}

void kki::Pixies::updateBuffer() {
    glBindBuffer(GL_ARRAY_BUFFER, _vbo[0]);
    glBufferSubData(GL_ARRAY_BUFFER, 0, positions.size() * sizeof(positions[0]), positions.data());
    glBindBuffer(GL_ARRAY_BUFFER, _vbo[1]);
    glBufferSubData(GL_ARRAY_BUFFER, 0, colours.size() * sizeof(colours[0]), colours.data());
}

void kki::Pixies::updateAll() {
    for(size_t i = 0; i < pixies; ++i){
        update(i);
    }
    updateBuffer();
}
