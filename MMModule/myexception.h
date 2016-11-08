#ifndef MYEXCEPTION_H
#define MYEXCEPTION_H

#include <exception>

using namespace std;

class MyException: public exception{

public:

    MyException(int numero=0, string const& phrase="", int niveau=0) throw()
         :m_numero(numero),m_phrase(phrase),m_niveau(niveau){}

     virtual const char* what() const throw(){
         return m_phrase.c_str();
     }

     int getNiveau() const throw(){
          return m_niveau;
     }

    virtual ~MyException() throw(){}

private:
    int m_numero;               //Numéro de l'erreur
    string m_phrase;            //Description de l'erreur
    int m_niveau;               //Niveau de l'erreur
};

#endif // MYEXCEPTION_H
