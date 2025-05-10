#include "wall.h"

void Wall::wall_initializer(){
    static float verts[]={
        //ściana 1
        1.0f,-1.0f,-1.0f,1.0f,
        -1.0f, 1.0f,-1.0f,1.0f,
        -1.0f,-1.0f,-1.0f,1.0f,

        1.0f,-1.0f,-1.0f,1.0f,
        1.0f, 1.0f,-1.0f,1.0f,
        -1.0f, 1.0f,-1.0f,1.0f,

        //ściana 2
        -1.0f,-1.0f, 1.0f,1.0f,
        1.0f, 1.0f, 1.0f,1.0f,
        1.0f,-1.0f, 1.0f,1.0f,

        -1.0f,-1.0f, 1.0f,1.0f,
        -1.0f, 1.0f, 1.0f,1.0f,
        1.0f, 1.0f, 1.0f,1.0f,


        //ściana 3
        -1.0f,-1.0f,-1.0f,1.0f,
        1.0f,-1.0f, 1.0f,1.0f,
        1.0f,-1.0f,-1.0f,1.0f,

        -1.0f,-1.0f,-1.0f,1.0f,
        -1.0f,-1.0f, 1.0f,1.0f,
        1.0f,-1.0f, 1.0f,1.0f,

        //ściana 4
        -1.0f, 1.0f, 1.0f,1.0f,
        1.0f, 1.0f,-1.0f,1.0f,
        1.0f, 1.0f, 1.0f,1.0f,

        -1.0f, 1.0f, 1.0f,1.0f,
        -1.0f, 1.0f,-1.0f,1.0f,
        1.0f, 1.0f,-1.0f,1.0f,

        //ściana 5
        -1.0f,-1.0f,-1.0f,1.0f,
        -1.0f, 1.0f, 1.0f,1.0f,
        -1.0f,-1.0f, 1.0f,1.0f,

        -1.0f,-1.0f,-1.0f,1.0f,
        -1.0f, 1.0f,-1.0f,1.0f,
        -1.0f, 1.0f, 1.0f,1.0f,

        //ściana 6
        1.0f,-1.0f, 1.0f,1.0f,
        1.0f, 1.0f,-1.0f,1.0f,
        1.0f,-1.0f,-1.0f,1.0f,

        1.0f,-1.0f, 1.0f,1.0f,
        1.0f, 1.0f, 1.0f,1.0f,
        1.0f, 1.0f,-1.0f,1.0f,
    };

    static float texCoords[] = {
        1.0f, 0.0f,	  0.0f, 1.0f,    0.0f, 0.0f,
        1.0f, 0.0f,   1.0f, 1.0f,    0.0f, 1.0f,

        1.0f, 0.0f,	  0.0f, 1.0f,    0.0f, 0.0f,
        1.0f, 0.0f,   1.0f, 1.0f,    0.0f, 1.0f,

        1.0f, 0.0f,	  0.0f, 1.0f,    0.0f, 0.0f,
        1.0f, 0.0f,   1.0f, 1.0f,    0.0f, 1.0f,

        1.0f, 0.0f,	  0.0f, 1.0f,    0.0f, 0.0f,
        1.0f, 0.0f,   1.0f, 1.0f,    0.0f, 1.0f,

        1.0f, 0.0f,	  0.0f, 1.0f,    0.0f, 0.0f,
        1.0f, 0.0f,   1.0f, 1.0f,    0.0f, 1.0f,

        1.0f, 0.0f,	  0.0f, 1.0f,    0.0f, 0.0f,
        1.0f, 0.0f,   1.0f, 1.0f,    0.0f, 1.0f,
    };

    static float normals[]={
            0.0f,0.0f,-1.0f,0.0f, //A
            0.0f,0.0f,-1.0f,0.0f, //B
            0.0f,0.0f,-1.0f,0.0f, //C
            0.0f,0.0f,-1.0f,0.0f, //A
            0.0f,0.0f,-1.0f,0.0f, //D
            0.0f,0.0f,-1.0f,0.0f, //B

            0.0f,0.0f,1.0f,0.0f, //A
            0.0f,0.0f,1.0f,0.0f, //B
            0.0f,0.0f,1.0f,0.0f, //C
            0.0f,0.0f,1.0f,0.0f, //A
            0.0f,0.0f,1.0f,0.0f, //D
            0.0f,0.0f,1.0f,0.0f, //B

            0.0f,-1.0f,0.0f,0.0f, //A
            0.0f,-1.0f,0.0f,0.0f, //B
            0.0f,-1.0f,0.0f,0.0f, //C
            0.0f,-1.0f,0.0f,0.0f, //A
            0.0f,-1.0f,0.0f,0.0f, //D
            0.0f,-1.0f,0.0f,0.0f, //B

            0.0f,1.0f,0.0f,0.0f, //A
            0.0f,1.0f,0.0f,0.0f, //B
            0.0f,1.0f,0.0f,0.0f, //C
            0.0f,1.0f,0.0f,0.0f, //A
            0.0f,1.0f,0.0f,0.0f, //D
            0.0f,1.0f,0.0f,0.0f, //B

            -1.0f,0.0f,0.0f,0.0f, //A
            -1.0f,0.0f,0.0f,0.0f, //B
            -1.0f,0.0f,0.0f,0.0f, //C
            -1.0f,0.0f,0.0f,0.0f, //A
            -1.0f,0.0f,0.0f,0.0f, //D
            -1.0f,0.0f,0.0f,0.0f, //B

            1.0f,0.0f,0.0f,0.0f, //A
            1.0f,0.0f,0.0f,0.0f, //B
            1.0f,0.0f,0.0f,0.0f, //C
            1.0f,0.0f,0.0f,0.0f, //A
            1.0f,0.0f,0.0f,0.0f, //D
            1.0f,0.0f,0.0f,0.0f, //B
    };

    VERTICES = verts;
    NORMALS = normals;
    TEX_COORDS = new float[72];
    for(unsigned short i=0;i<72;i++) TEX_COORDS[i] = texCoords[i];

    skaluj(TEX_COORDS, 1, 72, 2, h);
    skaluj(TEX_COORDS, 0, 36, 2, l);
    skaluj(TEX_COORDS, 36, 72, 2, w);
}

