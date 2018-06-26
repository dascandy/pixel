


const char vertex_shader[] =
"#version 330\n"
"\n"
"uniform vec4 sc_pos;\n"
"\n"
"in vec4 in_pos;\n"
"out vec4 f_pos;\n"
"\n"
"void main() {\n"
"  mat2 r = mat2(sin(in_pos.w), cos(in_pos.w), cos(in_pos.w), -sin(in_pos.w));\n"
"  gl_Position = vec4(((r * in_pos.xy) * sc_pos.z) + sc_pos.xy * sc_pos.z, in_pos.zw);\n"
"  gl_Position = in_pos;\n"
"  f_pos = in_pos;\n"
"}\n"
"\n"
;

const char fragment_shader[] =
"#version 330\n"
"\n"
"uniform vec4 sc_attr;\n"
"uniform sampler2D tex;\n"
"uniform vec4 key;\n"
"uniform int keyed;\n"
"\n"
"in vec4 f_pos;\n"
"\n"
"void main() {\n"
"  vec4 color = texture(tex, 0.5 * (f_pos.xy * sc_attr.zw + sc_attr.xy) + vec2(0.5, 0.5));\n"
"  if (keyed == 1 && key == color) discard;\n"
"  gl_FragColor = color;\n"
"}\n"
"\n"
;

const char shake_shader[] = 
"#version 330\n"
"\n"
"uniform sampler2D tex;\n"
"uniform float strength;\n"
"\n"
"in vec4 f_pos;\n"
"\n"
"void main() {\n"
"  vec2 uv = 0.5 * f_pos.xy + vec2(0.5, 0.5);\n"
"  vec2 uv_delta = vec2(sin(iTime *120.0), cos(iTime*120.0)) * (strength / 20.0);\n"
"  gl_FragColor = texture(tex, uv + uv_delta);\n"
"}\n"
"\n"
;

const char blocky_shader[] =
"#version 330\n"
"\n"
"uniform sampler2D tex;\n"
"uniform float strength;\n"
"\n"
"in vec4 f_pos;\n"
"\n"
"void main() {\n"
"  vec2 uv = 0.5 * f_pos.xy + vec2(0.5, 0.5);\n"
"  int i = int(strength * 6.0);\n"
"  float div = 256.0f / float(1 << i);\n"
"  ivec2 i_uv = ivec2(uv * div);\n"
"  gl_FragColor = texture(tex, vec2(i_uv) / div);\n"
"}\n"
;

const char spiral_shader[] =
"#version 330\n"
"\n"
"uniform sampler2D tex;\n"
"uniform float strength;\n"
"\n"
"in vec4 f_pos;\n"
"\n"
"void main() {\n"
"  float dist = dot(f_pos.xy, f_pos.xy) * strength * 20;\n"
"  vec2 npos = mat2(sin(dist), cos(dist), cos(dist), -sin(dist)) * f_pos.xy;\n"
"  vec2 uv = 0.5 * npos + vec2(0.5, 0.5);\n"
"  gl_FragColor = texture(tex, uv);\n"
"}\n"
;

const char vwaves_shader[] =
"#version 330\n"
"\n"
"uniform sampler2D tex;\n"
"uniform float strength;\n"
"\n"
"in vec4 f_pos;\n"
"\n"
"void main() {\n"
"  vec2 npos = f_pos.xy + vec2(0, sin(f_pos.y * 30));\n"
"  vec2 uv = 0.5 * npos + vec2(0.5, 0.5);\n"
"  gl_FragColor = texture(tex, uv);\n"
"}\n"
;

const char hwaves_shader[] =
"#version 330\n"
"\n"
"uniform sampler2D tex;\n"
"uniform float strength;\n"
"\n"
"in vec4 f_pos;\n"
"\n"
"void main() {\n"
"  vec2 npos = f_pos.xy + vec2(sin(f_pos.x * 20), 0);\n"
"  vec2 uv = 0.5 * npos + vec2(0.5, 0.5);\n"
"  gl_FragColor = texture(tex, uv);\n"
"}\n"
;

const char blur_shader[] =
""
;


