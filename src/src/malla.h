#ifndef MALLA_H
#define MALLA_H

using namespace std;

class malla{
    private:
        GLuint vao, vbo;
        int numvertices;
        glm::vec3 pos;
	glm::mat4 model;

        char* filename;
	int model_location;
	int shaderprog;
	bool saltando;
   	 glm::vec3 velocidad;
    double ultimo_salto;


    public:
        malla(char *filename, int shaderprog);

        // gets
        GLuint getvao();
        int getnumvertices();
        glm::vec3 getpos();
        char* getfilename();
	int get_model_location();

        // sets
        void setvao(GLuint vao);
        void setnumvertices(int num);
        void setpos(glm::vec3 p);
        void setfilename(char *f);
	void draw();
	void saltar();
    void calculo_velocidad_posicion();
};

#endif
