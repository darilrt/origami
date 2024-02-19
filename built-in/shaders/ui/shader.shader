[modules]
fragment = "eabf67b0-f508-ecd9-a6b5-65b94fbf4bff"
vertex = "d10f857f-16c2-e3e8-d2a9-180fc992eec1"

[[bindings]]
binding = 0
name = "Camera"
uniforms = [
    { name = "proj", type = "mat4", order = 0 },
]

[properties]
render_pass = "lit"
topology = "triangle_list"
cull_mode = "back"
front_face = "clockwise"
polygon_mode = "fill"