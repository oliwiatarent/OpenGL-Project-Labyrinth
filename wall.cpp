#include "wall.h"
#define PI 3.14159265359

void Wall_rect::wall_initializer(){
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

    VERTEX_COUNT = 36;
    VERTICES = verts;
    NORMALS = normals;
    TEX_COORDS = new float[72];
    for(unsigned short i=0;i<72;i++) TEX_COORDS[i] = texCoords[i];

    skaluj(TEX_COORDS, 1, 24, 2, h);
    skaluj(TEX_COORDS, 49, 72, 2, h);
    skaluj(TEX_COORDS, 0, 24, 2, l);
    skaluj(TEX_COORDS, 48, 72, 2, w);
    skaluj(TEX_COORDS, 24, 48, 2, l);
    skaluj(TEX_COORDS, 25, 48, 2, w);
}

void Wall_rect::skaluj(float tab[], unsigned int start, unsigned int stop, unsigned int step, float mnoznik){
    for(unsigned i=start;i<stop;i += step) tab[i] *= mnoznik;
}

Wall_rect::Wall_rect(){
    DBL = glm::vec3(0.0, 0.0, 0.0);
    h = 1.0;
    w = 1.0;
    l = 1.0;
    wall_initializer();
}

Wall_rect::Wall_rect(glm::vec3 DBL, glm::vec3 LHW){
    this->DBL = DBL;
    l = LHW.x;
    h = LHW.y;
    w = LHW.z;
    wall_initializer();
}

Wall_rect::Wall_rect(float xl, float yd, float zb, float dlugosc, float wysokosc, float szerokosc){
    DBL = glm::vec3(xl, yd, zb);
    this->l = dlugosc;
    this->h = wysokosc;
    this->w = szerokosc;
    wall_initializer();
}

Wall_rect::~Wall_rect(){
    //delete[] TEX_COORDS;
}

void Wall_rect::setAngle_horizontal(float alpha){
    this->angle_horizontal = alpha;
}

void Wall_rect::setAngle_vertical(float alpha){
    this->angle_vertical = alpha;
}

void Wall_rect::setTexture(GLuint texture_id){
    this->texture_id = texture_id;
}

void Wall_rect::draw(glm::mat4 P, glm::mat4 V, ShaderProgram* s_p){
    s_p->use(); //Aktywuj program cieniujący
    glm::mat4 M = glm::mat4(1.0f);

    M = glm::translate(M, DBL);
    M = glm::rotate(M, -angle_horizontal, glm::vec3(0.0, 1.0, 0.0));
    M = glm::rotate(M, (float)(angle_vertical), glm::vec3(0.0, 0.0, 1.0));
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
    
    glActiveTexture(GL_TEXTURE0); glBindTexture(GL_TEXTURE_2D, texture_id);
    glUniform1i(s_p->u("tex"),0);
    glDrawArrays( GL_TRIANGLES, 0, VERTEX_COUNT);

    glDisableVertexAttribArray(s_p->a("vertex"));
    glDisableVertexAttribArray(s_p->a("normal"));
    glDisableVertexAttribArray(s_p->a("texCoord")); 
}

char Wall_rect::getType(){
    return 0;
}

bool Wall_rect::is_within(glm::vec3 punkt, float r){
    glm::vec3 _punkt; // punkt w układzie współrzędnych muru
    _punkt.z = -(punkt.x - DBL.x)*sin(angle_horizontal) + (punkt.z - DBL.z)*cos(angle_horizontal);
    _punkt.y = -(punkt.x - DBL.x)*cos(angle_horizontal)*sin(angle_vertical) + (punkt.y - DBL.y)*cos(angle_vertical) - (punkt.z - DBL.z)*sin(angle_horizontal)*sin(angle_vertical);
    _punkt.x = (punkt.x - DBL.x)*cos(angle_horizontal)*cos(angle_vertical) + (punkt.y - DBL.y)*sin(angle_vertical) + (punkt.z - DBL.z)*sin(angle_horizontal)*cos(angle_vertical);
    return _punkt.x + r > 0 && _punkt.z + r > 0 && _punkt.y+r > 0 && _punkt.x-r < l && _punkt.z-r < w && _punkt.y-r < h;
}

