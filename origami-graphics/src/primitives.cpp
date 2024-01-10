#include "origami/graphics/primitives.hpp"

Mesh *primitive::quad()
{
    return new Mesh({
        {{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
        {{0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
        {{0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
        {{-0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
        {{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
        {{0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
    });
}

Mesh *primitive::cube()
{
    return new Mesh({
        // Front
        {{-0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
        {{0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
        {{0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
        {{-0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
        {{-0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
        {{0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
        // Back
        {{0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}},
        {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}},
        {{-0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f}},
        {{0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}},
        {{0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}},
        {{-0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f}},
        // Left
        {{-0.5f, -0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},
        {{-0.5f, -0.5f, 0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
        {{-0.5f, 0.5f, 0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
        {{-0.5f, 0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
        {{-0.5f, -0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},
        {{-0.5f, 0.5f, 0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
        // Right
        {{0.5f, -0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},
        {{0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
        {{0.5f, 0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
        {{0.5f, 0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
        {{0.5f, -0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},
        {{0.5f, 0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
        // Top
        {{-0.5f, 0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},
        {{0.5f, 0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},
        {{0.5f, 0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
        {{-0.5f, 0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
        {{-0.5f, 0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},
        {{0.5f, 0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
        // Bottom
        {{-0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f}},
        {{0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f}},
        {{0.5f, -0.5f, 0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f}},
        {{-0.5f, -0.5f, 0.5f}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f}},
        {{-0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f}},
        {{0.5f, -0.5f, 0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f}},
    });
}

Mesh *primitive::sphere(int subdivisions_x, int subdivisions_y)
{
    std::vector<Vertex> vertices;
    std::vector<Vertex> temp_vertices;

    for (int y = 0; y <= subdivisions_y; y++)
    {
        for (int x = 0; x <= subdivisions_x; x++)
        {
            float x_segment = (float)x / (float)subdivisions_x;
            float y_segment = (float)y / (float)subdivisions_y;

            float x_pos = std::cos(x_segment * 2.0f * math::pi) * std::sin(y_segment * math::pi);
            float y_pos = std::cos(y_segment * math::pi);
            float z_pos = std::sin(x_segment * 2.0f * math::pi) * std::sin(y_segment * math::pi);

            temp_vertices.push_back({{x_pos, y_pos, z_pos}, {x_pos, y_pos, z_pos}, {x_segment, y_segment}});
        }
    }

    bool odd_row = false;
    for (int y = 0; y < subdivisions_y; y++)
    {
        for (int x = 0; x < subdivisions_x; x++)
        {
            int i0 = y * (subdivisions_x + 1) + x;
            int i1 = i0 + 1;
            int i2 = i0 + (subdivisions_x + 1);
            int i3 = i2 + 1;

            if (!odd_row)
            {
                vertices.push_back(temp_vertices[i2]);
                vertices.push_back(temp_vertices[i0]);
                vertices.push_back(temp_vertices[i1]);

                vertices.push_back(temp_vertices[i2]);
                vertices.push_back(temp_vertices[i1]);
                vertices.push_back(temp_vertices[i3]);
            }
            else
            {
                vertices.push_back(temp_vertices[i2]);
                vertices.push_back(temp_vertices[i0]);
                vertices.push_back(temp_vertices[i3]);

                vertices.push_back(temp_vertices[i3]);
                vertices.push_back(temp_vertices[i0]);
                vertices.push_back(temp_vertices[i1]);
            }
        }
        odd_row = !odd_row;
    }

    return new Mesh(vertices);
}

Mesh *primitive::cylinder(int subdivisions_x)
{
    std::vector<Vertex> vertices;
    std::vector<Vertex> temp_vertices;

    for (int y = 0; y <= 1; y++)
    {
        for (int x = 0; x <= subdivisions_x; x++)
        {
            float x_segment = (float)x / (float)subdivisions_x;
            float x_pos = std::cos(x_segment * 2.0f * math::pi);
            float z_pos = std::sin(x_segment * 2.0f * math::pi);

            temp_vertices.push_back({{x_pos, (float)y * 2.0f - 1.0f, z_pos}, {x_pos, 0.0f, z_pos}, {x_segment, (float)y}});
        }
    }

    // ring
    for (int x = 0; x < subdivisions_x; x++)
    {
        int i0 = x;
        int i1 = i0 + 1;
        int i2 = i0 + subdivisions_x + 1;
        int i3 = i2 + 1;

        vertices.push_back(temp_vertices[i0]);
        vertices.push_back(temp_vertices[i2]);
        vertices.push_back(temp_vertices[i1]);

        vertices.push_back(temp_vertices[i1]);
        vertices.push_back(temp_vertices[i2]);
        vertices.push_back(temp_vertices[i3]);
    }

    // bottom cap
    for (int x = 0; x < subdivisions_x; x++)
    {
        int i0 = x;
        int i1 = i0 + 1;
        int i2 = (int)0;

        vertices.push_back(temp_vertices[i0]);
        vertices.push_back(temp_vertices[i1]);
        vertices.push_back(temp_vertices[i2]);
    }

    // top cap
    for (int x = 0; x < subdivisions_x; x++)
    {
        int i0 = x + subdivisions_x + 1;
        int i1 = i0 + 1;
        int i2 = (int)temp_vertices.size() - 1;

        vertices.push_back(temp_vertices[i0]);
        vertices.push_back(temp_vertices[i2]);
        vertices.push_back(temp_vertices[i1]);
    }

    return new Mesh(vertices);
}

Mesh *primitive::torus(float radius, float thickness, int subdivisions_x, int subdivisions_y)
{
    std::vector<Vertex> vertices;
    std::vector<Vertex> temp_vertices;

    for (int y = 0; y <= subdivisions_y; y++)
    {
        for (int x = 0; x <= subdivisions_x; x++)
        {
            float x_segment = (float)x / (float)subdivisions_x;
            float y_segment = (float)y / (float)subdivisions_y;

            float x_pos = std::cos(x_segment * 2.0f * math::pi) * (radius + std::cos(y_segment * 2.0f * math::pi) * thickness);
            float y_pos = std::sin(y_segment * 2.0f * math::pi) * thickness;
            float z_pos = std::sin(x_segment * 2.0f * math::pi) * (radius + std::cos(y_segment * 2.0f * math::pi) * thickness);

            Vec3 normal = Vec3(x_pos, y_pos, z_pos).normalize();

            temp_vertices.push_back({{x_pos, y_pos, z_pos}, normal, {x_segment, y_segment}});
        }
    }

    bool odd_row = false;
    for (int y = 0; y < subdivisions_y; y++)
    {
        for (int x = 0; x < subdivisions_x; x++)
        {
            int i0 = y * (subdivisions_x + 1) + x;
            int i1 = i0 + 1;
            int i2 = i0 + (subdivisions_x + 1);
            int i3 = i2 + 1;

            if (!odd_row)
            {
                vertices.push_back(temp_vertices[i0]);
                vertices.push_back(temp_vertices[i2]);
                vertices.push_back(temp_vertices[i1]);

                vertices.push_back(temp_vertices[i1]);
                vertices.push_back(temp_vertices[i2]);
                vertices.push_back(temp_vertices[i3]);
            }
            else
            {
                vertices.push_back(temp_vertices[i0]);
                vertices.push_back(temp_vertices[i2]);
                vertices.push_back(temp_vertices[i3]);

                vertices.push_back(temp_vertices[i0]);
                vertices.push_back(temp_vertices[i3]);
                vertices.push_back(temp_vertices[i1]);
            }
        }
        odd_row = !odd_row;
    }

    return new Mesh(vertices);
}

Mesh *primitive::plane()
{
    return new Mesh({
        {{0.5f, 0.0f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},
        {{-0.5f, 0.0f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},
        {{0.5f, 0.0f, 0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
        {{-0.5f, 0.0f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},
        {{-0.5f, 0.0f, 0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
        {{0.5f, 0.0f, 0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
    });
}