void Wall::skaluj(float tab[], unsigned int start, unsigned int stop, unsigned int step, float mnoznik){
    for(unsigned i=start;i<stop;i += step) tab[i] *= mnoznik;
}

Wall::Wall(){
    DBL = glm::vec3(0.0, 0.0, 0.0);
    h = 1.0;
    w = 1.0;
    l = 1.0;
    wall_initializer();
}

Wall::Wall(glm::vec3 DBL, glm::vec3 LHW){
    this->DBL = DBL;
    l = LHW.x;
    h = LHW.y;
    w = LHW.z;
    wall_initializer();
}

Wall::Wall(float xl, float yd, float zb, float dlugosc, float wysokosc, float szerokosc){
    DBL = glm::vec3(xl, yd, zb);
    this->l = dlugosc;
    this->h = wysokosc;
    this->w = szerokosc;
    wall_initializer();
}

Wall::~Wall(){
    //delete[] TEX_COORDS;
}

void Wall::setAngle_horizontal(float alpha){
    this->angle_horizontal = alpha;
}

void Wall::draw(glm::mat4 P, glm::mat4 V, GLuint tex){
    static ShaderProgram* s_p = spLambertSun;
    s_p->use(); //Aktywuj program cieniujący
    glm::mat4 M = glm::mat4(1.0f);

    M = glm::translate(M, DBL);
    M = glm::rotate(M, -angle_horizontal, glm::vec3(0.0, 3.0, 0.0));
    M = glm::translate(M, -DBL);
    M = glm::scale(M, glm::vec3(l, h, w)*glm::vec3(0.5, 0.5, 0.5));
    M = glm::translate(M, glm::vec3(1, 1, 1 ));
    M = glm::translate(M, DBL / glm::vec3(l*0.5, h*0.5, w*0.5));

    glUniformMatrix4fv(s_p->u("P"),1,false,glm::value_ptr(P));
    glUniformMatrix4fv(s_p->u("V"),1,false,glm::value_ptr(V));
    glUniformMatrix4fv(s_p->u("M"),1,false,glm::value_ptr(M));

    glEnableVertexAttribArray(s_p->a("vertex"));
    glEnableVertexAttribArray(s_p->a("normal"));
    glEnableVertexAttribArray(s_p->a("texCoord"));

    glVertexAttribPointer(s_p->a("vertex"),4,GL_FLOAT,false,0,VERTICES);
    glVertexAttribPointer(s_p->a("normal"),4,GL_FLOAT,false,0,NORMALS);
    glVertexAttribPointer(s_p->a("texCoord"),2,GL_FLOAT,false,0,TEX_COORDS);
    
    glActiveTexture(GL_TEXTURE0); glBindTexture(GL_TEXTURE_2D,tex);
    glUniform1i(s_p->u("tex"),0);
    glDrawArrays( GL_TRIANGLES, 0, VERTEX_COUNT);

    glDisableVertexAttribArray(spLambertTextured->a("vertex"));
    glDisableVertexAttribArray(spLambertTextured->a("normal"));
    glDisableVertexAttribArray(spLambertTextured->a("texCoord")); 
}