//Wall_traingular ---------------------------------------------------
void Wall_trian::shape_triangle(float v[], float n[]){
    float x = l * cos(gamma) / w;
    float z = l * sin(gamma) / w;
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

void Wall_trian::wall_initializer(){
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

    VERTEX_COUNT = 24;
    VERTICES = new float[96];
    TEX_COORDS = new float[48];
    NORMALS = new float[96];

    TexCoords[40] = l * cos(gamma) / w;
    TexCoords[41] = l * sin(gamma) / w;
    TexCoords[46] = l * cos(gamma) / w;
    TexCoords[47] = l * sin(gamma) / w;
    skaluj(TexCoords, 0, 12, 2, w);
    skaluj(TexCoords, 12, 24, 2, l);
    skaluj(TexCoords, 24, 36, 2, sqrt(l*l+w*w-2*l*w*cos(gamma)));
    skaluj(TexCoords, 36, 48, 2, w/sin(gamma));
    skaluj(TexCoords, 1, 36, 2, h);
    skaluj(TexCoords, 37, 48, 2, w/sin(gamma));

    for(unsigned short i=0;i<96;i++) VERTICES[i] = Vertices[i];
    for(unsigned short i=0;i<48;i++) TEX_COORDS[i] = TexCoords[i];
    for(unsigned short i=0;i<96;i++) NORMALS[i] = Normals[i];
}

void Wall_trian::skaluj(float tab[], unsigned int start, unsigned int stop, unsigned int step, float mnoznik){
    for(unsigned i=start;i<stop;i += step) tab[i] *= mnoznik;
}

Wall_trian::Wall_trian(){
    DBL = glm::vec3(0.0, 0.0, 0.0);
    h=1;
    w=1;
    l=1;
    gamma=0.78;
    wall_initializer();
}

Wall_trian::Wall_trian(glm::vec3 punkt, float a, float b, float h, float gamma){
    this->DBL = punkt;
    this->h = h;
    this->w = a;
    this->l = b;
    this->gamma = gamma;
    this->angle_horizontal = angle_horizontal;
    this->angle_vertical = 0;
    wall_initializer();
}

void Wall_trian::setAngle_horizontal(float alpha){
    angle_horizontal = alpha;
}

void Wall_trian::setAngle_vertical(float alpha){
    this->angle_vertical = alpha;
}

void Wall_trian::setTexture(GLuint texture_id){
    this->texture_id = texture_id;
}

void Wall_trian::draw(glm::mat4 P, glm::mat4 V, ShaderProgram* s_p){
    s_p->use(); //Aktwuj program cieniujący
    glm::mat4 M = glm::mat4(1.0);

    M = glm::translate(M, DBL);
    M = glm::rotate(M, (float)(-angle_horizontal), glm::vec3(0.0, 1.0, 0.0));
    M = glm::rotate(M, angle_vertical, glm::vec3(0.0, 0.0, 1.0));
    M = glm::scale(M, glm::vec3(w, h, w));


    glUniformMatrix4fv(s_p->u("P"),1,false,glm::value_ptr(P));
    glUniformMatrix4fv(s_p->u("V"),1,false,glm::value_ptr(V));
    glUniformMatrix4fv(s_p->u("M"),1,false,glm::value_ptr(M));

    glEnableVertexAttribArray(s_p->a("vertex"));
    glEnableVertexAttribArray(s_p->a("normal"));
    glEnableVertexAttribArray(s_p->a("texCoord"));

    glVertexAttribPointer(s_p->a("vertex"),4,GL_FLOAT,false,0,VERTICES);
    glVertexAttribPointer(s_p->a("normal"),4,GL_FLOAT,false,0,NORMALS);
    glVertexAttribPointer(s_p->a("texCoord"),2,GL_FLOAT,false,0,TEX_COORDS);
    
    glActiveTexture(GL_TEXTURE0); glBindTexture(GL_TEXTURE_2D, texture_id);
    glUniform1i(s_p->u("tex"),0);
    glDrawArrays( GL_TRIANGLES, 0, VERTEX_COUNT);

    glDisableVertexAttribArray(s_p->a("vertex"));
    glDisableVertexAttribArray(s_p->a("normal"));
    glDisableVertexAttribArray(s_p->a("texCoord")); 
}

char Wall_trian::getType(){
    return 1;
}

bool Wall_trian::is_within(glm::vec3 punkt, float r){
    glm::vec3 _punkt; // punkt w układzie współrzędnych muru
    _punkt.z = -(punkt.x - DBL.x)*sin(angle_horizontal) + (punkt.z - DBL.z)*cos(angle_horizontal);
    _punkt.y = -(punkt.x - DBL.x)*cos(angle_horizontal)*sin(angle_vertical) + (punkt.y - DBL.y)*cos(angle_vertical) - (punkt.z - DBL.z)*sin(angle_horizontal)*sin(angle_vertical);
    _punkt.x = (punkt.x - DBL.x)*cos(angle_horizontal)*cos(angle_vertical) + (punkt.y - DBL.y)*sin(angle_vertical) + (punkt.z - DBL.z)*sin(angle_horizontal)*cos(angle_vertical);

    glm::vec2 C(l*sin(gamma+PI/2), l*cos(gamma-PI/2));
    return _punkt.y+r > 0 && _punkt.y-r < h && _punkt.z+r > 0 && (_punkt.z)*(C.x) - (C.y)*(_punkt.x)-r < 0 && (_punkt.z)*(C.x-w) - (C.y)*(_punkt.x - w)+r > 0;
}
//Ramp ----------------------------------------------------------------------------------------------------------------

void Ramp::wall_initializer(){
    Wall_trian::wall_initializer();
}

void Ramp::skaluj(float tab[], unsigned int start, unsigned int stop, unsigned int step, float mnoznik){
    Wall_trian::skaluj(tab, start, stop, step, mnoznik);
}

Ramp::Ramp(glm::vec3 punkt, float a, float b, float h){
    this->DBL = punkt;
    this->h = a;
    this->l = b;
    this->w = h;
    this->gamma = PI/2;
    this->angle_vertical = PI/2;
    wall_initializer();
}

void Ramp::setAngle_horizontal(float alpha){
    Wall_trian::setAngle_horizontal(alpha);
}

void Ramp::setAngle_vertical(float alpha){

}

void Ramp::setTexture(GLuint texture_id){
    Wall_trian::setTexture(texture_id);
}

void Ramp::draw(glm::mat4 P, glm::mat4 V, ShaderProgram* s_p){
    Wall_trian::draw(P, V, s_p);
}

char Ramp::getType(){
    return 2;
}

bool Ramp::is_within(glm::vec3 punkt, float radius){
    return Wall_trian::is_within(punkt, radius);
}

float Ramp::getRampAngleRatio(){
    return h/l;
}

//Wall_creator --------------------------------------------------------------------------------------------------------
void Wall_creator::set_current_wall(){
    if(current_wall_creation_type==0){
        current_wall_rect = Wall_rect(DBL.x, DBL.y, DBL.z, l, h, w);
        current_wall_rect.setAngle_horizontal(angle_horizontal);
        current_wall_rect.setAngle_vertical(angle_vertical);
        current_wall_rect.setTexture(texture_id);
        current_wall = &current_wall_rect;
    }
    else if(current_wall_creation_type==1){
        current_wall_trian = Wall_trian(DBL, l, w, h, gamma);
        current_wall_trian.setAngle_horizontal(angle_horizontal);
        current_wall_trian.setAngle_vertical(angle_vertical);
        current_wall_trian.setTexture(texture_id);
        current_wall = &current_wall_trian;
    }
}

Wall_creator::Wall_creator(){
    walls_rect = new Wall_rect[1000];
    walls_trian = new Wall_trian[1000];
    setArguments(glm::vec3(0.0, 0.0, 0.0), 1.0, 1.0, 1.0, 0.78, 0.0, 0.0);
}

void Wall_creator::setArguments(glm::vec3 DBL, float length, float width, float height, float gamma, float angle_horizontal, float angle_vertical){
    this->DBL = DBL;
    l = length;
    w = width;
    h = height;
    this->gamma = gamma;
    this->angle_horizontal = angle_horizontal;
    this->angle_vertical = angle_vertical;
    this->texture_id = texture_id;
    current_wall_creation_type = 0;
    set_current_wall();
}

void Wall_creator::assign_next_texture(std::vector<GLuint>& textures){
    static unsigned int ptr = 0;
    this->texture_id = textures[ptr];
    ptr++;
    ptr %= textures.size();
    set_current_wall();
}

void Wall_creator::switch_wall_type(){
    current_wall_creation_type++;
    if(current_wall_creation_type==2) current_wall_creation_type = 0;
    set_current_wall();
}

char Wall_creator::get_wall_type(){
    return current_wall_creation_type;
}

void Wall_creator::move_X(float dx){
    DBL.x += dx;
    set_current_wall();
}

void Wall_creator::move_Y(float dx){
    DBL.y += dx;
    set_current_wall();
}

void Wall_creator::move_Z(float dx){
    DBL.z += dx;
    set_current_wall();
}

void Wall_creator::changeLength(float dx){
    if(l + dx > 0){
        l += dx;
        set_current_wall();
    }
}

void Wall_creator::changeWidth(float dx){
    if(w + dx > 0){
        w += dx;
        set_current_wall();
    }
}

void Wall_creator::changeHeight(float dx){
    if(h + dx > 0){
        h += dx;
        set_current_wall();
    }
}

void Wall_creator::changeGamma(float dx){
    if(gamma + dx > 0 && gamma +dx < 3.14159265359){
        gamma += dx;
        set_current_wall();
    }
}

void Wall_creator::changeAngle_horizontal(float dx){
    angle_horizontal += dx;
    set_current_wall();
}

void Wall_creator::changeAngle_vertical(float dx){
    angle_vertical += dx;
    set_current_wall();
}

void Wall_creator::finish_wall_creation(std::vector<Obstacle*>& obstacles){
    is_creating_wall = false;
    if(current_wall_creation_type==0){
        walls_rect[walls_rect_ptr++] = current_wall_rect;
        obstacles.push_back(&walls_rect[walls_rect_ptr-1]);
    }
    else if(current_wall_creation_type==1){
        walls_trian[walls_trian_ptr++] = current_wall_trian;
        obstacles.push_back(&walls_trian[walls_trian_ptr-1]);
    }
    setArguments(glm::vec3(0.0, 0.0, 0.0), 1.0, 1.0, 1.0, 0.78, 0.0, 0.0);
}

void Wall_creator::abort_wall_creation(){
    is_creating_wall = false;
    setArguments(glm::vec3(0.0, 0.0, 0.0), 1.0, 1.0, 1.0, 0.78, 0.0, 0.0);
}

// Obstacle_rect-------------------------------------------------------------------------------------------

bool Obstacle_rect::rayIntersectsAABB(const glm::vec3& rayOrigin, const glm::vec3& rayDir, const glm::vec3& boxMin, const glm::vec3& boxMax, float& t) {
    float tmin = (boxMin.x - rayOrigin.x) / rayDir.x;
    float tmax = (boxMax.x - rayOrigin.x) / rayDir.x;
    if (tmin > tmax) std::swap(tmin, tmax);

    float tymin = (boxMin.y - rayOrigin.y) / rayDir.y;
    float tymax = (boxMax.y - rayOrigin.y) / rayDir.y;
    if (tymin > tymax) std::swap(tymin, tymax);

    if ((tmin > tymax) || (tymin > tmax)) return false;
    if (tymin > tmin) tmin = tymin;
    if (tymax < tmax) tmax = tymax;

    float tzmin = (boxMin.z - rayOrigin.z) / rayDir.z;
    float tzmax = (boxMax.z - rayOrigin.z) / rayDir.z;
    if (tzmin > tzmax) std::swap(tzmin, tzmax);

    if ((tmin > tzmax) || (tzmin > tmax)) return false;
    if (tzmin > tmin) tmin = tzmin;
    if (tzmax < tmax) tmax = tzmax;

    t = tmin;
    return true;
}

Obstacle_rect::Obstacle_rect(){
    DBL.x = 0.0;
    DBL.y = 0.0;
    DBL.z = 0.0;
    l = 6.0;
    w = 8.0;
    h = 5.0;
    angle_horizontal = 0.0;
    angle_vertical = 0.0;
}

Obstacle_rect::Obstacle_rect(glm::vec3 position){
    DBL = position;
    l = 6.0;
    w = 8.0;
    h = 5.0;
    angle_horizontal = 0.0;
    angle_vertical = 0.0;
}

Obstacle_rect::Obstacle_rect(glm::vec3 position, glm::vec3 size){
    DBL = position;
    l = size.x;
    h = size.y;
    w = size.z;
    angle_horizontal = 0.0;
    angle_vertical = 0.0;   
}

void Obstacle_rect::setAngle_horizontal(float alpha){
    angle_horizontal = alpha;
}

void Obstacle_rect::setAngle_vertical(float alpha){
    angle_vertical = alpha;
}

void Obstacle_rect::draw(glm::mat4 P, glm::mat4 V, ShaderProgram* s_p){

}

bool Obstacle_rect::is_within(glm::vec3 punkt, float r){
    return false;
}

glm::vec3 Obstacle_rect::getSize(){
    return glm::vec3(l, h, w);
}

glm::vec3 Obstacle_rect::getPosition(){
    return DBL;
}

void Obstacle_rect::setModelMatrix(glm::mat4 matrix){
    this->modelMatrix = matrix;
}

void Obstacle_rect::setIsSelected(bool is_selected){
    this->is_selected = is_selected;
}

bool Obstacle_rect::is_clicked_on(const glm::vec3& rayOrigin, const glm::vec3& rayDir, float& t){
    glm::vec3 halfSize = getSize() * 0.5f;
    glm::vec3 boxMin = getPosition() - halfSize;
    glm::vec3 boxMax = getPosition() + halfSize;
    return rayIntersectsAABB(rayOrigin, rayDir, boxMin, boxMax, t);
}

// FENCE --------------------------------------------------------------------------

Fence::Fence(){
    DBL = glm::vec3(0.0, 0.0, 0.0);
    l = 6.0;
    w = 8.0;
    h = 9.0;
    angle_horizontal = 0.0;
    angle_vertical = 0.0;
    final_height = DBL.y;
}

Fence::Fence(glm::vec3 position){
    DBL = position;
    l = 6.0;
    w = 8.0;
    h = 9.0;
    angle_horizontal = 0.0;
    angle_vertical = 0.0;
    final_height = position.y;
}

Fence::Fence(glm::vec3 position, glm::vec3 size){
    DBL = position;
    l = size.x;
    h = size.y;
    w = size.z;
    angle_horizontal = 0.0;
    angle_vertical = 0.0;   
    final_height = position.y;
}

void Fence::setAngle_horizontal(float alpha){
    angle_horizontal = alpha;
}

void Fence::setAngle_vertical(float alpha){
    angle_vertical = alpha;
}

void Fence::draw(glm::mat4 P, glm::mat4 V, ShaderProgram* s_p){
    if(!is_existent) return;

    glm::vec3 scaleFactor = glm::vec3(6.0f, 8.0f, 0.5f) / glm::vec3(3.0f, 4.013751983642578f, 0.25f);
    glm::mat4 M = glm::mat4(1.0f);
    M = glm::translate(M, getPosition());
    M = glm::rotate(M, (float)(-PI/2), glm::vec3(1.0f, 0.0f, 0.0f));
    M = glm::rotate(M, angle_horizontal, glm::vec3(0.0f, 0.0f, 1.0f));
    M = glm::scale(M, scaleFactor);
    glUniformMatrix4fv(s_p->u("M"), 1, false, glm::value_ptr(M));
    modelMatrix = M;
    Models::fence.Draw(*s_p);
}

bool Fence::is_within(glm::vec3 punkt, float r){
    if(!is_existent) return false;
    glm::vec3 _punkt; // punkt w układzie współrzędnych muru
    glm::vec3 _DBL = DBL - getSize()/glm::vec3(2.0, 2.0, 2.0);
    _punkt.z = -(punkt.x - _DBL.x)*sin(angle_horizontal) + (punkt.z - _DBL.z)*cos(angle_horizontal);
    _punkt.y = -(punkt.x - _DBL.x)*cos(angle_horizontal)*sin(angle_vertical) + (punkt.y - _DBL.y)*cos(angle_vertical) - (punkt.z - _DBL.z)*sin(angle_horizontal)*sin(angle_vertical);
    _punkt.x = (punkt.x - _DBL.x)*cos(angle_horizontal)*cos(angle_vertical) + (punkt.y - _DBL.y)*sin(angle_vertical) + (punkt.z - _DBL.z)*sin(angle_horizontal)*cos(angle_vertical);
    return _punkt.x + r > l*0.25 && _punkt.z + r > 0 && _punkt.y+r > 0 && _punkt.x-r < l*0.75 && _punkt.z-r < w && _punkt.y-r < h;
}

glm::vec3 Fence::getSize(){
    return glm::vec3(l, h, w);
}

glm::vec3 Fence::getPosition(){
    return DBL;
}

void Fence::setModelMatrix(glm::mat4 matrix){
    this->modelMatrix = matrix;
}

void Fence::setIsSelected(bool is_selected){
    this->is_selected = is_selected;
}

bool Fence::is_clicked_on(const glm::vec3& rayOrigin, const glm::vec3& rayDir, float& t){
    if(!is_existent) return false;
    return Obstacle_rect::is_clicked_on(rayOrigin, rayDir, t);
}

void Fence::change_height(float dh){
    is_moving = true;
    final_height += dh;
}

void Fence::move(float T){
    if(is_moving){
        float margin = 0.01;
        if(final_height - margin < DBL.y && final_height + margin > DBL.y){
            DBL.y = final_height;
            if(is_moving) is_existent = false;
            is_moving = false;
        }
        if(final_height > DBL.y) DBL.y += velocity_value*T;
        else if(final_height < DBL.y) DBL.y -= velocity_value*T;
    }
}

// DOOR ---------------------------------------------------------------------------------------------

Door::Door(){
    DBL = glm::vec3(0.0, 0.0, 0.0);
    l = 4.0/1.5;
    h = 4.0;
    w = 4.0/10.0;
    angle_horizontal = 0.0;
    final_angle_horizontal = 0.0;
    angle_vertical = 0.0;   
}

Door::Door(glm::vec3 position, float scale){
    DBL = position;
    l = scale/1.5;
    h = scale;
    w = scale/10.0;
    angle_horizontal = 0.0;
    final_angle_horizontal = 0.0;
    angle_vertical = 0.0;  
}

void Door::setAngle_horizontal(float alpha){
    Obstacle_rect::setAngle_horizontal(alpha);
}

void Door::setAngle_vertical(float alpha){
    Obstacle_rect::setAngle_vertical(alpha);
}

void Door::draw(glm::mat4 P, glm::mat4 V, ShaderProgram* s_p){
    glm::mat4 M = glm::mat4(1.0f);
    M = glm::translate(M, getPosition());
    M = glm::rotate(M, (float) 0.0, glm::vec3(0.0, 1.0, 0.0));
    M = glm::rotate(M, (float) -angle_horizontal, glm::vec3(0.0, 1.0, 0.0));
    M = glm::scale(M, getSize()/(glm::vec3(-1744.371826171875, -181.78280639648438, 743.0694580078125) - glm::vec3(-1893.22802734375, -400.7828063964844, 738.0694580078125)));
    M = glm::translate(M, glm::vec3(1893.22802734375, 400.7828063964844, -738.0694580078125));
    s_p->use();
    glUniformMatrix4fv(s_p->u("M"), 1, false, glm::value_ptr(M));
    glUniformMatrix4fv(s_p->u("P"), 1, false, glm::value_ptr(P));
    glUniformMatrix4fv(s_p->u("V"), 1, false, glm::value_ptr(V));
    Models::door.Draw(*s_p);
    s_p->use();
}

bool Door::is_within(glm::vec3 punkt, float r){
    glm::vec3 _punkt; // punkt w układzie współrzędnych muru
    _punkt.z = -(punkt.x - DBL.x)*sin(angle_horizontal) + (punkt.z - DBL.z)*cos(angle_horizontal);
    _punkt.y = -(punkt.x - DBL.x)*cos(angle_horizontal)*sin(angle_vertical) + (punkt.y - DBL.y)*cos(angle_vertical) - (punkt.z - DBL.z)*sin(angle_horizontal)*sin(angle_vertical);
    _punkt.x = (punkt.x - DBL.x)*cos(angle_horizontal)*cos(angle_vertical) + (punkt.y - DBL.y)*sin(angle_vertical) + (punkt.z - DBL.z)*sin(angle_horizontal)*cos(angle_vertical);
    return _punkt.x + r > 0 && _punkt.z + r > 0 && _punkt.y+r > 0 && _punkt.x-r < l && _punkt.z-r < w && _punkt.y-r < h;
}

glm::vec3 Door::getSize(){
    return glm::vec3(l, h, w);
}

glm::vec3 Door::getPosition(){
    return DBL;
}

bool Door::is_clicked_on(const glm::vec3& rayOrigin, const glm::vec3& rayDir, float& t){
    glm::vec3 boxMin = getPosition();
    glm::vec3 boxMax = getPosition();

    boxMax.x += l * cos(-angle_horizontal) + w * sin(-angle_horizontal);
    boxMax.y += h;
    boxMax.z += w * cos(angle_horizontal) + l * sin(angle_horizontal);

    if(boxMax.x  < boxMin.x) std::swap(boxMax.x, boxMin.x);
    if(boxMax.y  < boxMin.y) std::swap(boxMax.y, boxMin.y);
    if(boxMax.z  < boxMin.z) std::swap(boxMax.z, boxMin.z);

    return Obstacle_rect::rayIntersectsAABB(rayOrigin, rayDir, boxMin, boxMax, t);
}

void Door::open_close(){
    if(!is_moving){
        if(angle_horizontal < PI/4){ // drzwi zamknięte
            is_moving = true;
            final_angle_horizontal = PI*0.45;
        }
        else{ // drzwi otwarte
            is_moving = true;
            final_angle_horizontal = 0.0;
        }
    }
}

void Door::move(float T){
    if(is_moving){
        float margin = 0.01;
        if(final_angle_horizontal - margin < angle_horizontal && final_angle_horizontal + margin > angle_horizontal){
            angle_horizontal = final_angle_horizontal;
            is_moving = false;
        }
        if(final_angle_horizontal > angle_horizontal) angle_horizontal += velocity_value*T;
        else if(final_angle_horizontal < angle_horizontal) angle_horizontal -= velocity_value*T;
    }
}

// PAINTING -------------------------------------------------------------------

Painting::Painting(){
    DBL = glm::vec3(0.0, 0.0, 0.0);
    l = 0.5;
    w = 5.0;
    h = 3.0;
    angle_horizontal = 0.0;
    angle_vertical = 0.0;
    final_height = DBL.y;
}

Painting::Painting(glm::vec3 position, unsigned short facing) {
    this->facing = facing;
    DBL = position;
    l = 0.5;
    w = 5.0;
    h = 3.0;
    final_height = DBL.y;
    angle_horizontal = 0.0;
    angle_vertical = 0.0;  
}

void Painting::setAngle_horizontal(float alpha){
    Obstacle_rect::setAngle_horizontal(alpha);
}

void Painting::setAngle_vertical(float alpha){
    Obstacle_rect::setAngle_vertical(alpha);
}

void Painting::draw(glm::mat4 P, glm::mat4 V, ShaderProgram* s_p) {
        glm::mat4 M = glm::mat4(1.0f);
        M = glm::translate(M, getPosition());
        M = glm::rotate(M, (float) PI/2, glm::vec3(0.0f, 0.0f, 1.0f));

        if (getFacing() == 0) {
                M = glm::rotate(M, (float) PI/2, glm::vec3(1.0f, 0.0f, 0.0f));
        }

        if (getFacing() == 1) {
                M = glm::rotate(M, (float) PI, glm::vec3(1.0f, 0.0f, 0.0f));
        }

        if (getFacing() == 2) {
                M = glm::rotate(M, (float) -PI/2, glm::vec3(1.0f, 0.0f, 0.0f));
        }

        M = glm::scale(M, glm::vec3(1.5f));

        s_p->use();
        glUniformMatrix4fv(spTextured->u("M"), 1, false, glm::value_ptr(M));
        glUniformMatrix4fv(s_p->u("P"), 1, false, glm::value_ptr(P));
        glUniformMatrix4fv(s_p->u("V"), 1, false, glm::value_ptr(V));
        Models::painting.Draw(*s_p);
}

glm::vec3 Painting::getPosition(){
    return DBL;
}

short unsigned Painting::getFacing(){
    return facing;
}

bool Painting::getOnFloor() {
    return on_floor;
}

bool Painting::is_clicked_on(const glm::vec3& rayOrigin, const glm::vec3& rayDir, float& t){
    glm::vec3 boxMin = getPosition();
    glm::vec3 boxMax = getPosition();

    boxMax.x += l * cos(-angle_horizontal) + w * sin(-angle_horizontal);
    boxMax.y += h;
    boxMax.z += w * cos(angle_horizontal) + l * sin(angle_horizontal);

    if(boxMax.x  < boxMin.x) std::swap(boxMax.x, boxMin.x);
    if(boxMax.y  < boxMin.y) std::swap(boxMax.y, boxMin.y);
    if(boxMax.z  < boxMin.z) std::swap(boxMax.z, boxMin.z);

    return Obstacle_rect::rayIntersectsAABB(rayOrigin, rayDir, boxMin, boxMax, t);
}

void Painting::change_height(float dh){
    if (!on_floor) {
        is_moving = true;
        final_height -= dh;
        on_floor = true;
    }
}

void Painting::move(float T){
    if(is_moving) {
        float margin = 1.5;

        if (DBL.y > final_height + margin) {
            DBL.y -= velocity_value*T;
        } else is_moving = false;
    }
}

#undef PI