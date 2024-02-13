
[modules]
fragment = "de7c3a32-aa9f-3f81-b265-8a29bd24dfac"
vertex = "97d64cf5-0df3-4ad7-725f-093edc66292e"

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
    { name = "time", type = "float", order = 0 },
]

[[bindings]]
binding = 2
name = "Material"
uniforms = [
]

[properties]
render_pass = "lit"
topology = "triangle_list"
cull_mode = "back"
front_face = "clockwise"
polygon_mode = "fill"