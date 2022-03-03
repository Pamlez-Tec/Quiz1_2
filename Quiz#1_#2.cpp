
#include <iostream>
using namespace std;

/*
ITCR
Estudiante: Pamela González
Quiz #1_#2
*/

//Para crear la lista de los medios

struct Medio{
	string tipo;
	string autor;
	string ruta;
	
	Medio (string _tipo, string _autor, string _ruta){
		tipo = _tipo;
		autor = _autor;
		ruta = _ruta;
	}
	void imprimir(){
		cout <<"Tipo medio: "<< tipo <<"\tAutor: "<<autor<<"\t\tRuta:" << ruta << endl;
	}
};

struct NodoMedio{
	Medio * medio;
	NodoMedio * siguiente;
	
	NodoMedio(Medio * _medio){
		medio = _medio;
		siguiente = NULL;
	}
};

struct ListaMedios{
	NodoMedio * primerNodo, *ultimoNodo;

	ListaMedios (){
		primerNodo = ultimoNodo = NULL;
	}
	void imprimir();
	void insertar(Medio*);		
};

//Inicio de las clases del tipo noticia

class Noticia{
	private:
		string titulo;
		string fecha;
		string reportero;
	public:
		Noticia(string,string,string);
		virtual void getInfo();
};

class NoticiaPaper : public Noticia{
	string rutaFoto;
	public:
		NoticiaPaper(string,string,string,string);
		void getInfo();
};

class NoticiaDigital : public Noticia{
	private:
		ListaMedios *medios;
	public:
		NoticiaDigital(string, string, string, ListaMedios*);
		void getInfo();		
};

class NoticiaRadio : public Noticia{
	private:
		string audioURL;
	public:
		NoticiaRadio(string,string,string,string);
		void getInfo();
};

//Constructores y funciones

Noticia::Noticia(string _titulo, string _fecha, string _reportero){
	titulo = _titulo;
	fecha = _fecha;
	reportero = _reportero;
}

void Noticia::getInfo(){
	cout<<"Titulo de la noticia: "<<titulo<<endl;
	cout<<"Fecha: "<<fecha<<endl;
	cout<<"Reportero: "<<reportero<<endl;
}

NoticiaPaper::NoticiaPaper(string _titulo, string _fecha, string _reportero, string _rutaFoto) : Noticia(_titulo, _fecha,_reportero){
	rutaFoto = _rutaFoto;
}

void NoticiaPaper::getInfo(){
	Noticia::getInfo();
	cout<<"Ruta de la foto: "<<rutaFoto<<endl;
}

NoticiaDigital::NoticiaDigital(string _titulo,string _fecha, string _reportero,ListaMedios*_medios) : Noticia(_titulo,_fecha,_reportero){
	medios = _medios;
}

void NoticiaDigital::getInfo(){
	Noticia::getInfo();
	cout<<"Lista de los medios: "<<endl;	
	medios->imprimir();	
}

NoticiaRadio::NoticiaRadio(string _titulo,string _fecha, string _reportero, string _audioURL) : Noticia(_titulo,_fecha,_reportero){
	audioURL = _audioURL;
}

void NoticiaRadio::getInfo(){
	Noticia::getInfo();
	cout<<"Url del audio/file: "<<audioURL<<endl;	
}

void ListaMedios::insertar (Medio * medio)
{
     if (primerNodo == NULL){
         ultimoNodo = primerNodo = new NodoMedio(medio);
     }
     else{
         NodoMedio *nuevo = new NodoMedio(medio);
         nuevo->siguiente = primerNodo;
         primerNodo = nuevo; 
     }    
}

void ListaMedios::imprimir(void)
{
     NodoMedio *tmp = primerNodo;
     
     while (tmp != NULL){
        tmp->medio->imprimir();
        tmp = tmp->siguiente;
     }
}


int main(int argc, char** argv) {
	//Creando los medios para la noticia digital
	ListaMedios *_medios = new ListaMedios();
	Medio * _foto = new Medio("Foto", "Pamela","rutaDeLaFoto");
	Medio * _video = new Medio("Video", "Yendry","rutaDelVideo");
	Medio * _audio = new Medio("Audio", "Trebol","rutaDelAudio");
	_medios->insertar(_foto);
	_medios->insertar(_video);
	_medios->insertar(_audio);
	
	//Creando las noticias	
	Noticia * noticias[3];
	noticias[0] = new NoticiaPaper("Noticia_Paper","02/03/2022","Manuel","rutaAqui");
	noticias[1] = new NoticiaDigital("Noticia_Digital","02-03-2022","Ana",_medios);
	noticias[2] = new NoticiaRadio("Noticia_Radio","02_03_2022","Carolina","URL-Audio");

	for(int i = 0; i < 3; i++){
		cout << endl;
		noticias[i]->getInfo();
	}	
	
	return 0;
}