bool Wall::is_within(glm::vec3 punkt, float r){
    glm::vec3 _punkt; // punkt w układzie współrzędnych muru
    _punkt.x = (punkt.x - DBL.x)*cos(angle_horizontal) + (punkt.z - DBL.z)*sin(angle_horizontal);
    _punkt.z = -(punkt.x - DBL.x)*sin(angle_horizontal) + (punkt.z - DBL.z)*cos(angle_horizontal);
    _punkt.y = punkt.y;

    if(_punkt.x + r > 0 && _punkt.z + r > 0 && _punkt.y > DBL.y && _punkt.x-r < l && _punkt.z-r < w && _punkt.y < DBL.y + h){
        printf("new position invalid\n");
        return true;
    }
    else return false;
}

//Wall_traingular ---------------------------------------------------
void Wall_triangular::shape_triangle(float v[], float n[]){
    float x = b * cos(gamma) / a;
    float z = b * sin(gamma) / a;
    v[32] = x;
    v[34] = z;
    v[36] = x;
    v[38] = z;
    v[40] = x;
    v[42] = z;
    v[56] = x;
    v[58] = z;
    v[60] = x;
    v[62] = z;
    v[64] = x;
    v[66] = z;
    v[80] = x;
    v[82] = z;
    v[92] = x;
    v[94] = z;

    for(unsigned short i=6;i<12;i++){
        n[i*4] = -z;
        n[i*4 + 2] = x; 
    }
    for(unsigned short i=12;i<18;i++){
        n[i*4] = z;
        n[i*4 + 2] = -x;
    }
}

void Wall_triangular::wall_initializer(){
    float Vertices[]={
        //ściana 1
        0.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f,

        //ściana 2
        0.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.5f, 0.0f, 0.5f, 1.0f,

        0.5f, 0.0f, 0.5f, 1.0f,
        0.5f, 1.0f, 0.5f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,

        //ściana 3
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f,
        0.5f, 0.0f, 0.5f, 1.0f,

        0.5f, 0.0f, 0.5f, 1.0f,
        0.5f, 1.0f, 0.5f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f,

        //ściana 4
        0.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.0f, 0.5f, 1.0f,

        //ściana 5
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f,
        0.5f, 1.0f, 0.5f, 1.0f
    };

    float TexCoords[] = {
        1.0f, 1.0f,   1.0f, 0.0f,    0.0f, 1.0f,
        1.0f, 0.0f,	  0.0f, 1.0f,    0.0f, 0.0f,

        1.0f, 1.0f,   1.0f, 0.0f,    0.0f, 1.0f,
        0.0f, 1.0f,	  0.0f, 0.0f,   1.0f, 0.0f,  

        1.0f, 1.0f,   1.0f, 0.0f,    0.0f, 1.0f,
        0.0f, 1.0f,	  0.0f, 0.0f,   1.0f, 0.0f, 

        0.0f, 0.0f,	  1.0f, 0.0f,    0.5f, 0.5f,

        0.0f, 0.0f,	  1.0f, 0.0f,    0.5f, 0.5f
    };

    float Normals[]={
        0.0f,0.0f,-1.0f,0.0f, //A
        0.0f,0.0f,-1.0f,0.0f, //B
        0.0f,0.0f,-1.0f,0.0f, //C
        0.0f,0.0f,-1.0f,0.0f, //A
        0.0f,0.0f,-1.0f,0.0f, //D
        0.0f,0.0f,-1.0f,0.0f, //B
    
        0.5f,0.0f,0.5f,0.0f, //A
        0.5f,0.0f,0.5f,0.0f, //B
        0.5f,0.0f,0.5f,0.0f, //C
        0.5f,0.0f,0.5f,0.0f, //A
        0.5f,0.0f,0.5f,0.0f, //D
        0.5f,0.0f,0.5f,0.0f, //B
        
        -0.5f,0.0f, 0.5f, 0.0f, //A
        -0.5f,0.0f, 0.5f, 0.0f, //B
        -0.5f,0.0f, 0.5f, 0.0f, //C
        -0.5f,0.0f, 0.5f, 0.0f, //A
        -0.5f,0.0f, 0.5f, 0.0f, //D
        -0.5f,0.0f, 0.5f, 0.0f,  //B
    
        0.0f,-1.0f, 0.0f, 0.0f, //A
        0.0f,-1.0f, 0.0f, 0.0f, //B
        0.0f,-1.0f, 0.0f, 0.0f, //C
    
        0.0f,1.0f, 0.0f, 0.0f, //A
        0.0f,1.0f, 0.0f, 0.0f, //D
        0.0f,1.0f, 0.0f, 0.0f //B
    };
    shape_triangle(Vertices, Normals);

    VERTICES = new float[96];
    TEX_COORDS = new float[48];
    NORMALS = new float[96];

    TexCoords[40] = b * cos(gamma) / a;
    TexCoords[41] = b * sin(gamma) / a;
    TexCoords[46] = b * cos(gamma) / a;
    TexCoords[47] = b * sin(gamma) / a;
    skaluj(TexCoords, 0, 12, 2, a);
    skaluj(TexCoords, 12, 24, 2, b);
    skaluj(TexCoords, 24, 36, 2, sqrt(a*a+b*b-2*a*b*cos(gamma)));
    skaluj(TexCoords, 36, 48, 2, a/sin(gamma));
    skaluj(TexCoords, 1, 36, 2, h);
    skaluj(TexCoords, 37, 48, 2, a/sin(gamma));

    for(unsigned short i=0;i<96;i++) VERTICES[i] = Vertices[i];
    for(unsigned short i=0;i<48;i++) TEX_COORDS[i] = TexCoords[i];
    for(unsigned short i=0;i<96;i++) NORMALS[i] = Normals[i];
}

