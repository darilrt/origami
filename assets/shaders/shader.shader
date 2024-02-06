
[modules]
fragment = "de7c3a32-aa9f-3f81-b265-8a29bd24dfac"
vertex = "97d64cf5-0df3-4ad7-725f-093edc66292e"

[[bindings]]
binding = 0
input_rate = "vertex"

[attributes]
position = { format = "vec3", location = 0, binding = 0, offset = 0 }
normal = { format = "vec3", location = 1, binding = 0, offset = 12 } 
uv = { format = "vec2", location = 2, binding = 0, offset = 24 }

[uniforms]
model = { position = 0, type = "mat4" }
view = { position = 1, type = "mat4" }
projection = { position = 2, type = "mat4" }
time = { position = 3, type = "float" }

[properties]
render_pass = "lit"
topology = "triangle_list"
cull_mode = "back"
front_face = "clockwise"
polygon_mode = "fill"