[modules]
fragment = "22e5fb6e-78f0-23e7-5574-5826f198aefa"
vertex = "b774a3df-8008-debb-4330-33f113079f8d"

[[bindings]]
binding = 0
name = "Transform"
uniforms = [
    { name = "model", type = "mat4", order = 0 },
    { name = "view", type = "mat4", order = 1 },
    { name = "proj", type = "mat4", order = 2 }
]

[[bindings]]
binding = 1
name = "Environment"
uniforms = [
    { name = "camera", type = "vec3", order = 0 },
    { name = "time", type = "float", order = 1 },
]

[properties]
render_pass = "lit"
topology = "triangle_list"
cull_mode = "back"
front_face = "clockwise"
polygon_mode = "fill"