void Wall_triangular::skaluj(float tab[], unsigned int start, unsigned int stop, unsigned int step, float mnoznik){
    for(unsigned i=start;i<stop;i += step) tab[i] *= mnoznik;
}

Wall_triangular::Wall_triangular(){
    C = glm::vec3(0.0, 0.0, 0.0);
    h=1;
    a=1;
    b=1;
    gamma=0.78;
    wall_initializer();
}

Wall_triangular::Wall_triangular(glm::vec3 punkt, float a, float b, float h, float gamma, float angle_horizontal){
    this->C = punkt;
    this->h = h;
    this->a = a;
    this->b = b;
    this->gamma = gamma;
    this->angle_horizontal = angle_horizontal;
    wall_initializer();
}

void Wall_triangular::draw(glm::mat4 P, glm::mat4 V, GLuint tex){
    static ShaderProgram* s_p = spLambertSun;
    s_p->use(); //Aktywuj program cieniujący
    glm::mat4 M = glm::mat4(1.0);

    M = glm::translate(M, C);
    M = glm::rotate(M, (float)(-angle_horizontal), glm::vec3(0.0, 1.0, 0.0));
    //M = glm::rotate(M, (float)(3.14159265359), glm::vec3(1.0, 0.0, 0.0));
    M = glm::scale(M, glm::vec3(a, h, a));


    glUniformMatrix4fv(s_p->u("P"),1,false,glm::value_ptr(P));
    glUniformMatrix4fv(s_p->u("V"),1,false,glm::value_ptr(V));
    glUniformMatrix4fv(s_p->u("M"),1,false,glm::value_ptr(M));

    glEnableVertexAttribArray(s_p->a("vertex"));
    glEnableVertexAttribArray(s_p->a("normal"));
    glEnableVertexAttribArray(s_p->a("texCoord"));

    glVertexAttribPointer(s_p->a("vertex"),4,GL_FLOAT,false,0,VERTICES);
    glVertexAttribPointer(s_p->a("normal"),4,GL_FLOAT,false,0,NORMALS);
    glVertexAttribPointer(s_p->a("texCoord"),2,GL_FLOAT,false,0,TEX_COORDS);
    
    glActiveTexture(GL_TEXTURE0); glBindTexture(GL_TEXTURE_2D,tex);
    glUniform1i(s_p->u("tex"),0);
    glDrawArrays( GL_TRIANGLES, 0, VERTEX_COUNT);

    glDisableVertexAttribArray(s_p->a("vertex"));
    glDisableVertexAttribArray(s_p->a("normal"));
    glDisableVertexAttribArray(s_p->a("texCoord")); 
}

bool Wall_triangular::is_within(glm::vec3 punkt, float radius){
    glm::vec3 _punkt; // punkt w układzie współrzędnych muru
    _punkt.x = (punkt.x - C.x)*cos(angle_horizontal) + (punkt.z - C.z)*sin(angle_horizontal);
    _punkt.z = -(punkt.x - C.x)*sin(angle_horizontal) + (punkt.z - C.z)*cos(angle_horizontal);
    _punkt.y = punkt.y;

    float ht = b*sin(gamma);
    float dt = -ht * tan(gamma - 3.14159265359/2);
    if(_punkt.y > C.y && _punkt.y < C.y + h && _punkt.z > -radius && radius > _punkt.z*dt-_punkt.x*ht && -radius < _punkt.z*(dt-a) - (_punkt.x-a)*ht) return true;

    return false;
}