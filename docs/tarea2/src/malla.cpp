#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <string>
#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "tools.h"
#include "malla.h"
using namespace std;
malla::malla(char* filename, int shaderprog){
    this->setpos(glm::vec3(0,0,0));
	this->filename = filename;
	this->shaderprog = shaderprog;
	assert(load_mesh(filename, &vao, &numvertices));
	model_location = glGetUniformLocation(shaderprog, "model");
	this-> saltando  =false;
	this -> velocidad = glm::vec3(0.0f,0.0f,0.0f);
    this -> ultimo_salto = 0.0;
}

GLuint malla::getvao(){
    return this->vao;
}

int malla::getnumvertices(){
    return this->numvertices;
}

glm::vec3 malla::getpos(){
	return this->pos;
}

char* malla::getfilename(){
    	return this->filename;
}

void malla::setpos(glm::vec3 p){
	pos = p;
   	model = glm::translate(glm::mat4(1.0f), pos); 
}

void malla::draw(){
	glUseProgram(shaderprog);
        glBindVertexArray(this->getvao());
        glUniformMatrix4fv(model_location, 1, GL_FALSE, &model[0][0]);
        glDrawArrays(GL_TRIANGLES, 0, this->getnumvertices());
        glBindVertexArray(0);
}

void malla::saltar(){
    if (!(this->saltando)){
        this->velocidad = glm::vec3(0.0f, 0.09f, 0.0f);
        this->saltando = true;
        this-> ultimo_salto = getpos()[1];
    }
}

void malla::calculo_velocidad_posicion(){
    if (this->saltando && this->getpos()[1] >= this->ultimo_salto){
        this->setpos(this->getpos() + this->velocidad);
        this->velocidad += glm::vec3(0.0f, -0.001f, 0.0f);
    }
    else if (this->saltando && this->getpos()[1] < this->ultimo_salto){
        this->setpos(glm::vec3(this->getpos()[0], this->ultimo_salto, this->getpos()[2]));
        this->saltando = false;
    }
}