#version 330

uniform sampler2D tex;

out vec4 pixelColor; //Zmienna wyjsciowa fragment shadera. Zapisuje sie do niej ostateczny (prawie) kolor piksela
in vec4 l;
in vec4 l1;
in vec4 l2;
in vec4 l3;
in vec4 l4;
in vec4 n;
in vec4 v;
in vec2 i_tc;

void main(void) {
    vec4 _l = normalize(l);
    vec4 _n = normalize(n);
    vec4 _v = normalize(v);

    vec4 _r = reflect(-_l, _n);

    float nl = clamp(dot(_n, l), 0, 1); // iloczyn skalarny należący do (0, 1)
    float nl1 = clamp(dot(_n, l1), 0, 1); // iloczyn skalarny należący do (0, 1)
    float nl2 = clamp(dot(_n, l2), 0, 1); // iloczyn skalarny należący do (0, 1)
    float nl3 = clamp(dot(_n, l3), 0, 1); // iloczyn skalarny należący do (0, 1)
    float nl4 = clamp(dot(_n, l4), 0, 1); // iloczyn skalarny należący do (0, 1)
    float rv = pow(clamp(dot(_r, _v), 0, 1), 25);


    //pixelColor = ic*nl + rv;

    vec4 color=texture(tex,i_tc);
	pixelColor=vec4(clamp(color.rgb*nl + color.rgb*nl1*0.67 + color.rgb*nl2*0.33 + color.rgb*nl3*0.1 + color.rgb*nl4*0.5, 0, 1),color.a);
}